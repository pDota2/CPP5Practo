#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <locale>
using namespace std;

class BankAccount {
private:
	int accountNumber;
	double balance;
	double interestRate;
public:
	BankAccount(int number, double initialBalance) {
		this->accountNumber = number;
		this->balance = initialBalance;
		this->interestRate = 0.0;
	}
	void deposit(double amount) {
		if (amount > 0) {
			this->balance += amount;
		}
		else {
			throw invalid_argument("Нельзя внести отрицательную сумму или ноль");
		}
	}
	void withdraw(double amount) {
		if (amount > 0 && amount <= this->balance) {
			this->balance -= amount;
		}
		else {
			throw invalid_argument("Недостаточно средств на счете или неправильная сумма для снятия");
		}
	}
	double getBalance() {
		return this->balance;
	}
	double getInterest() {
		double monthlyInterest = this->balance * this->interestRate * (1.0 / 12);
		return monthlyInterest;
	}
	void setInterestRate(double rate) {
		if (rate >= 0) {
			this->interestRate = rate;
		}
		else {
			throw invalid_argument("Процентная ставка не может быть отрицательной");
		}
	}
	int getAccountNumber() {
		return this->accountNumber;
	}
	friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};
bool transfer(BankAccount& from, BankAccount& to, double amount) {
	try {
		from.withdraw(amount); 
		to.deposit(amount); 
		return true; 
	}
	catch (const invalid_argument& e) {
		cerr << "Ошибка перевода: " << e.what() << endl; 
		return false; 
	}
}
int main() {
	setlocale(LC_ALL, "Russian"); 
	BankAccount account1(111, 1000.0);
	BankAccount account2(222, 2000.0);
	account1.setInterestRate(0.05);
	account2.setInterestRate(0.03);
	double transferAmount = 500.0;
	bool transferStatus = transfer(account1, account2, transferAmount);
	cout << fixed << setprecision(2);
	if (transferStatus) {
		cout << "Перевод успешно выполнен\n";
		cout << "Баланс первого счета: " << account1.getBalance() << endl;
		cout << "Баланс второго счета: " << account2.getBalance() << endl;
	}
	else {
		cout << "Перевод не выполнен\n";
	}
	return 0;
}
