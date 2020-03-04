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
    unsigned long int KRshuffleSeed;

public:
    Randomizer() {
        LFshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        KRshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
    }

    /*
     * Sort
     * Requires:
     * Modifies:
     * Effects: returns the index of the object to be located
     */
    vector<T> sort(const vector<T> &unsortedList) {
        vector<T> sortedList = unsortedList;
        std::stable_sort(sortedList.begin(), sortedList.end());
        return sortedList;
    }

    /*
     * Find
     * Requires: T object
     * Modifies: Nothing
     * Effects: returns the index of the object to be located
     */
    int find(T object) {
        for (int i = 0; i < list.size(); i++) {
            if (object == list[i]) {
                return i;
            }
        }
        return -1;
    }


    /*
     * Austin Black's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
    vector<T> ABshuffle() {
        unsigned long int seed;
        vector<T> shuffled = list;
        double result = logisticMap(100, 0.4);
        result *= 1.0*pow(10,4);
        seed = (int)result;


        string seedToString = to_string(seed);
        cout << "seedToString = " << seedToString << endl;

        int seedSquared = pow(seed, 2);
        cout << "seedSquared = " << seedSquared << endl;

        string squaredToString = to_string(seedSquared);
        cout << "squaredToString = " << squaredToString << endl;

        int seedLength = seedToString.length();
        int squareLength = squaredToString.length();

        if (squareLength % 2 != 0) {
            squaredToString += "1";
        }
    }

    /*
     * Logistic Map Function
     * Requires:
     * Modifies:
     * Effects:
     */
    double logisticMap(int iter, double start) {
        vector<double> x (iter+1);
        x[0] = start;
        for (int i = 0; i < iter; i++) {
            x[i+1] = 4*x[i]*(1-x[i]);
        }
        return x[iter];
    }

    /*
     * Kai Morrissey's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
    vector<T> KRshuffle() {
        vector<T> out;
        for(T t : list) {
            out.insert(out.begin() + (out.size() == 0? 0 : (rand() % out.size())), t);
        }
        KRshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        return out;
    }

    /*
     * Luke Fredrickson's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
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

    /*
     * Megan Work's Algorithm
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns vector with indices randomly shuffled
     */
    vector<T> MWshuffle() {
        vector<T> shuffled = list;
        int size = shuffled.size();
        //for every element, swap with random element in remaining elements
        for(int i = 0; i < size - 1; ++i) {
            int j = i + rand() % (size - i);
            swap(shuffled[i], shuffled[j]);
        }
        return shuffled;
    }


    /*
     * Requires: a vector of scrambled versions of the original list vector (unique objects with equality operators)
     * Modifies: nothing
     * Effects: calculates a randomness score using the average of the standard error of relative distance traveled
     * by each element in the list from its unshuffled position to its shuffled position across n trials.
     * This score will change with different list sizes, as the standard error of sample means goes up as the number
     * of trials goes down. But using the same initial vector and the same sample size, this score can be used as a metric
     * for calculating relative randomness compared to other functions.
     */
    double calculateRandomness(const vector<vector<T>> &shuffledVectors) {
        // vector of all relative distances moved for each element in every trial
        vector<vector<double>> trialDistances;
        // for each shuffled vector, find the distance moved for each elem from the initial vector
        for(vector<T> vect : shuffledVectors) {
            vector<double> relativeDistances;
            // for each element in list, find its position in the shuffled vector
            for (int initIndex = 0; initIndex < list.size(); ++initIndex) {
                int finalIndex = -1;
                // search through shuffled vector for elem
                for (int i = 0; i < vect.size(); i++) {
                    if (list[initIndex] == vect[i]) {
                        finalIndex = i;
                    }
                }
                // if the object was found
                if (finalIndex != -1) {
                    // calculate how far it moved
                    double distance = abs(finalIndex - initIndex);
                    // divide by size of vector to obtain a relative distance moved
                    relativeDistances.push_back((distance / vect.size()) * 100);
                } else { // wasn't found
                    relativeDistances.push_back(0);
                }
            }
            trialDistances.push_back(relativeDistances);
        }
        // calculate the standard error of distance moved from original list to shuffled list
        // for each index position for all trials (SE of each column in the 2d vector)
        // overallStandardError is the mean of the SE of all columns.
        double overallStandardError = calculateStandardError(trialDistances);
        return overallStandardError;
    }

    // Requires: a 2d vector of doubles
    // Modifies: nothing
    // Effects: calculates the average of the standard errors of each column in a 2d vector of doubles.
    double calculateStandardError(const vector<vector<double>> &trialDistances) {
        // the standard error of each column in the provided 2d vector
        vector<double> colStandardErrors;
        // for each column push the relative distances onto a new vector
        for (int col = 0; col < trialDistances[col].size(); ++col) {
            vector<double> colDistances;
            for (int row = 0; row < trialDistances.size(); ++row) {
                colDistances.push_back(trialDistances[row][col]);
            }
            // calculate the standard error in the relative distance for each column
            // VAR = sqrt( sum((X-m)^2) / N ), where X = number in list, m = mean, N = count
            // SE = sqrt(VAR) / sqrt(N), where N = count
            double colMean = calculateMean(colDistances);
            double sumSquaredColDistances = 0;
            for (double num : colDistances) {
                sumSquaredColDistances += pow(((num - colMean)), 2);
            }
            double colVariance = sumSquaredColDistances / colDistances.size();
            double colStandardError = sqrt(colVariance) / sqrt(colDistances.size());
            colStandardErrors.push_back(colStandardError);
        }
        // calculate the mean standard error
        double meanSE = calculateMean(colStandardErrors);
        return meanSE;
    }

    /*
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the mean value of a vector of doubles
     */
    double calculateMean(const vector<double> &numbers) {
        double mean = 0;
        for (double num : numbers) {
            mean += num;
        }
        return mean /= numbers.size();
    }

    /*
     * GETTER(S)
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the mean value of a vector of doubles
     */
    const vector<T> &getList() const {
        return list;
    }

    /*
     * SETTER(S)
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the mean value of a vector of doubles
     */
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
