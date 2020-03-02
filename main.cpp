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
    int maxBalance = 1000000;
    int maxCents = .09;
    double maxInterestRate = 0.05;
    for (int i = 0; i < 100; ++i) {
        BankAccount account;
        account.setID(i);
        account.setBalance((rand() % maxBalance) + ((float)rand() / (RAND_MAX + maxCents)));
        account.setInterestRate((rand() / (RAND_MAX + maxInterestRate)));
        randomizer.add(account);
    }

    //cout << randomizer << endl;
    testLFshuffle(randomizer);

    return 0;
}

void testLFshuffle(Randomizer<BankAccount> randomizer) {
    vector<double> randomnessScores;
    for (int i = 0; i < 1000; ++i) {
        vector<BankAccount> shuffled = randomizer.LFshuffle();
        double randomness = randomizer.calculateRandomness(shuffled);
        randomnessScores.push_back(randomness);
        //cout << randomness << endl;
    }
    double meanRandomness = randomizer.calculateMean(randomnessScores);
    cout << "Mean Randomness = " << meanRandomness << endl;
}