#include <iostream>
#include <ctime>
#include "bankAccount.h"
#include "Randomizer.h"
#include <vector>
using namespace std;

int main() {
    Randomizer<BankAccount> randomizer;
    time_t now = time(0);
    srand(now);

    //Generate vector of multiple accounts with appropriate fields
    double maxBalance = 1000000.0;
    double maxInterestRate = 0.05;
    for (int i = 10; i > 0; --i) {
        BankAccount account;
        account.setID(i);
        account.setBalance((rand() / (RAND_MAX + maxBalance)));
        account.setInterestRate((rand() / (RAND_MAX + maxInterestRate)));
        randomizer.add(account);
    }

    //randomizer.LFshuffle();


    return 0;
}
