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
    /*
     * Fields
     */
    // the index of the bank account in a vector.
    // (useful for measuring randomness.)
    unsigned int id;
    // the total balance of the account
    double balance;
    // the interest rate of the account
    double interestRate;
public:
    /*
     * Constructors
     */
    BankAccount();
    /*
     * Requires: An integer
     * Modifies: id field
     * Effects: Creates a bankAccount object with a given id.
     */
    explicit BankAccount(int id);

    /*
     * Requires: Non-negative doubles
     * Modifies: balance and interestRate fields
     * Effects: Creates a bankAccount object with given balance and interestRate fields.
     */
    BankAccount(double balance_, double interestRate_);

    /*
     * Requires: An integer and non-negative doubles
     * Modifies: id, balance, and interestRate fields
     * Effects: Creates a bankAccount object with given id, balance, and interestRate fields.
     */
    BankAccount(int id, double balance, double interestRate);

    /*
     * Getters
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns respective field.
     */
    double getBalance() const;
    double getInterestRate() const;
    int getID() const;

    /*
     * Setters
     * Requires: Non-negative double, integer
     * Modifies: Fields
     * Effects: Sets fields to respective values.
     */
    void setInterestRate(double interestRate_);
    void setBalance(double balance_);
    void setID(int id);

    /*
     * Requires: Non-negative double
     * Modifies: balance
     * Effects: increments balance by continuously compounding for n years, returns interest gained.
     */
    double compoundInterest(double numYears);

    /*
     * Overloaded Operators
     */
    friend ostream &operator <<(ostream &os, const BankAccount &account);
    bool operator ==(const BankAccount &rhs) const;
    bool operator !=(const BankAccount &rhs) const;
    bool operator <(const BankAccount &rhs) const;
    bool operator >(const BankAccount &rhs) const;
    bool operator <=(const BankAccount &rhs) const;
    bool operator >=(const BankAccount &rhs) const;
};



#endif //AB_KR_LF_MW_PROJECT4_BANKACCOUNT_H