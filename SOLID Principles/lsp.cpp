
#include <iostream>
using namespace std;

class Account {
protected:
    double balance;
    int account_number;

public:
    Account(int account_number, double balance) {
        this->account_number = account_number;
        this->balance = balance;
    }

    void getBalance() {
        cout << "Balance in account number "
             << account_number << ": " << balance << endl;
    }

    void getAccountNumber() {
        cout << "Account number: " << account_number << endl;
    }

    virtual ~Account() {}
};

class NonWithdrewableAccount : public Account {
public:
    NonWithdrewableAccount(int account_number, double balance)
        : Account(account_number, balance) {}

    virtual void deposit(double amount) = 0;
};

class WithdrewableAccount : public NonWithdrewableAccount {
public:
    WithdrewableAccount(int account_number, double balance)
        : NonWithdrewableAccount(account_number, balance) {}

    virtual void withdraw(double amount) = 0;
};

class SavingsAccount : public WithdrewableAccount {
public:
    SavingsAccount(int account_number, double balance)
        : WithdrewableAccount(account_number, balance) {}

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "Invalid deposit amount\n";
            return;
        }

        balance += amount;

        cout << "Deposited " << amount
             << ". New balance: " << balance << endl;
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient balance\n";
            return;
        }

        balance -= amount;

        cout << "Withdrawn " << amount
             << ". New balance: " << balance << endl;
    }
};

class CreditAccount : public NonWithdrewableAccount {
public:
    CreditAccount(int account_number, double balance)
        : NonWithdrewableAccount(account_number, balance) {}

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "Invalid deposit amount\n";
            return;
        }

        balance += amount;

        cout << "Deposited " << amount
             << ". New balance: " << balance << endl;
    }
};

class FixedDepositAccount : public NonWithdrewableAccount {
public:
    FixedDepositAccount(int account_number, double balance)
        : NonWithdrewableAccount(account_number, balance) {}

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "Invalid deposit amount\n";
            return;
        }

        balance += amount;

        cout << "Deposited " << amount
             << ". New balance: " << balance << endl;
    }
};

int main() {
    SavingsAccount s1(101, 5000);
    CreditAccount c1(102, 10000);
    FixedDepositAccount f1(103, 20000);

    s1.getAccountNumber();
    s1.getBalance();
    s1.deposit(2000);
    s1.withdraw(1000);

    cout << "\n";

    c1.getBalance();
    c1.deposit(5000);

    cout << "\n";

    f1.getBalance();
    f1.deposit(3000);

    return 0;
}
