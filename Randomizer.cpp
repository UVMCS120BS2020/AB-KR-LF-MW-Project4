//
// Created by ironi on 2/24/2020.
//

#include "Randomizer.h"

template<class T>
const vector<T> &Randomizer<T>::getList() const {
    return list;
}

template<class T>
void Randomizer<T>::setList(const vector<T> &list) {
    Randomizer::list = list;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Randomizer<T> &randomizer) {
    return os;
}

template<class T>
void Randomizer<T>::add(T push) {
    list.push_back(push);
}

template<class T>
T Randomizer<T>::get(int index) {
    return list[index];
}
