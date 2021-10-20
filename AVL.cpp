#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

class AVL{
    
    struct AVLNode{ //altezza differisce al massimo di 1
        int key = -1;
        string value = "";
        int height = 0;
        AVLNode* left = NULL;
        AVLNode* right = NULL;

        AVLNode(){
            int key = -1;
            string value = "";
            int height = 0;
            AVLNode* left = new AVLNode();
            AVLNode* right = new AVLNode();
        }

        AVLNode(int k, string v){
            key = k;
            value = v;
            left = NULL;
            right = NULL;
            height = 1; // Ogni nuovo nodo è una foglia
        }
    };

    AVLNode* root;

    // Ruota a destra sul nodo x
    AVLNode* rightRotate(AVLNode* x){
        AVLNode* y = x->left;
        AVLNode* r = y->right;

        y->right = x;
        x->left = r;

        x->height = findMax(getHeight(x->left),getHeight(x->right)) + 1;
        y->height = findMax(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }

    // Ruota a sinistra sul nodo x
    AVLNode* leftRotate(AVLNode* x){
        AVLNode* y = x->right;
        AVLNode* r = y->left;

        // Rotazione
        y->left = x;
        x->right = r;

        // Aggiornamento altezze
        x->height = findMax(getHeight(x->left),getHeight(x->right)) + 1;
        y->height = findMax(getHeight(y->left), getHeight(y->right)) + 1;
        
        return y;
    }

    int getBalance(AVLNode* node) {
        if (node == NULL) {
            return 0;
        } else {
            return getHeight(node->left) - getHeight(node->right);
        }
    }

    AVLNode* insertAVL(AVLNode* node, int key, string value) {
        // Inserisco il nodo come in un BST
        if (node == NULL) {
            return new AVLNode(key, value);
        }

        if (key < node->key) {
            node->left = insertAVL(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertAVL(node->right, key, value);
        }

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

        return node;
    }

    int findMax(int a, int b)
    {
        return (a > b)? a : b;
    }

    int getHeight(AVLNode* x)
    {
        if (x == NULL){
            return 0;
        } else {
            return x->height;
        }
    }

    string findKey(AVLNode* r, int k) {
        if (r == NULL) {
            return "";
        }
        
        if(r->key == k){
            return r->value;
        } else{
            if(r->key < k){
                return findKey(r->right, k);
            } else{
                return findKey(r->left, k);
            }
        }
    }

    void preorder(AVLNode* r) {
        if(r != NULL) {
            cout << r->key << ":" << r->value << ":" << r->height << " ";
            preorder(r->left);
            preorder(r->right);
        } else {
            cout << "NULL" << " ";
        }
    }

    public:
        AVL() {
            root = NULL;
        }

        void insertAVL(int k, string v){
            root = insertAVL(root, k, v);
        }

        string findAVL(int k){
            return findKey(root, k);  
        }

        void showAVL(){
            preorder(root);
        }

        AVLNode* getRoot() {
            return root;
        }
};


// todo: DA TOGLIERE
/*int main(){
    char command[20];
    int assignedKey = 0;
    string assignedValue = "";
    AVL t;

    while(true){
        cin >> command;
        if(strcmp(command, "insert") == 0){
            cin >> assignedKey >> assignedValue;
            t.insert(assignedKey, assignedValue);
        } else if(strcmp(command, "find") == 0){
            cin >> assignedKey;
            string s = t.find(assignedKey);
            cout << s << endl;
        } else if(strcmp(command, "show") == 0){
            t.show();
            //cout << endl;
        } else{
            return 0;
        }
    }
}*/