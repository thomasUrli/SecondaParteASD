#include <string.h>

class RBT {
    public:
        enum COLOR {
            BLACK,
            RED
        };

        struct RBTNode{
            int key;
            std::string value;
            RBTNode* parent;
            RBTNode* left;
            RBTNode* right;
            COLOR color;
            RBTNode();
            RBTNode(int, std::string, COLOR, RBTNode*, RBTNode*);
            ~RBTNode();
        };
        
        RBT();
        ~RBT();
        void insert(int, std::string);
        RBTNode* find(int);
        void show();

    private:
        RBTNode* root;
        void leftRotate(RBTNode*);
        void rightRotate(RBTNode*);
        void treeInsert(RBTNode*);
        void insert(RBTNode*);
        RBTNode* findKey(RBTNode*, int);
        std::string color(RBTNode*);
        void preorder(RBTNode*);

};