#include "AVL.cpp"
#include "BST.cpp"
#include "RBT.cpp"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <random>
#include <string.h>
#include <limits>

using namespace std;
using namespace std::chrono;

//constants
const int A = 1000;
const double B = 1.0715;
string value = "a";
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(1, __INT_MAX__ - 1);

int pseudoRand(){ // genera in modo pseudo casuale un valore k
    return distrib(gen);  // generates number in the range 1..9999999 
}

void useAVL(){
    
    AVL tree;

    // tempo partenza
    for(int i = 0; i < 100; i++){
        cout << "albero numero " << i+1 << endl;
        int size = (int)floor(A * pow(B, i));
        
        for(int n = 0; n < size; n++){
            int key = pseudoRand();
            
            while (tree.findAVL(key) == "a") {
                key = pseudoRand();
            }

            tree.insertAVL(key, value);
            
        }        

    }
}

void useAVL(int size){

    AVL tree;

    for(int n = 0; n < size; n++){
        int key = pseudoRand();
        
        while (tree.findAVL(key) == "a") {
            key = pseudoRand();
        }

        tree.insertAVL(key, value);
        
    }
}

void useBST(){
    BST tree;

    // tempo partenza
    for(int i = 0; i < 100; i++){
        
        cout << "albero numero " << i+1 << endl;
        int size = (int)floor(A * pow(B, i));
        
        for(int n = 0; n < size; n++){
            int key = pseudoRand();
            
            while (tree.findBST(key) == "a") {
                key = pseudoRand();
            }

            tree.insertBST(key, value);
            
        }        

    }
}

void useBST(int size){
    BST tree;
        
    for(int n = 0; n < size; n++){
        int key = pseudoRand();
        
        while (tree.findBST(key) == "a") {
            key = pseudoRand();
        }

        tree.insertBST(key, value);
        
    }
}

void useRBT(){
    RBT tree;

    for(int i = 0; i < 100; i++){
        
        cout << "albero numero " << i+1 << endl;
        int size = (int)floor(A * pow(B, i));
        
        for(int n = 0; n < size; n++){
            int key = pseudoRand();
            
            while (tree.findRBT(key) == "a") {
                key = pseudoRand();
            }

            tree.insertRBT(key, value);
            
        }        

    }
}

void useRBT(int size){
    RBT tree;

    for(int n = 0; n < size; n++){
        int key = pseudoRand();
        
        while (tree.findRBT(key) == "a") {
            key = pseudoRand();
        }

        tree.insertRBT(key, value);
        
    }
}





















































