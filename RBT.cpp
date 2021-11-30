#include <iostream>
#include <string.h>
#include <stdio.h>
#include "headers/RBT.hpp"

using namespace std;


    //////////////////+++++++++++++++++++++++++++++++++++++
RBT::RBTNode* NIL = new RBT::RBTNode(-1, "", RBT::BLACK, NIL, NIL);
RBT::RBTNode* root;

void RBT::leftRotate(RBTNode* x){
    RBTNode* y = x->right;      //  inizializzo y
    x->right = y->left;         /*  ruoto sottoalbero sinistro di y
                                    nel sottoalbero destro di x */
    if(y->left != NIL){
        y->left->parent = x;
    }

    y->parent = x->parent;      //  collego padre di x a y

    if(x->parent == NIL){
        root = y;
    } else if(x == x->parent->left){
        x->parent->left = y;
    } else{
        x->parent->right = y;
    }

    y->left = x;                // metto x a sinistra di y
    x->parent = y;
}


void RBT::rightRotate(RBTNode* x){
    RBTNode* y = x->left;       
    x->left = y->right;         
    
    if(y->right != NIL){
        y->right->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == NIL){
        root = y;
    } else if(x == x->parent->right){
        x->parent->right = y;
    } else{
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void RBT::treeInsert(RBTNode* z) {
    RBTNode* y = NIL;
    RBTNode* x = root;

    while (x != NIL) {
        y = x;

        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;
    if (y == NIL) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

void RBT::insert(RBTNode* x) {
    treeInsert(x);
    x->color = RED;
    
    while (x != root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            RBTNode* y = x->parent->parent->right;

            if (y->color == RED) { // CASO 1
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) { // CASO 2
                    x = x->parent;
                    leftRotate(x);
                }

                x->parent->color = BLACK;   // CASO 3
                x->parent->parent->color = RED;
                rightRotate(x->parent->parent);
            }
        } else {
            RBTNode* y = x->parent->parent->left;

            if (y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rightRotate(x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                leftRotate(x->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

RBT::RBTNode* RBT::findKey(RBTNode* r, int k) {
    // if (r == nullptr) {
    //     return NULL;
    // }

    // if(r->key == k || r == NIL){
    //     return r;
    // } else{
    //     if(r->key > k){
    //         return findKey(r->left, k);
    //     } else{
    //         return findKey(r->right, k);
    //     }
    // }

    while (r != NIL) {
        if (r->key == k) {
            return r;
        } else {
            if (r->key < k) {
                r = r->right;
            } else {
                r = r->left;
            }
        }
    }

    return NULL;
}

string RBT::color(RBTNode* x) {
    if (x->color == BLACK) {
        return "black";
    } else {
        return "red";
    }
}

void RBT::preorder(RBTNode* r) {
    if(r != NIL) {
        cout << r->key << ":" << r->value << ":" << color(r) << " ";
        preorder(r->left);
        preorder(r->right);
    } else {
        cout << "NULL" << " ";
    }
}

RBT::RBTNode::RBTNode() {
    value = "";
    parent = NIL;
    left = NIL;
    right = NIL;
}

RBT::RBTNode::RBTNode(int k, std::string v, COLOR c, RBTNode* l, RBTNode* r) {
    key = k;
    value = v;
    color = c;
    parent = NIL;
    left = l;
    right = r;
}

RBT::RBTNode::~RBTNode() {
    if (right != nullptr && right != NIL) {
        delete right;
    }

    if (left != nullptr && left != NIL) {
        delete left;
    }
}

RBT::RBT() {
    root = NIL;
}

RBT::~RBT() {
    delete root;
}

void RBT::insert(int k, string v){
    RBTNode* toInsert = new RBT::RBTNode(k, v, RBT::RED, NIL, NIL);
    insert(toInsert);
}

RBT::RBTNode* RBT::find(int k){
    return findKey(root, k);
}

void RBT::show(){
    preorder(root);
    cout << endl;
}

// int main(){
//     char command[20];
//     int assignedKey;
//     string assignedValue;
//     RBT t;

//     while(true){
//         cin >> command;
//         if(strcmp(command, "insert") == 0){
//             cin >> assignedKey >> assignedValue;

//             t.insert(assignedKey, assignedValue);
//         } else if(strcmp(command, "find") == 0){
//             cin >> assignedKey;
//             RBT::RBTNode* r = t.find(assignedKey);
//             cout << r->value << endl;
//         } else if(strcmp(command, "show") == 0){
//             t.show();
//             cout << endl;
//         } else {
//             return 0;
//         }
//     }
// }