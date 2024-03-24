#include <iostream>
#include <Windows.h>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);

    double num[3][5];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> num[i][j];
		}
	}
	double sum = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sum += num[i][j];
		}
		cout << "Сторка: " << i + 1 << " - " << sum / 5 << endl;
		sum = 0;
	}
    
}

