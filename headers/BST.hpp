#include <string.h>

class BST {
    public: 
        struct BSTNode{
            int key;
            std::string value;
            BSTNode* parent;
            BSTNode* left;
            BSTNode* right;
            ~BSTNode();
        };
        
        BST();
        ~BST();
        void insert(int, std::string);
        std::string find(int);
        void show();

    private:
        BSTNode* root;
        void insert(BSTNode*);
        std::string findKey(BSTNode*, int);
        void preorder(BSTNode*);

};