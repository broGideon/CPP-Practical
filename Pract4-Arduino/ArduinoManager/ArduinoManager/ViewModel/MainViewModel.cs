using System.Collections.ObjectModel;
using SecondLibPractice;
using System.Timers;
using System.IO.Ports;
using System.Windows.Threading;
using Timer = System.Timers.Timer;

namespace ArduinoManager.ViewModel;

public class MainViewModel : BindingHelper
{
    public string Message
    {
        get => _message;
        set => SetField(ref _message, value);
    }

    private string _message;

    public ObservableCollection<float> Timings
    {
        get => _timings;
        set => SetField(ref _timings, value);
    }

    private ObservableCollection<float> _timings = new();

    public string PortName
    {
        get => _portName;
        set => SetField(ref _portName, value);
    }

    private string _portName;

    public string CommandName
    {
        get => _commandName;
        set => SetField(ref _commandName, value);
    }

    private string _commandName;

    public float TimingSelect
    {
        get => _timingSelect;
        set => SetField(ref _timingSelect, value);
    }

    private float _timingSelect;

    private SerialPort _serialPort;

    private Timer _timer;

    private delegate void UpdateText(string text);

    public MainViewModel()
    {
        CommandName = "Подключиться";
        Timings.Add(0.1f);
        Timings.Add(0.5f);
        Timings.Add(1f);
    }

    public void LedBlink()
    {

        if (TimingSelect != 0 && _serialPort != null && _serialPort.IsOpen)
        {
            _serialPort.Write(TimingSelect.ToString());
            Console.WriteLine(TimingSelect.ToString());
        }
    }

    public void ConnectOrDisconnectArduino()
    {
        if (_serialPort != null && _serialPort.IsOpen)
        {
            _serialPort.Close();
            CommandName = "Подключиться";
            Console.WriteLine("Отключено");
            return;
        }
        else
        {
            try
            {
                _serialPort = new SerialPort(PortName, 9600)
                {
                    DtrEnable = true,
                    ReadTimeout = 1000
                };

                Thread.Sleep(500);
                _serialPort.Open();
                Console.WriteLine("Подключено");
            }
            catch (Exception e)
            {
                //Console.WriteLine(e.Message);
                return;
            }

            _timer = new Timer(1000);
            _timer.Elapsed += OnTimerEvent;
            _timer.AutoReset = true;
            _timer.Enabled = true;

            CommandName = "Отключиться";
        }

    }

    public void OnTimerEvent(object sender, ElapsedEventArgs e)
    {
        if (!_serialPort.IsOpen) return;

        try
        {
            _serialPort.DiscardInBuffer();
            string textInPort = _serialPort.ReadLine();
            Message = textInPort;
        }
        catch (Exception exception)
        {
            //Console.WriteLine(exception);
            return;
        }
    }

    public void PlayMusic()
    {
        if (_serialPort != null && _serialPort.IsOpen)
        {
            _serialPort.Write("-1");
        }
    }
}