#include "AvlTree.h"
#include <functional>

using namespace ::std;

/********************************************************************
 * Nodes
 *******************************************************************/

AvlTree::Node::Node(const int k) : key(k){}

AvlTree::Node::Node(const int k, AvlTree::Node* ro) : key(k), root(ro){}

AvlTree::Node::Node(const int k, AvlTree::Node * l, AvlTree::Node *r) : key(k), left(l), right(r){}

AvlTree::Node::Node(const int k, AvlTree::Node* ro, AvlTree::Node * l, AvlTree::Node *r) : key(k), root(ro), left(l), right(r){}

AvlTree::Node::~Node() {
    delete left;
    delete right;
}

/********************************************************************
 * Constructors Destructor
 *******************************************************************/




AvlTree::~AvlTree() {
    delete root;
}





/********************************************************************
 * Search
 *******************************************************************/

bool AvlTree::search(const int value) const {
    if (root == nullptr)
        return false;
    else
        return root->search(value);
}

bool AvlTree::Node::search(const int value) const {
    if(key == value)
        return true;

    if(value < key && left != nullptr)
        return left->search(value);

    if(value > key && right != nullptr)
        return right->search(value);

    return false;
}

/********************************************************************
 * Insert
 *******************************************************************/

void AvlTree::insert(const int value) {
    root = (root == nullptr) ? new Node(value, nullptr) : root->insert(value);
}

AvlTree::Node* AvlTree::Node::insert(const int value) {
    if(key == value)
        return this;

    else if(value < key){
        if(left == nullptr) {
            left = new Node(value, this);
            if(right == nullptr) {
                balance = -1;
                upin();
            }else//No change in height of subtree -> no upin
                balance = 0;
        }else
            left->insert(value);

    }else if(value > key){
        if(right == nullptr){
            right = new Node(value, this);
            if(left == nullptr){
                balance = +1;
                upin();
            }else
                balance = 0;

        } else
            right->insert(value);
    }
    return this;
}
/********************************************************************
 * upin
 *******************************************************************/

void AvlTree::Node::upin(){
    if(root == nullptr)
        return;
    Node * nodeRoot = root;
    //Node is left son
    if(isLeftSon()) {
        if (nodeRoot->balance == +1){//parent tree was right heavy before left insert -> height hasn't changed
            nodeRoot->balance = 0;
            return;
        }else if(nodeRoot->balance == 0){//parent tree was neutral before left insert -> height +1
            nodeRoot->balance = -1;
            nodeRoot->upin();
        }else if(nodeRoot->balance == -1){//parent tree was left heavy before left insert
            //TODO rotations
            if(balance == -1){
                nodeRoot->rotateRight();
            }else if(balance = +1){
                rotateLeft();
                nodeRoot->rotateRight();
            }else
                throw "Invariant violated";
        }else{
            throw "Invariant violated";
        }
    }//
    else if(isRightSon()){
        switch (nodeRoot->balance) {
            case -1:
                nodeRoot->balance = 0;
                return;
                break;
            case 0:
                nodeRoot->balance = +1;
                nodeRoot->upin();
                break;
            case 1:
                if(balance == +1){
                    nodeRoot->rotateLeft();
                }else if(balance = -1){
                    rotateRight();
                    nodeRoot->rotateLeft();
                }else
                    throw "Invariant violated";

                break;
            default:
                throw "Invariant violated";
        }
    }

}
/********************************************************************
 * Rotations
 *******************************************************************/
void AvlTree::Node::rotateRight() {
    auto newRoot = left;
    left = newRoot->right;
    if(left != nullptr)
        left->root = this;

    newRoot->right = this;
    newRoot->root = root;
    root = newRoot;
    if(newRoot->root != nullptr){
        if(newRoot->root->left == this)
            newRoot->root->left = newRoot;
        else if(newRoot->root->right == this)
            newRoot->root->right = newRoot;
        else
            throw "Tree inconsistent";
    }
}
void AvlTree::Node::rotateLeft() {
    auto newRoot = right;
    right = newRoot->left;
    if(right != nullptr)
        right->root = this;

    newRoot->left = this;
    newRoot->root = root;
    root = newRoot;
    if(newRoot->root != nullptr){
        if(newRoot->root->left == this)
            newRoot->root->left = newRoot;
        else if(newRoot->root->right == this)
            newRoot->root->right = newRoot;
        else
            throw "Tree inconsistent";
    }
}

bool AvlTree::Node::isRightSon() const {
    if(root == nullptr)
        return false;
    if(this == root->right)
        return true;
    return false;
}
bool AvlTree::Node::isLeftSon() const {
    if(root == nullptr)
        return false;
    if(this == root->left)
        return true;
    return false;
}

/********************************************************************
 * Remove
 *******************************************************************/

void AvlTree::remove(const int value) {

}

/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AvlTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AvlTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AvlTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}



/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AvlTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}

