/*
*/

// LIBRERIE
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>
#include "AVL.cpp"
#include "BST.cpp"
#include "RBT.cpp"

using namespace std;
using namespace std::chrono;

// DICHIARAZIONE COSTANTI
const int A = 1000;
const double B = exp((log(1000000)-log(1000))/99);
const int N = 20;

string FILENAMES[] = {
    "BST_Times.txt",
    "BST_StdDevs.txt",
    "RBT_Times.txt",
    "RBT_StdDevs.txt",
    "AVL_Times.txt",
    "AVL_StdDevs.txt"
};

// DICHIARAZIONE FUNZIONI
double getResolution();
double getTmin();
double getFinalTime(double[], int);
template<class TreeType> double calcAvgTime(int);
template<class TreeType> double calcStdDev(int);
void writeToFile(vector<vector<double>>, string[]);


random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distrib(1, __INT_MAX__);
const double minTime = getTmin();


unsigned int pseudoRand(){ // genera in modo pseudo casuale un valore k
    return distrib(gen);
}


int main() {
    vector<double> BSTtimes(100);
    vector<double> RBTtimes(100);
    vector<double> AVLtimes(100);
    vector<double> BSTstdDevs(100);
    vector<double> RBTstdDevs(100);
    vector<double> AVLstdDevs(100);

    for(int i = 0; i < 100; i++) {
        int size = floor(A * pow(B, i));

        BSTtimes[i] = calcAvgTime<BST>(size);
        RBTtimes[i] = calcAvgTime<RBT>(size);
        AVLtimes[i] = calcAvgTime<AVL>(size);
        BSTstdDevs[i] = calcStdDev<BST>(size);
        RBTstdDevs[i] = calcStdDev<RBT>(size);
        AVLstdDevs[i] = calcStdDev<AVL>(size);

        cout << i << " " << size << " " << BSTtimes[i] << " " << BSTstdDevs[i] << " " << RBTtimes[i] << " " << RBTstdDevs[i] << " " << AVLtimes[i] << " " << AVLstdDevs[i] << endl;
    }

    vector<vector<double>> vectorsToWrite = {BSTtimes, BSTstdDevs, RBTtimes, RBTstdDevs, AVLtimes, AVLstdDevs};

    writeToFile(vectorsToWrite, FILENAMES);
    

    return 0;
    
}

// DEFINIZIONE FUNZIONI

template<class TreeType> double calcAvgTime(int size) {
    int iter = 0;
    TreeType* tree = new TreeType();  
    
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;

    do {
        for(int n = 0; n < size; n++){
                unsigned int key = pseudoRand();
                if (tree->find(key) == NULL) {
                    tree->insert(key, "");
                }
        }

        end = steady_clock::now();
        iter++;
    } while(duration_cast<duration<double>>(end - start).count() <= minTime);
    double avgTime = ((double) duration_cast<nanoseconds>(end - start).count() / iter) / size; 

    //cout << "FINAL: " << avgTime << endl;
    delete tree;
    return avgTime;
}

template<class TreeType> double calcStdDev(int size) {    
    double avgTime = 0;
    double times[N];
    double stdDev = 0.0;

    for (int j=0; j<N; j++) {
        TreeType *tree = new TreeType();
        int iter = 0;
        
        steady_clock::time_point start = steady_clock::now();
        steady_clock::time_point end;

        do {
            for(int n = 0; n < size; n++){
                    unsigned int key = pseudoRand();
                    if (tree->find(key) == NULL) {
                        tree->insert(key, "");
                    }
            }

            end = steady_clock::now();
            iter++;
        } while(duration_cast<duration<double>>(end - start).count() <= minTime);
        double iterTime = ((double) duration_cast<nanoseconds>(end - start).count() / iter) / size;
        times[j] = iterTime;
        avgTime += iterTime;

        delete tree;
    }
    
    avgTime = avgTime / N;

    for (int k=0; k<N; k++) {
        stdDev += pow((times[k] - avgTime), 2);
    }

    stdDev = stdDev / N;

    return stdDev;
}

void writeToFile(vector<vector<double>> vectors, string filenames[]) {
    for (int i=0; i<6; i++) {
        ofstream file;
        file.open(filenames[i],  ios::trunc);   //Elimina il contenuto presente nel file
        
        file << "var data = [" << endl;

        for (int j = 0; j < 100; j++) {
            int size = floor(A * pow(B, i));
            file << "[" << size << ", " << vectors[i][j] << "]\n";
        }
        
        file << "];";
        
        file.close();
    }
    
}

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