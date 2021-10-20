#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

class RBT{
    enum COLOR {
        BLACK, 
        RED
    };

    struct RBTNode{
        int key;
        string value = "";
        COLOR color;
        RBTNode* parent = NULL;
        RBTNode* left; 
        RBTNode* right;

        RBTNode(){}

        RBTNode(int k, string v, COLOR c, RBTNode* l, RBTNode* r){
            key = k;
            value = v;
            color = c;
            left = l;
            right = r;
        }

    };

    //////////////////+++++++++++++++++++++++++++++++++++++
    RBTNode* NIL = new RBTNode(-1, "", BLACK, NULL, NULL);
    RBTNode* root;

    void leftRotate(RBTNode* x){
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

    
    void rightRotate(RBTNode* x){
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

    void treeInsert(RBTNode* z) {
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

    void RB_Insert(RBTNode* x) {
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

    string findKey(RBTNode* r, int k) {
        if (r == NULL) {
            return "";
        }

        if(r->key == k || r == NIL){
            return  r->value;
        } else{
            if(r->key > k){
                return findKey(r->left, k);
            } else{
                return findKey(r->right, k);
            }
        }
    }

    string color(RBTNode* x) {
        if (x->color == BLACK) {
            return "black";
        } else {
            return "red";
        }
    }

    void preorder(RBTNode* r) {
        if(r != NIL) {
            cout << r->key << ":" << r->value << ":" << color(r) << " ";
            preorder(r->left);
            preorder(r->right);
        } else {
            cout << "NULL" << " ";
        }
    }

    
    public:
        RBT() {
            root = NIL;
        }

        void insertRBT(int k, string v){
            RBTNode* toInsert = new RBTNode();
            toInsert->key = k;
            toInsert->value = v;
            toInsert->parent = NIL;
            toInsert->left = NIL;
            toInsert->right = NIL;
            RB_Insert(toInsert);
        }

        string findRBT(int k){
            return findKey(root, k);
        }

        void showRBT(){
            preorder(root);
            cout << endl;
        }
};


// todo: DA TOGLIERE
/*int main(){
    char command[20];
    int assignedKey;
    string assignedValue;
    RBT t;

    cout << "caso 1" << endl;
    t.insertRBT(1, "a");
    cout << t.findRBT(1) << endl;
    t.showRBT();
    
    cout << "caso 2" << endl;
    t.insertRBT(2, "b");
    cout << t.findRBT(2) << endl;
    t.showRBT();
    
    cout << "caso 3" << endl;
    t.insertRBT(3, "c");
    cout << t.findRBT(3);
    t.showRBT();
    /*while(true){
        cin >> command;
        if(strcmp(command, "insert") == 0){
            cin >> assignedKey >> assignedValue;

            t.insert(assignedKey, assignedValue);
        } else if(strcmp(command, "find") == 0){
            cin >> assignedKey;
            t.find(assignedKey);
        } else if(strcmp(command, "show") == 0){
            t.show();
            cout << endl;
        } else {
            return 0;
        }
    }
}*/