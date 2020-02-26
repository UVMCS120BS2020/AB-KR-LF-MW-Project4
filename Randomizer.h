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

    //Shuffles should return own copies of shuffled vector, not void
    //That way they can be compared together at the same time

    void ABshuffle();

    void KRshuffle();

    void LFshuffle();

    void MWshuffle();

    const vector<T> &getList() const {
        return list;
    }

    void setList(const vector<T> &list_) {
        list = list_;
    }

    void add(T push) {
        list.push_back(push);
    }

    T get(int index) {
        return list[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const Randomizer<T> &randomizer);
};




#endif //AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
