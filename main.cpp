#include "bankAccount.h"
#include <iostream>
#include <ctime>
#include <random>
#include "Randomizer.h"
#include <vector>
using namespace std;

void testBaseline(Randomizer<BankAccount> randomizer);
void testCppShuffle(Randomizer<BankAccount> randomizer);
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

    testBaseline(randomizer);
    testCppShuffle(randomizer);
    testLFshuffle(randomizer);

    return 0;
}

void testBaseline(Randomizer<BankAccount> randomizer) {
    vector<vector<BankAccount>> reversedVectors;
    vector<BankAccount> vect = randomizer.sort(randomizer.getList());
    reverse(vect.begin(),vect.end());
    for (int i = 0; i < 1000; ++i) {
        reversedVectors.push_back(vect);
    }
    double randomness = randomizer.calculateRandomness(reversedVectors);
    cout << "Reversed Randomness = " << randomness << endl;
}

void testCppShuffle(Randomizer<BankAccount> randomizer) {
    vector<vector<BankAccount>> shuffledVectors;
    for (int i = 0; i < 1000; ++i) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        vector<BankAccount> vect = randomizer.getList();
        shuffle(vect.begin(), vect.end(), std::default_random_engine(seed));
        shuffledVectors.push_back(vect);
    }
    double randomness = randomizer.calculateRandomness(shuffledVectors);
    cout << "C++shuffle Randomness = " << randomness << endl;
}

void testLFshuffle(Randomizer<BankAccount> randomizer) {
    vector<vector<BankAccount>> shuffledVectors;
    for (int i = 0; i < 1000; ++i) {
        vector<BankAccount> shuffled = randomizer.LFshuffle();
        shuffledVectors.push_back(shuffled);
    }
    double randomness = randomizer.calculateRandomness(shuffledVectors);
    cout << "LFshuffle Randomness = " << randomness << endl;
}
