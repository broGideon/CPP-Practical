#include <Windows.h>
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int num, sum1, sum2;
	double double1, double2;
	do
	{
		setlocale(LC_ALL, "Rus");
		SetConsoleCP(1251);
		cout << "Выберети действие\n";
		cout << "1. Сложиь 2 числа\n";
		cout << "2. Вычесть второе из первого\n";
		cout << "3. Перемножить два числа\n";
		cout << "4. Разделить первое на второе\n";
		cout << "5. Возвести в степень N число\n";
		cout << "6. Найти квадратный корень из числа\n";
		cout << "7. Найти 1 процент от числа\n";
		cout << "8. Найти факториал из числа\n";
		cout << "9. Выход\n";
		cin >> num;
		switch (num)
		{
		case 1:
			cout << "Введите первое число: ";
			cin >> sum1;
			cout << "Введите второе число: ";
			cin >> sum2;
			cout << "Ответ: " << sum1 + sum2 << "\n";
			break;
		case 2:
			cout << "Введите первое число: ";
			cin >> sum1;
			cout << "Введите второе число: ";
			cin >> sum2;
			cout << "Ответ: " << sum1 - sum2 << "\n";
			break;
		case 3:
			cout << "Введите первое число: ";
			cin >> sum1;
			cout << "Введите второе число: ";
			cin >> sum2;
			cout << "Ответ: " << sum1 * sum2 << "\n";
			break;
		case 4:
			cout << "Введите первое число: ";
			cin >> sum1;
			cout << "Введите второе число: ";
			cin >> sum2;
			if (sum2 != 0)
			{
				cout << "Ответ: " << sum1 / sum2 << "\n";
			}
			else
			{
				cout << "На ноль делить нельзя\n";
			}
			break;
		case 5:
			cout << "Введите число: ";
			cin >> double1;
			cout << "Введите степень: ";
			cin >> double2;
			cout << "Ответ: " << pow(double1, double2) << "\n";
			break;
		case 6:
			cout << "Введите число: ";
			cin >> double1;
			cout << "Ответ: " << sqrt(double1) << "\n";
			break;
		case 7:
			cout << "Введите число: ";
			cin >> double1;
			cout << "Ответ: " << double1 / 100 << "\n";
			break;
		case 8:
			cout << "Введите число: ";
			cin >> sum1;
			sum2 = 1;
			if (sum1 >= 0)
			{
				for (int i = 1; i <= sum1; i++)
				{
					sum2 *= i;
				}
				cout << "Ответ: " << sum2 << "\n";
			}
			else
			{
				cout << "Факториал начинается с нуля\n";
			}
			break;
		}
	} while (num != 9);
}

