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

    /*
     * Default Constructor
     */
    Randomizer() {
        LFshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        KRshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
    }

    /*
     * Sort
     * Requires: A vector of template objects
     * Modifies: Nothing
     * Effects: returns the index of the object to be located.
     */
    vector<T> sort(const vector<T> &unsortedList) {
        vector<T> sortedList = unsortedList;
        std::stable_sort(sortedList.begin(), sortedList.end());
        return sortedList;
    }

    /*
     * Find
     * Requires: A template object
     * Modifies: Nothing
     * Effects: returns the index of the object to be located.
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
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns a vector of template objects. It contains all of objects in
     *          in the list field of this class, but arranged randomly.
     */
    vector<T> ABshuffle() {
        vector<T> shuffled = list;
        unsigned long int seed;

        seed = chrono::duration_cast<chrono::nanoseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        seed /= pow(10,7);

        for (int i = 0; i < shuffled.size(); i++) {
            double result = logisticMap(seed, 0.663);
            result *= 1.0 * pow(10, 5);
            seed = (int) result;

            string seedToString = to_string(seed);
            unsigned long int seedSquared = pow(seed, 2);
            string squaredToString = to_string(seedSquared);

            if (squaredToString.length() % seedToString.length() != 0) {
                while (squaredToString.length() % seedToString.length() != 0) {
                    squaredToString += to_string(seed % 10);
                }
            }

            int seedLength = seedToString.length();
            int squareLength = squaredToString.length();
            string middle = squaredToString.substr((squareLength / 2) - (seedLength / 2), seedLength);
            seed = stoi(middle);

            int j = seed % shuffled.size();
            T temp = shuffled[i];
            shuffled[i] = shuffled[j];
            shuffled[j] = temp;
        }
        return shuffled;
    }

    /*
     * Logistic Map
     * Requires: An integer and a double.
     * Modifies: Nothing
     * Effects: Calculates the output of the logistic map Xn+1 = r(Xn)(1-Xn)
     *          after (iter) iterations, for a given initial point (initial).
     *          (chaotic for ~3.57 < r <= 4)
     */
    double logisticMap(int iter, double initial) {
        vector<double> x (iter+1);
        double r = 4.0;
        x[0] = initial;
        for (int i = 0; i < iter; i++) {
            x[i+1] = r*x[i]*(1-x[i]);
        }
        return x[iter];
    }

    /*
     * Kai Morrissey's Algorithm
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns a vector of template objects (from the list field) arranged randomly.
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
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns a vector of template objects (from the list field) in a random arrangement.
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
     * Effects: Returns vector with indices randomly shuffled.
     */
    vector<T> MWshuffle() {
        vector<T> shuffled = list;
        int size = shuffled.size();
        // For every element, swap with random element in remaining elements.
        for(int i = 0; i < size - 1; ++i) {
            int j = i + rand() % (size - i);
            swap(shuffled[i], shuffled[j]);
        }
        return shuffled;
    }


    /*
     * Requires: A vector of scrambled versions of the original list vector (unique objects with equality operators)
     * Modifies: Nothing
     * Effects: Calculates a randomness score using the average of the standard error of relative distance traveled
     *          by each element in the list from its unshuffled position to its shuffled position across n trials.
     *          This score will change with different list sizes, as the standard error of sample means goes up as the number
     *          of trials goes down. But using the same initial vector and the same sample size, this score can be used as a metric
     *          for calculating relative randomness compared to other functions.
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
        double overallStandardError = calculateAverageColumnStandardError(rotate2DVector(trialDistances));
        return overallStandardError;
    }

    /*
     * Rotate 2D Vector
     * Requires: 2D vector
     * Modifies: Nothing
     * Effects: Transposes the vector so rows swap with columns.
     */
    vector<vector<double>> rotate2DVector(const vector<vector<double>> &vect) {
        vector<vector<double>> rotated;
        for (int col = 0; col < vect[col].size(); ++col) {
            vector<double> rows;
            for (const auto & row : vect) {
                rows.push_back(row[col]);
            }
            rotated.push_back(rows);
        }
        return rotated;
    }

    /*
     * Calculate Average Column Standard Error
     * Requires: A 2D vector of doubles
     * Modifies: Nothing
     * Effects: Calculates the average of the standard errors of each column in a 2d vector of doubles.
     */
    double calculateAverageColumnStandardError(const vector<vector<double>> &vect) {
        // the standard error of each column in the provided 2d vector
        vector<double> colStandardErrors;
        for(const vector<double> &column : vect) {
            colStandardErrors.push_back(calculateStandardError(column));
        }
        // calculate the mean standard error
        double meanSE = calculateMean(colStandardErrors);
        return meanSE;
    }

    /*
     * Calculate Standard Error
     * Requires: A vector of doubles
     * Modifies: Nothing
     * Effects: Calculates the standard error of a vector of doubles.
     */
    double calculateStandardError(const vector<double> &vect) {
        // calculate the standard error in the relative distance for each column
        // VAR = sqrt( sum((X-m)^2) / N ), where X = number in list, m = mean, N = count
        // SE = sqrt(VAR) / sqrt(N), where N = count
        double colMean = calculateMean(vect);
        double sumSquaredColDistances = 0;
        for (const double &num : vect) {
            sumSquaredColDistances += pow(((num - colMean)), 2);
        }
        double colVariance = sumSquaredColDistances / vect.size();
        double colStandardError = sqrt(colVariance) / sqrt(vect.size());
        return colStandardError;
    }

    /*
     * Calculate Mean
     * Requires: A vector of doubles
     * Modifies: Nothing
     * Effects: Calculates the mean value of a vector of doubles.
     */
    double calculateMean(const vector<double> &numbers) {
        double mean = 0;
        for (const double &num : numbers) {
            mean += num;
        }
        return mean /= numbers.size();
    }

    /*
     * Getter(s)
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Returns value(s) of the class field(s).
     */
    const vector<T> &getList() const {
        return list;
    }

    /*
     * Setter(s)
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: Sets value(s) of the class field(s) to the input value(s).
     */
    void setList(const vector<T> &list_) {
        list = list_;
    }

    /*
     * Add
     * Requires: Template object
     * Modifies: Nothing
     * Effects: Pushes input object into field vector.
     */
    void add(T push) {
        list.push_back(push);
    }

    /*
     * Get
     * Requires: An integer
     * Modifies: Nothing
     * Effects: Returns template object contained at a given index within field vector.
     */
    T get(int index) {
        return list[index];
    }

    /*
     * Overloaded Operator(s)
     */
    friend std::ostream &operator<<(std::ostream &os, const Randomizer<T> &randomizer) {
        for(T obj : randomizer.list) {
            os << obj << endl;
        }
        return os;
    }
};




#endif //AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
