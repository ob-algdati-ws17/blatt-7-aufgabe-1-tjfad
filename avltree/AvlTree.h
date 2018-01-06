#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AvlTree {

private:

    struct Node {
        const int key;
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
        void insert(const int);

        /*
         *
         */
        bool isLeftSon() const;

        bool isRightSon() const;

        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

    /*
    *
    */
    static void upin(Node *);

public:

    ~AvlTree();

    bool search(const int) const;

    void insert(const int);

    void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //TREES_AVLTREE_H
