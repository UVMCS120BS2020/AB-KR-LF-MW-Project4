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
    double balance;
    double interestRate;
public:
    BankAccount();
    BankAccount(double balance_, double interestRate_);

    double getBalance() const;

    void setBalance(double balance_);

    double getInterestRate() const;

    void setInterestRate(double interestRate_);

    double compoundInterest(double years);

    //Requires: BankAccount object (account)
    //Modifies: Nothing
    //Effects: Overloads output operator to print account
    friend ostream &operator<<(ostream &os, const BankAccount &account);

};



#endif //AB_KR_LF_MW_PROJECT4_BANKACCOUNT_H
