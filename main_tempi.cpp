/*
*/

// LIBRERIE
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <chrono>
#include <random>
#include "alberi.cpp"
#include "AVL.cpp"
#include "BST.cpp"
#include "RBT.cpp"

using namespace std;
using namespace std::chrono;

// DICHIARAZIONE COSTANTI
const int A = 1000;
const double B = exp((log(1000000)-log(1000))/99);
const int N = 20;

// DICHIARAZIONE FUNZIONI
double getResolution();
double getTmin();
double getFinalTime(double[], int);
template<class TreeType> int calcAvgTime();
template<class TreeType> int calcStdDev();


random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(1, 1000000000);


unsigned int pseudoRand(){ // genera in modo pseudo casuale un valore k
    return distrib(gen);
}


int main() {
    calcStdDev<AVL>();
}

template<class TreeType> int calcAvgTime() {
    for(int i = 0; i < 100; i++) {
        int iter = 0;
        TreeType* tree = new TreeType();
        int size = (int)floor(A * pow(B, i));
        cout << "albero numero: " << i+1 << "\tSize: " << size << endl;
        double minTime = getTmin();
        
        steady_clock::time_point start = steady_clock::now();
        steady_clock::time_point end;

        do {
            for(int n = 0; n < size; n++){
                    unsigned int key = pseudoRand();
                    if (tree->find(key) != "a") {
                        tree->insert(key, "a");
                    }
            }

            end = steady_clock::now();
            iter++;
        } while(duration_cast<duration<double>>(end - start).count() <= minTime);
        double avgTime = (duration_cast<nanoseconds>(end - start).count() / iter) / size; 

        cout << "FINAL: " << avgTime << endl;
        delete tree;
        
    }

return 0;
}

template<class TreeType> int calcStdDev() {
    for(int i = 0; i < 100; i++) {
        int size = (int)floor(A * pow(B, i));
        cout << "alberi numero: " << i+1 << "\tSize: " << size << endl;

        double avgTime = 0;
        double times[N];
        double minTime = getTmin();
        double stdDev = 0.0;

        for (int j=0; j<N; j++) {
            TreeType *tree = new TreeType();
            int iter = 0;
            
            steady_clock::time_point start = steady_clock::now();
            steady_clock::time_point end;

            do {
                for(int n = 0; n < size; n++){
                        unsigned int key = pseudoRand();
                        if (tree->find(key) != "a") {
                            tree->insert(key, "a");
                        }
                }

                end = steady_clock::now();
                iter++;
            } while(duration_cast<duration<double>>(end - start).count() <= minTime);
            double iterTime = (duration_cast<nanoseconds>(end - start).count() / iter) / size;
            times[j] = iterTime;
            avgTime += iterTime;

            delete tree;
        }
        
        avgTime = avgTime / 20;

        for (int k=0; k<N; k++) {
            stdDev += pow((times[k] - avgTime), 2);
        }

        stdDev = stdDev / 20;

        cout << "FINAL: " << stdDev << endl;
    }
    return 0;
}

// DEFINIZIONE FUNZIONI

double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    typedef duration<double, seconds::period> duration;

    return duration(end - start).count();
}

double getTmin(){ // a posto

    double R = getResolution();

    double Tmin = R * ((1.000/0.01) + 1.000);

    return Tmin;
}

double getFinalTime(double times[], int length) {
    double sum = 0.0;

    for (int i = 0; i < length; i++) {
        sum += times[i];
    }

    return sum / length;
}