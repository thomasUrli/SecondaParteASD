#include <string.h>

class AVL {
    public: 
        struct AVLNode { //altezza differisce al massimo di 1
            int key;
            std::string value;
            int height;
            AVLNode* left;
            AVLNode* right;
            AVLNode();
            AVLNode(int k, std::string v);
            ~AVLNode();
        };
        
        AVL();
        ~AVL();
        void insert(int k, std::string v);
        std::string find(int k);
        void show();
        AVLNode* getRoot();

    private:
        AVLNode* root;
        AVLNode* rightRotate(AVLNode*);
        AVLNode* leftRotate(AVLNode*);
        int getBalance(AVLNode* node);
        AVLNode* insert(AVLNode*, int, std::string);
        int findMax(int, int);
        int getHeight(AVLNode*);
        std::string findKey(AVLNode*, int);
        void preorder(AVLNode*);

};