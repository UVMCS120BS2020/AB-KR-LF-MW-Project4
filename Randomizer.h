//
// Created by ironi on 2/24/2020.
//

#ifndef AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
#define AB_KR_LF_MW_PROJECT4_RANDOMIZER_H

#include <cmath>
#include <ostream>
#include <vector>

using namespace std;


template <class T>
class Randomizer {

    vector<T> list;

public:
    vector<T> sort(const vector<T> &unsortedList) {
        return nullptr;
    }

    // returns the index of the object to be located
    int find(T object) {
        for (int i = 0; i < list.size(); i++) {
            if (object == list[i]) {
                return i;
            }
        }
        return -1;
    }

    //Shuffles should return own copies of shuffled vector, not void
    //That way they can be compared together at the same time

    vector<T> ABshuffle();

    vector<T> KRshuffle();

    vector<T> LFshuffle();

    vector<T> MWshuffle();


    // Requires: a scrambled version of the list vector (unique objects which possess equality operators)
    // Modifies: nothing
    // Effects: calculates the standard deviation of distance traveled by each object from its initial position in list
    double calculateRandomness(const vector<T> &randomizedList) {
        vector<double> distances;
        // find the distance each object in the randomizedList has moved from its position in list
        for (int endPos = 0; endPos < randomizedList.size(); endPos++) {
            int startPos = find(randomizedList[endPos]);
            // if the object is in list calculate and push back how far it moved
            if (startPos != -1) {
                double distance = abs(endPos - startPos);
                distances.push_back(distance);
            }
        }
        return calculateStandardDeviation(distances);
    }

    // Requires: a vector of doubles
    // Modifies: nothing
    // Effects: calculates the standard deviation of a vector of doubles
    double calculateStandardDeviation(const vector<double> &numbers) {
        // SD = sqrt( sum((X-m)^2) / N ) , where X = number in list, m = mean, N = count of numbers
        double mean = calculateMean(numbers);
        double sumSquaredDistances = 0;
        for (double num : numbers) {
            sumSquaredDistances += pow((num - mean), 2);
        }
        double variance = sumSquaredDistances / numbers.size();
        return sqrt(variance);
    }

    // Requires: a vector of doubles
    // Modifies: nothing
    // Effects: calculates the mean value of a vector of doubles
    double calculateMean(const vector<double> &numbers) {
        double mean = 0;
        for (double num : numbers) {
            mean += num;
        }
        return mean /= numbers.size();
    }

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
