#include <iostream>
#include <string.h>
#include <stdio.h>
#include "headers/AVL.hpp"

using namespace std;

// Ruota a destra sul nodo x


AVL::AVLNode* AVL::rightRotate(AVLNode* x){
    AVL::AVLNode* y = x->left;
    AVL::AVLNode* r = y->right;

    y->right = x;
    x->left = r;

    x->height = findMax(getHeight(x->left),getHeight(x->right)) + 1;
    y->height = findMax(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Ruota a sinistra sul nodo x
AVL::AVLNode* AVL::leftRotate(AVLNode* x){
    AVL::AVLNode* y = x->right;
    AVL::AVLNode* r = y->left;

    // Rotazione
    y->left = x;
    x->right = r;

    // Aggiornamento altezze
    x->height = findMax(getHeight(x->left),getHeight(x->right)) + 1;
    y->height = findMax(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

int AVL::getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    } else {
        return getHeight(node->left) - getHeight(node->right);
    }
}

AVL::AVLNode* AVL::insert(AVLNode* node, int key, string value) {
    // Inserisco il nodo come in un BST
    if (node == NULL) {
        return new AVLNode(key, value);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }

    // while (node != NULL) {
    //     if(node->key < key){
    //         node = node->right;
    //     } else{
    //         node = node->left;
    //     }
    // }

    // node = new AVLNode(key, value);

    // Aggiorno l'altezza del nodo
    node->height = 1 + findMax(getHeight(node->left), getHeight(node->right));

    // Controllo, col fattore di bilanciamento del nodo, se il nodo è sbilanciato
    int balance = getBalance(node);

    // Caso 1
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Caso 2
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Caso 3
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // while(abs(getBalance(node)) == 2) {
    //     // Aggiorno l'altezza del nodo
    //     node->height = 1 + findMax(getHeight(node->left), getHeight(node->right));

    //     // Controllo, col fattore di bilanciamento del nodo, se il nodo è sbilanciato
    //     int balance = getBalance(node);

    //     // Caso 1
    //     if (balance > 1 && key < node->left->key) {
    //         return rightRotate(node);
    //     }

    //     // Caso 2
    //     if (balance < -1 && key > node->right->key) {
    //         return leftRotate(node);
    //     }

    //     // Caso 3
    //     if (balance > 1 && key > node->left->key) {
    //         node->left = leftRotate(node->left);
    //         return rightRotate(node);
    //     }

    //     // Caso 4
    //     if (balance < -1 && key < node->right->key) {
    //         node->right = rightRotate(node->right);
    //         return leftRotate(node);
    //     }
    // }
    return node;
}

int AVL::findMax(int a, int b) {
    return (a > b)? a : b;
}

int AVL::getHeight(AVLNode* x) {
    if (x == NULL){
        return 0;
    } else {
        return x->height;
    }
}

AVL::AVLNode* AVL::findKey(AVLNode* r, int k) {
    while (r != nullptr) {
        if(r->key == k){
            return r;
        } else{
            if(r->key < k){
                r = r->right;
            } else{
                r = r->left;
            }
        }
    }

    return NULL;
}

void AVL::preorder(AVLNode* r) {
    if(r != NULL) {
        cout << r->key << ":" << r->value << ":" << r->height << " ";
        preorder(r->left);
        preorder(r->right);
    } else {
        cout << "NULL" << " ";
    }
}

AVL::AVLNode::AVLNode() {
    key = -1;
    value = "";
    height = 1;
    left = nullptr;
    right = nullptr;
}

AVL::AVLNode::AVLNode(int k, string v) {
    key = k;
    value = v;
    left = nullptr;
    right = nullptr;
    height = 1; // Ogni nuovo nodo è una foglia
}

AVL::AVLNode::~AVLNode() {
    if (right != nullptr) {
        delete right;
    }

    if (left != nullptr) {
        delete left;
    }
}

AVL::AVL() {
    root = NULL;
}

AVL::~AVL() {
    delete root;
}

void AVL::insert(int k, string v){
    root = insert(root, k, v);
}

AVL::AVLNode* AVL::find(int k){
    return findKey(root, k);  
}

void AVL::show(){
    preorder(root);
}

AVL::AVLNode* AVL::getRoot() {
    return root;
}