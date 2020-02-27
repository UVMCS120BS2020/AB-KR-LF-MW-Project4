//
// Created by Megan on 2/24/2020.
//

#include "bankAccount.h"
#include <iomanip>
#include <iostream>


BankAccount::BankAccount() : id(0), balance(0.0), interestRate(0.01) {}

BankAccount::BankAccount(int id) : id(id), balance(0.0), interestRate(0.01) {}

BankAccount::BankAccount(double balance, double interestRate) : id(0),
balance(balance), interestRate(interestRate) {}

int BankAccount::getID() const {
    return id;
}

void BankAccount::setID(int id_) {
    id = id_;
}

BankAccount::BankAccount(int id, double balance, double interestRate) :
    id(id), balance(balance), interestRate(interestRate) {}

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
    os << "\tID: " << account.id <<  "\tAccount Balance: $" << account.balance
    << "\tAccount Interest Rate: " << setprecision(2) << fixed << account.interestRate;
    return os;
}

bool BankAccount::operator<(const BankAccount &rhs) const {
    return id < rhs.id;
}

bool BankAccount::operator>(const BankAccount &rhs) const {
    return id > rhs.id;
}

bool BankAccount::operator<=(const BankAccount &rhs) const {
    return id <= rhs.id;
}

bool BankAccount::operator>=(const BankAccount &rhs) const {
    return id >= rhs.id;
}

bool BankAccount::operator==(const BankAccount &rhs) const {
    return id == rhs.id;
}

bool BankAccount::operator!=(const BankAccount &rhs) const {
    return !(rhs == *this);
}


