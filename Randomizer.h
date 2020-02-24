//
// Created by ironi on 2/24/2020.
//

#ifndef AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
#define AB_KR_LF_MW_PROJECT4_RANDOMIZER_H

#include <vector>
#include <ostream>

using namespace std;

template <class T>
class Randomizer {
    vector<T> list;

public:
    void sort();
    void find(T object);

    void ABshuffle();

    void KRshuffle();

    void LFshuffle();

    void MWshuffle();

    friend std::ostream &operator<<(std::ostream &os, const Randomizer &randomizer) {
        return os;
    }
};


#endif //AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
