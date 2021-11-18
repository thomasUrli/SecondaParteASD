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
            AVLNode(int, std::string);
            ~AVLNode();
        };
        
        AVL();
        ~AVL();
        void insert(int, std::string);
        std::string find(int);
        void show();
        AVLNode* getRoot();

    private:
        AVLNode* root;
        AVLNode* rightRotate(AVLNode*);
        AVLNode* leftRotate(AVLNode*);
        int getBalance(AVLNode*);
        AVLNode* insert(AVLNode*, int, std::string);
        int findMax(int, int);
        int getHeight(AVLNode*);
        std::string findKey(AVLNode*, int);
        void preorder(AVLNode*);

};