#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;
/**
 * AvlTree. Abgabe für Algorythmen und Datanstrukturen I SS2018
 * Author: Christoph Hahn
 * Mail: hahn0@hm.edu
 */
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

    friend class AvlTreeTest;

public:
    /**
     * Destructor
     */
    ~AvlTree();

    /**
     * Search for an Element in the tree.
     * @return true if found else false.
     */
    bool search(const int) const;
    /**
     * Insert an Element in the Tree.
     */
    void insert(const int);
    /**
     * Remove an Element from tree.
     */
    void remove(const int);

    /**
     * Get the next greater int from the tree. If no greater 0.
     * @returnnext greater int from the tree.
     */
    const int getSymSuccessor(const int);
    /**
     * Get the next smaller int from the tree. If no smaller 0.
     * @return next smaller int from the tree.
     */
    const int getSymPredecessor(const int);

    /**
     * Get the values of the nodes in preorder.
     *
     * key
     * left
     * right
     * @return values of the nodes in preorder.
     */
    vector<int> *preorder() const;  // (Hauptreihenfolge)

    /**
     * * Get the values of the nodes in order.
     *
     * left
     * key
     * right
     * @return values of the nodes in order.
     */
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)

    /**
     * Get the values of the nodes in postorder.
     *
     * left
     * right
     * key
     * @return values of the nodes in postorder.
     */
    vector<int> *postorder() const; // (Nebenreihenfolge)

    //just for testing

    /**
     * Get the balances of the nodes in preorder.
     *
     * key
     * left
     * right
     * @return balances of the nodes in preorder.
     */
    vector<int> *bPreorder() const;
    /*
     *
     */
    /**
     * Get the balances of the nodes in order.
     *
     * left
     * key
     * right
     * @return balances of the nodes in order.
     */
    vector<int> *bInorder() const;
    /**
     * Get the balances of the nodes in postorder.
     *
     * left
     * right
     * key
     *
     * @return balances of the nodes in postorder.
     */
    vector<int> *bPostorder() const;
    /**
     * Output a tree.
     * @return
     */
    friend ostream &operator<<(ostream &, const AvlTree &);


};


#endif //TREES_AVLTREE_H
