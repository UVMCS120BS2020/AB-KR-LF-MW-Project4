#include <iostream>
#include <ctime>
#include "bankAccount.h"
#include "Randomizer.h"
using namespace std;

int main() {
    time_t now = time(0);
    srand(now);

    for (int i = 0; i < 10; i ++) {
        BankAccount account;
        account.setBalance(rand() % 10000);
        account.setInterestRate(rand() / RAND_MAX);
        list.pushback(account)

    }
    //BankAccount(1000, .05);

    return 0;
}
