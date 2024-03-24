#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

class BankAccount
{

private:
	int accountNumber; //номер банковского счёта
	double balance; //баланс
	double interestRate; //процентная ставка

public:
	BankAccount(int accountNumber, double balance) { //конструктор
		this->accountNumber = accountNumber;
		this->balance = balance;
		interestRate = 0;
	}
	void deposit(double value) { //внести средства на счет
		balance = (value > 0) ? balance + value : balance;
	}
	void withdraw(double value) { //снять средства со счета
		balance = (value < balance && value > 0) ? balance - value : balance;
	}
	double getBalance() { //вернуть текущий баланс 
		return balance;
	}
	double getInterest() { //рассчет и возвращение суммы процентов, заработанных на счете
		return balance * interestRate * (1.0 / 12.0);
	}
	void setInterestRate(double interestRate) {//обновить процентную ставку
		this->interestRate = (interestRate >= 0) ? interestRate : this->interestRate;
	}
	int getAccountNumber() { //получить номер банковского счёта
		return accountNumber;
	}

	friend bool transfer(BankAccount& akk1, BankAccount& akk2, double value); //дружественная функция
};

bool transfer(BankAccount& akk1, BankAccount& akk2, double value) { //перевод средств
	if (akk1.balance >= value) {
		akk1.balance -= value;
		akk2.balance += value;
		return true;
	}
	return false;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	vector <BankAccount> bankAccounts;
	int menu = 0;
	int number = 0;
	do {
		cout << "1. Создать счёт" << endl;
		cout << "2. Все счета" << endl;
		cout << "3. Внести средства на счёт" << endl;
		cout << "4. Снять средства со счёта" << endl;
		cout << "5. Получение баланса" << endl;
		cout << "6. Получение процентов" << endl;
		cout << "7. Обновить процентную ставку" << endl;
		cout << "8. Получить номер банковского счёта" << endl;
		cout << "9. Перевод средств" << endl;
		cout << "10. Выход" << endl;
		cout << "Выберите действие: ";
		cin >> menu;
		switch (menu)
		{
		case 1: {
			number = 0;
			int accountNumber;
			cout << "Введите номер счёта: ";
			cin >> accountNumber;
			bool prov = true;
			for (BankAccount item : bankAccounts) {
				if (item.getAccountNumber() == accountNumber) {
					cout << "Такой счёт уже есть" << endl;
					prov = false;
					break;
				}
			}
			if (!prov) {
				break;
			}
			double balance;
			cout << "Введите начальный баланс: ";
			cin >> balance;
			if (balance >= 0 && accountNumber >= 0) {
				BankAccount bankAccount(accountNumber, balance);
				bankAccounts.emplace_back(bankAccount);
			}
			else {
				cout << "Значение не должно быть меньше нуля" << endl;
			}
			break;
		}
		case 2: {
			int i = 1;
			for (BankAccount item : bankAccounts) {
				cout << "Номер " << i << " счёта: " << item.getAccountNumber() << endl;
				i++;
			}
			cout << "Выберите счёт с которым будете работать: ";
			int num;
			cin >> num;
			if (num > 0 && num <= bankAccounts.size()) {
				number = num;
			}
			break;
		}
		case 3: {
			if (number != 0) {
				double value;
				cout << "Введите значение: ";
				cin >> value;
				bankAccounts[number - 1].deposit(value);
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
			break;
		}
		case 4: {
			if (number != 0) {
				double value;
				cout << "Введите значение: ";
				cin >> value;
				bankAccounts[number - 1].withdraw(value);
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
			break;
		}
		case 5: {
			if (number != 0) {
				cout << "Баланс: " << bankAccounts[number - 1].getBalance() << endl;
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
			break;
		}
		case 6: {
			if (number != 0) {
				cout << "Проценты: " << bankAccounts[number - 1].getInterest() << endl;
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
			break;
		}
		case 7: {
			if (number != 0) {
				double value;
				cout << "Введите значение: ";
				cin >> value;
				bankAccounts[number - 1].setInterestRate(value);
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
			break;
		}
		case 8: {
			if (number != 0) {
				cout << "Номер аккаунта: " << bankAccounts[number - 1].getAccountNumber() << endl;
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
			break;
		}
		case 9: {
			int i = 1;
			if (number != 0) {
				for (BankAccount item : bankAccounts) {
					cout << "Номер " << i << " счёта: " << item.getAccountNumber() << endl;
					i++;
				}
				int num = 0;
				cout << "Выберите кому переводить: ";
				cin >> num;
				if (num > 0 && num <= bankAccounts.size()) {
					double value;
					cout << "Введите сколько переводить: ";
					cin >> value;
					transfer(bankAccounts[number - 1], bankAccounts[num - 1], value);
				}
			}
			else {
				cout << "Счёт не выбран" << endl;
			}
		}
			  break;
		default: {
			cout << "Такой команды нет";
			break;
		}
		}
	} while (menu != 10);
}