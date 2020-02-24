//
// Created by Megan on 2/24/2020.
//

#include "bankAccount.h"


BankAccount::BankAccount() {
    this->balance = 0.0;
    this->interestRate = 0.01;
}

BankAccount::BankAccount(double balance_, double interestRate_) {
    this->balance = balance_;
    this->interestRate = interestRate_;
}

double BankAccount::getBalance() const {
    return balance;
}

void BankAccount::setBalance(double balance_) {
    this->balance = balance_;
}

double BankAccount::getInterestRate() const {
    return interestRate;
}

void BankAccount::setInterestRate(double interestRate_) {
    this->interestRate = interestRate_;
}

double BankAccount::compoundInterest(double numYears) {
    double interest = balance*pow(M_E, interestRate*numYears);
    balance += interest;
    return interest;
}

ostream &operator<<(ostream &os, const BankAccount &account) {
    os << "Account Balance: " << account.balance << " Account's Interest Rate: " << account.interestRate;
    return os;
}

bool BankAccount::operator<(const BankAccount &rhs) const {
    return balance < rhs.balance;
}

bool BankAccount::operator>(const BankAccount &rhs) const {
    return balance > rhs.balance;
}

bool BankAccount::operator<=(const BankAccount &rhs) const {
    return balance <= rhs.balance;
}

bool BankAccount::operator>=(const BankAccount &rhs) const {
    return balance >= rhs.balance;
}
