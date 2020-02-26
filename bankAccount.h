//
// Created by Megan on 2/24/2020.
//

#ifndef AB_KR_LF_MW_PROJECT4_BANKACCOUNT_H
#define AB_KR_LF_MW_PROJECT4_BANKACCOUNT_H

#include <cmath>
#include <iostream>

using namespace std;

class BankAccount {
private:
    // Fields
    // the index of the bank account in a vector.
    // (useful for measuring randomness.)
    unsigned int id;
    // the total balance of the account
    double balance;
    // the interest rate of the account
    double interestRate;
public:
    // Constructors
    BankAccount();

    explicit BankAccount(int id);

    // Requires: non-negative doubles
    // Modifies: fields
    // Effects: creates a bankAccount object
    BankAccount(double balance_, double interestRate_);

    BankAccount(int id, double balance, double interestRate);

    // getters
    // Requires: nothing
    // Modifies: nothing
    // Effects: returns field
    double getBalance() const;
    double getInterestRate() const;
    int getID() const;

    // setters
    // Requires: non-negative double or int
    // Modifies: fields
    // Effects: sets fields
    void setInterestRate(double interestRate_);
    void setBalance(double balance_);
    void setID(int id);


    // Requires: non-negative number
    // Modifies: balance
    // Effects: increments balance by continuously compounding for n years, returns interest gained.
    double compoundInterest(double numYears);

    //Requires: BankAccount object (account)
    //Modifies: Nothing
    //Effects: Overloads output operator to print account
    friend ostream &operator<<(ostream &os, const BankAccount &account);

    bool operator<(const BankAccount &rhs) const;

    bool operator>(const BankAccount &rhs) const;

    bool operator<=(const BankAccount &rhs) const;

    bool operator>=(const BankAccount &rhs) const;

};



#endif //AB_KR_LF_MW_PROJECT4_BANKACCOUNT_H
