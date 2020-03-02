#include "bankAccount.h"
#include <iostream>
#include <ctime>
#include <random>
#include "Randomizer.h"
#include <vector>
using namespace std;

vector<BankAccount> generateBankAccounts(int numBankAccounts);
void testShuffleMethods(Randomizer<BankAccount> &randomizer, int numTrials);
double testBaseline(Randomizer<BankAccount> &randomizer, int numTrials);
double testCppShuffle(Randomizer<BankAccount> &randomizer, int numTrials);
double testLFshuffle(Randomizer<BankAccount> &randomizer, int numTrials);

int main() {
    time_t now = time(0);
    srand(now);

    //populate randomizer
    Randomizer<BankAccount> randomizer;
    vector<BankAccount> accounts1 = generateBankAccounts(10);
    vector<BankAccount> accounts2 = generateBankAccounts(25);
    vector<BankAccount> accounts3 = generateBankAccounts(50);
    randomizer.setList(accounts1);

    int numTrials = 100;

    cout << "\n10 ACCOUNTS" << endl;
    testShuffleMethods(randomizer, numTrials);
    cout << "\n25 ACCOUNTS" << endl;
    randomizer.setList(accounts2);
    testShuffleMethods(randomizer, numTrials);
    cout << "\n50 ACCOUNTS" << endl;
    randomizer.setList(accounts3);
    testShuffleMethods(randomizer, numTrials);

    return 0;
}

vector<BankAccount> generateBankAccounts(int numBankAccounts) {
    vector<BankAccount> accounts;
    int maxBalance = 1000000;
    double maxCents = 0.09;
    double maxInterestRate = 0.05;
    for (int i = 0; i < numBankAccounts; ++i) {
        BankAccount account;
        account.setID(i);
        account.setBalance((rand() % maxBalance) + ((float)rand() / (RAND_MAX + maxCents)));
        account.setInterestRate((rand() / (RAND_MAX + maxInterestRate)));
        accounts.push_back(account);
    }
    return accounts;
}

void testShuffleMethods(Randomizer<BankAccount> &randomizer, int numTrials) {
    double baselineRandomness = testBaseline(randomizer, numTrials);
    double cppRandomness = testCppShuffle(randomizer, numTrials);
    double LFRandomness = testLFshuffle(randomizer, numTrials);
    cout << "Randomness for " << numTrials << " trials:" << endl;
    cout << "non-rand =\t" << baselineRandomness << endl;
    cout << "c++-rand =\t" << cppRandomness << endl;
    cout << "LF-rand =\t" << LFRandomness << endl;
}

double testBaseline(Randomizer<BankAccount> &randomizer, int numTrials) {
    vector<vector<BankAccount>> reversedVectors;
    vector<BankAccount> vect = randomizer.sort(randomizer.getList());
    reverse(vect.begin(),vect.end());
    for (int i = 0; i < numTrials; ++i) {
        reversedVectors.push_back(vect);
    }
    return randomizer.calculateRandomness(reversedVectors);
}

double testCppShuffle(Randomizer<BankAccount> &randomizer, int numTrials) {
    vector<vector<BankAccount>> shuffledVectors;
    for (int i = 0; i < numTrials; ++i) {
        unsigned seed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        vector<BankAccount> vect = randomizer.getList();
        shuffle(vect.begin(), vect.end(), std::default_random_engine(seed));
        shuffledVectors.push_back(vect);
    }
    return randomizer.calculateRandomness(shuffledVectors);
}

double testLFshuffle(Randomizer<BankAccount> &randomizer, int numTrials) {
    vector<vector<BankAccount>> shuffledVectors;
    for (int i = 0; i < numTrials; ++i) {
        vector<BankAccount> shuffled = randomizer.LFshuffle();
        shuffledVectors.push_back(shuffled);
    }
    return randomizer.calculateRandomness(shuffledVectors);
}
