#include <iostream>
#include <ctime>
#include "bankAccount.h"
#include "Randomizer.h"
#include <vector>
using namespace std;

void testLFshuffle(Randomizer<BankAccount> randomizer);

int main() {
    Randomizer<BankAccount> randomizer;
    time_t now = time(0);
    srand(now);

    //Generate vector of multiple accounts with appropriate fields
    double maxBalance = 1000000.0;
    double maxInterestRate = 0.05;
    for (int i = 0; i < 10; ++i) {
        BankAccount account;
        account.setID(i);
        account.setBalance((rand() / (RAND_MAX + maxBalance)));
        account.setInterestRate((rand() / (RAND_MAX + maxInterestRate)));
        randomizer.add(account);
    }

    testLFshuffle(randomizer);




    return 0;
}

void testLFshuffle(Randomizer<BankAccount> randomizer) {
    vector<double> standardDeviations;
    for (int i = 0; i < 100; ++i) {
        vector<BankAccount> shuffled = randomizer.LFshuffle();
        standardDeviations.push_back(randomizer.calculateRandomness(shuffled));
    }
    double meanStandardDeviation = randomizer.calculateMean(standardDeviations);
    cout << "Mean SD = " << meanStandardDeviation << endl;
}
