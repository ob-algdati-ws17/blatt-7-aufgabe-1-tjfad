#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;





class AvlTree {

private:

    struct Node {
        int key;
        int balance = 0;
        Node *root = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;

        explicit Node(const int);
        Node(const int, Node*);
        Node(const int, Node *, Node *);
        Node(const int, Node* , Node *,Node *);

        ~Node();
        /*
         * Search in a Node.
         */
        bool search(const int) const;
        /*
         * Insert in a Node.
         */
        Node* insert(const int);
        /*
         *
         */
        void rotateRight();
        /*
         *
         */
        void rotateLeft();
        /*
         *return the node that was removed.. root points to new root of the tree... delete in tree
         */
        Node* remove(const int);
        /*
         *
         */
        void upin();
        /*
         *
         */
        void upout();
        /*
         *
         */
        bool isLeftSon() const;

        bool isRightSon() const;

        bool isLeaf() const;

        bool isInnerNode() const;

        Node* traceRoot();
        Node* getSymSuccessor(const int);
        Node* getSymPredecessor(const int);
        vector<int> *preorder(const bool) const;  // (Hauptreihenfolge)
        vector<int> *inorder(const bool) const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder(const bool) const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

    friend void removeLeaf(Node*);

public:

    ~AvlTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);

    const int getSymSuccessor(const int);
    const int getSymPredecessor(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    //just for testing
    vector<int> *bPreorder() const;
    vector<int> *bInorder() const;
    vector<int> *bPostorder() const;

    friend ostream &operator<<(ostream &, const AvlTree &);


};


#endif //TREES_AVLTREE_H
