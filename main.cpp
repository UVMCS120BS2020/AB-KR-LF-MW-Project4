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
    for (int i = 0; i < 10; i ++) {
        BankAccount account;
        account.setID(i);
        account.setBalance(rand() % 10000);
        account.setInterestRate(rand() / RAND_MAX);
        randomizer.add(account);
    }

    return 0;
}
