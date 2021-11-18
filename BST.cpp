#include <iostream>
#include <string.h>
#include <stdio.h>
#include "headers/BST.hpp"

using namespace std;


void BST::insert(BSTNode* z){
    BSTNode* y = NULL;
    BSTNode* x = root;

    while(x != NULL) {
        y = x;

        if (x->key > z->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NULL) {
        root = z;
    } else {
        if (y->key > z->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
}

string BST::findKey(BSTNode* r, int k) {
    if (r == NULL) {
        return "";
    } 

    if(r->key == k){
        return r->value;
    } else{
        if(r->key > k){
            return findKey(r->left, k);
        } else{
            return findKey(r->right, k);
        }
    }
}

void BST::preorder(BSTNode* r) {
    if(r != NULL) {
        cout << r->key << ":" << r->value << " ";
        preorder(r->left);
        preorder(r->right);
    } else {
        cout << "NULL" << " ";
    }
}

BST::BSTNode::~BSTNode() {
    if (right != nullptr) {
        delete right;
    }

    if (left != nullptr) {
        delete left;
    }
}

BST::BST() {
    root = NULL;
}

BST::~BST() {
    delete root;
}

void BST::insert(int k, string v){
    BSTNode* toInsert = new BSTNode();
    toInsert->key = k;
    toInsert->value = v;
    insert(toInsert);
}

string BST::find(int k){
    return findKey(root, k);
}

void BST::show(){
    preorder(root);
}