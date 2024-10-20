
using ArduinoManager.ViewModel;

namespace ArduinoManager;

public partial class MainWindow
{
    public MainWindow()
    {
        InitializeComponent();
        DataContext = new MainViewModel();
    }
}