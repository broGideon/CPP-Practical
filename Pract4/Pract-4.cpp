#include <iostream>
#include <string>
#include "Pract-4.h"
#include <Windows.h>
#include <algorithm>
#include <random>
using namespace std;

string reverse(string text) {
	string reverseText = "";
	for (int i = text.length() - 1; i >= 0; i--) {
		reverseText = reverseText + text[i];
	}
	return reverseText;
}

string removeVowels(string text) {
	string returnText = "";
	string a = "aeiouyAEIOUYуеаоэяиюУЕАОЭЯИЮ";
	bool prov = true;
	for (char item : text) {
		for (char i : a) {
			if (item == i) {
				prov = false;
			}
		}
		if (prov == true) {
			returnText = returnText + item;
		}
		prov = true;
	}
	return returnText;
}

string removeConsonants(string text) {
	string returnText = "";
	string a = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyzбвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШ";
	bool prov = true;
	for (char item : text) {
		for (char i : a) {
			if (item == i) {
				prov = false;
			}
		}
		if (prov == true) {
			returnText = returnText + item;
		}
		prov = true;
	}
	return returnText;
}
string shuffleText(string text) {
	random_device rd;
	mt19937 g(rd());
	shuffle(text.begin(), text.end(), g);
	return text;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	int menu;
	cout << "1.Слово выводится задом наперед.\n2.Вывести слово без гласных.\n3.Вывести слово без согласных.\n4. Рандомно раскидывать буквы заданного слова." << endl;
	cin >> menu;

	string text;
	cout << "Введите текст: ";
	cin >> text;

	switch (menu)
	{
	case 1:
		cout << reverse(text) << endl;
		break;
	case 2:
		cout << removeVowels(text) << endl;
		break;
	case 3:
		cout << removeConsonants(text) << endl;
		break;
	case 4:
		cout << shuffleText(text) << endl;
		break;
	}
}
