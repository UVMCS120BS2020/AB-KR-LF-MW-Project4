//
// Created by ironi on 2/24/2020.
//

#ifndef AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
#define AB_KR_LF_MW_PROJECT4_RANDOMIZER_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ostream>
#include <vector>

using namespace std;


template <class T>
class Randomizer {
private:
    vector<T> list;
    unsigned long int LFshuffleSeed;

public:
    vector<T> sort(const vector<T> &unsortedList) {
        vector<T> sortedList = unsortedList;
        std::stable_sort(sortedList.begin(), sortedList.end());
        return sortedList;
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

    vector<T> KRshuffle(){
        vector<T> out;
        for(T t : list){
            out.insert(out.begin() + (out.size() == 0? 0 : (rand() % out.size())), t);
        }

        LFshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();

        return out;
    }

    vector<T> LFshuffle() {
        vector<T> scrambled = list;
        unsigned long int first = 1;
        unsigned long int second = LFshuffleSeed;
        unsigned long int current;
        for (int i = 0; i < scrambled.size(); ++i) {
            current = first + second;
            first = second;
            second = current;
            int j = current % scrambled.size();
            // swap objects from current index to random index
            T temp = scrambled[j];
            scrambled[j] = scrambled[i];
            scrambled[i] = temp;
            // update seed
            LFshuffleSeed = current;
        }
        return scrambled;
    }

    vector<T> MWshuffle() {
        vector<T> shuffled = list;


        return shuffled;
    }


    // Requires: a scrambled version of the list vector (unique objects which possess equality operators)
    // Modifies: nothing
    // Effects: calculates a randomness score by taking the standard deviation of distance traveled by each object from
    //          its initial position in list and dividing that by the total size of the list;
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
        return (calculateStandardDeviation(distances) / randomizedList.size());
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

    friend std::ostream &operator<<(std::ostream &os, const Randomizer<T> &randomizer) {
        for(T obj : randomizer.list) {
            os << obj << endl;
        }
        return os;
    }
};




#endif //AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
