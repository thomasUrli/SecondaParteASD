#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

class BST{
    struct BSTNode{
        int key;
        string value = "";
        BSTNode* parent = NULL;
        BSTNode* left = NULL;
        BSTNode* right = NULL;
    };

    BSTNode* root;

    void insert(BSTNode* z){
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

    string findKey(BSTNode* r, int k) {
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

    void preorder(BSTNode* r) {
        if(r != NULL) {
            cout << r->key << ":" << r->value << " ";
            preorder(r->left);
            preorder(r->right);
        } else {
            cout << "NULL" << " ";
        }
    }

    public:
        BST() {
            root = NULL;
        }

        void insert(int k, string v){
            BSTNode* toInsert = new BSTNode();
            toInsert->key = k;
            toInsert->value = v;
            insert(toInsert);
        }

        string find(int k){
            return findKey(root, k);
        }

        void show(){
            preorder(root);
        }
};



// todo: DA TOGLIERE
/*int main(){
    char command[20];
    int assignedKey = 0;
    string assignedValue = "prova";
    BST t;

    while(true){
        cin >> command;
        if(strcmp(command, "insert") == 0){
            cin >> assignedKey >> assignedValue;
            t.insert(assignedKey, assignedValue);
        } else if(strcmp(command, "find") == 0){
            cin >> assignedKey;
            t.find(assignedKey);
        } else if(strcmp(command, "show") == 0){
            t.show();
            //cout << endl;
        } else{
            return 0;
        }
    }
}*/