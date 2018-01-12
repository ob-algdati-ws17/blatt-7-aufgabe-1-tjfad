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

//leftmost node
AvlTree::Node *AvlTree::Node::getSymSuccessor(const int value) {
    if(value >= key){
        if(right != nullptr)
            return right->getSymSuccessor(value);
        else
            return nullptr;
    }else if(value < key){
        if(left != nullptr){
            auto pre = left->getSymSuccessor(value);
            return pre == nullptr ? this : pre;
        } else
          return this;
    }

}

AvlTree::Node *AvlTree::Node::getSymPredecessor(const int value) {
    if(value <= key){
        if(left != nullptr)
            return left->getSymPredecessor(value);
        else
            return nullptr;
    }else if(value > key){
        if(right != nullptr){
            auto pre = right->getSymPredecessor(value);
            return pre == nullptr ? this : pre;
        }
        else
            return this;
    }
}

/********************************************************************
 * Insert
 *******************************************************************/

void AvlTree::insert(const int value) {
    root = (root == nullptr) ? new Node(value, nullptr) : root->insert(value);
    while(root != nullptr && root->root != nullptr)//check if the root has changed
        root = root->root;
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
                nodeRoot->balance=0;
                balance=0;
            }else if(balance == +1){
                auto newSubRoot = right;
                rotateLeft();
                nodeRoot->rotateRight();
                switch (newSubRoot->balance){
                    case -1:
                        newSubRoot->left->balance = 0;
                        newSubRoot->right->balance = +1;
                        break;
                    case 0:
                        newSubRoot->left->balance = 0;
                        newSubRoot->right->balance = 0;
                        break;
                    case +1:
                        newSubRoot->left->balance = -1;
                        newSubRoot->right->balance = 0;
                        break;
                }
                newSubRoot->balance = 0;
            }else
                throw "Invariant violated";
        }else{
            throw "Invariant violated";
        }
    }//i7i5i9i3i6i4i13i14
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
            case +1:
                if(balance == +1){
                    nodeRoot->rotateLeft();
                    nodeRoot->balance=0;
                    balance=0;
                }else if(balance == -1){
                    auto newSubRoot = left;
                    rotateRight();
                    nodeRoot->rotateLeft();
                    switch (newSubRoot->balance){
                        case -1:
                            newSubRoot->left->balance = 0;
                            newSubRoot->right->balance = +1;
                            break;
                        case 0:
                            newSubRoot->left->balance = 0;
                            newSubRoot->right->balance = 0;
                            break;
                        case +1:
                            newSubRoot->left->balance = -1;
                            newSubRoot->right->balance = 0;
                            break;
                    }
                    newSubRoot->balance = 0;
                }else
                    throw "Invariant violated";

                break;
            default:
                throw "Invariant violated";
        }
    }

}

void AvlTree::Node::upout() {
    if(balance != 0)
        throw "Invariant violated";
    if(root == nullptr)//end at root
        return;
    if(isLeftSon()){
        if(root->balance == -1){
            root->balance = 0;
            root->upout();
        }else if(root->balance == 0){
            root->balance = +1;
            return;
        }else if(root->balance == +1){
            if(root->right->balance == 0){//rotate left root
                root->rotateLeft();
                root->root->balance = -1;
                root->balance = +1;
                return;
            }else if(root->right->balance == +1){//rotate left root
                root->rotateLeft();
                root->root->balance = 0;
                root->balance = 0;
                root->root->upout();
            }else if(root->right->balance == -1){//rotate right(root->right) left(root)
                auto newRoot = root->right->left;
                root->right->rotateRight();
                root->rotateLeft();
                switch(newRoot->balance){
                    case -1://new root was left heavy
                        newRoot->left->balance = 0;
                        newRoot->right->balance = +1;
                        break;
                    case 0://newRoot was balanced
                        newRoot->left->balance = 0;
                        newRoot->right->balance = 0;
                        break;
                    case +1://newRoot was right heavy
                        newRoot->left->balance = -1;
                        newRoot->right->balance = 0;
                        break;
                    default:
                        throw "Invariant violated";
                }
                newRoot->balance = 0;

                newRoot->upout();
            }

        }else
            throw "Invariant violated";
    }else if(isRightSon()){
        if(root->balance == +1){
            root->balance = 0;
            root->upout();
        }else if(root->balance == 0){
            root->balance = -1;
            return;
        }else if(root->balance == -1) {
            if (root->left->balance == 0) {//rotate right root
                root->rotateRight();
                root->root->balance = -1;
                root->balance = +1;
                return;
            } else if (root->left->balance == -1) {//rotate right root
                root->rotateRight();
                root->root->balance = 0;
                root->balance = 0;
                root->root->upout();
            } else if (root->left->balance == +1) {//rotate left(root->right) right(root)
                auto newRoot = root->left->right;
                root->left->rotateLeft();
                root->rotateRight();
                switch (newRoot->balance) {
                    case -1://new root was left heavy
                        newRoot->left->balance = 0;
                        newRoot->right->balance = +1;
                        break;
                    case 0://newRoot was balanced
                        newRoot->left->balance = 0;
                        newRoot->right->balance = 0;
                        break;
                    case +1://newRoot was right heavy
                        newRoot->left->balance = -1;
                        newRoot->right->balance = 0;
                        break;
                    default:
                        throw "Invariant violated";
                }
                newRoot->balance = 0;

                newRoot->upout();
            }
        }
    }else
        throw "Tree inconsistent";

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
    return this == root->right;
}
bool AvlTree::Node::isLeftSon() const {
    if(root == nullptr)
        return false;
    return this == root->left;
}

bool AvlTree::Node::isLeaf() const {
    return left == nullptr && right == nullptr;
}

bool AvlTree::Node::isInnerNode() const {
    return left != nullptr && right != nullptr;
}

/********************************************************************
 * Remove
 *******************************************************************/

void AvlTree::remove(const int value) {
    if(root != nullptr)
        root = root->remove(value);
    while(root != nullptr && root->root != nullptr)//check if the root has changed #dirty
        root = root->root;

}
/*
 if(toRemove->root == nullptr){//only one node in the tree
        delete toRemove;
        return nullptr;
    }else if(root->balance == 0){//parent was balanced, is now right/left heavy but height doesnt change
        if(isRightSon()){
            root->right = nullptr;
            root->balance = -1;

        }else if(isLeftSon()){
            root->left = nullptr;
            root->balance = +1;
        }else
            throw "Invariant violated";
    }else if(root->balance == -1 && isLeftSon()){//parent was left heavy, is now balanced, height decreased by 1
        root->left = nullptr;
        root->balance = 0;
        root->upout();
    }else if(root->balance == +1 && isRightSon()) {//parent was left heavy, is now balanced, height decreased by 1
        root->right = nullptr;
        root->balance = 0;
        root->upout();
    }else{//rotations in upout...//parent is now double left/right heavy, rotations needet
        upout();
    }
    delete toRemove;
    return nullptr;
 */
AvlTree::Node* AvlTree::Node::remove(const int value) {
    if(value < key && left != nullptr){
        left = left->remove(value);
        return this;
    }

    else if(value > key && right != nullptr){
        right = right->remove(value);
        return this;
    }
    else if(key == value){
        //remove
        auto toRemove = this;

        if(isLeaf()){//remove a leaf
            removeLeaf(this);
        //    delete toRemove;
            return nullptr;
        }else if(isInnerNode()) {//remove a node with 1 leaf
            if(balance >= 0){//right heavy
                auto suc = right->getSymSuccessor(key);
                key = suc->key;
                right = right->remove(key);
            }else{
                auto pre = left->getSymPredecessor(key);
                key = pre->key;
                left = left->remove(key);
            }
            return this;//TODO
        }else{//only possible is a node with one leaf one inner node as sons
            if(left == nullptr){
                toRemove = right;
                key = right->key;
                right = nullptr;
                delete toRemove;
            }else if(right == nullptr){
                toRemove = left;
                key = left->key;
                left = nullptr;
                delete toRemove;
            }else
                throw "tree inconsistent";
            balance = 0;
            upout();
  //          delete  toRemove;
            return this;
        }

    }
    return nullptr; //key is not in the tree
}

void removeLeaf(AvlTree::Node * toRemove) {
    if(toRemove->root == nullptr){//only one node in the tree
        //falltrough

    }else if(toRemove->root->balance == 0){//parent was balanced, is now right/left heavy but height doesnt change
        if(toRemove->isRightSon()){
            toRemove->root->balance = -1;
        }else if(toRemove->isLeftSon()){
            toRemove->root->balance = +1;
        }else
            throw "Invariant violated";
    }else if(toRemove->root->balance == -1 && toRemove->isLeftSon()){//parent was left heavy, is now balanced, height decreased by 1
        toRemove->root->left = nullptr;
        toRemove->root->balance = 0;
        toRemove->root->upout();
    }else if(toRemove->root->balance == +1 && toRemove->isRightSon()) {//parent was left heavy, is now balanced, height decreased by 1
        toRemove->root->right = nullptr;
        toRemove->root->balance = 0;
        toRemove->root->upout();
    }else{//rotations in upout...//parent is now double left/right heavy, rotations needet
        toRemove->upout();
    }
    delete toRemove;

}
//i7i5i9i3i6i4i13i14d4d7d5i7i5i9i3i6i4i13i14i-5i-7i8i43i12i4569i1243i123i53i645i31i1253 d9 d123 d14 d4 d12
/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder(false);
}

vector<int> *AvlTree::bPreorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder(true);
}

vector<int> *AvlTree::Node::preorder(const bool balances) const {
    auto vec = new vector<int>();
    // Wurzel oder Balance in vec
    if(balances)
        vec->push_back(balance);
    else
        vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder(balances);
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder(balances);
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder(false);
}

vector<int> *AvlTree::bInorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder(true);
}

vector<int> *AvlTree::Node::inorder(const bool balances) const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder(balances);
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel oder Balance in vec
    if(balances)
        vec->push_back(balance);
    else
        vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder(balances);
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder(false);
}

vector<int> *AvlTree::bPostorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder(true);
}

vector<int> *AvlTree::Node::postorder(const bool balances) const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder(balances);
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder(balances);
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel oder Balance in vec
    if(balances)
        vec->push_back(balance);
    else
        vec->push_back(key);
    return vec;
}




/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int, const int, const AvlTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const int balance, const AvlTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value  <<" -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << node->key << "[label=\"key:" << node->key << " bal:" <<node->balance << "\"]" << endl; //print root

                    os << "    " << value << " -> " << node->key  // added to print bal
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->balance, node->left, "l");


                    printToOs(os, node->key, node->balance, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        os << "    " << tree.root->key << "[label=\"key:" << tree.root->key << " bal:" << tree.root->balance << "\"]" << endl; //print root

        printToOs(os, tree.root->key, tree.root->balance,tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->balance,tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}


const int AvlTree::getSymSuccessor(const int value) {
    if(root == nullptr)
       return 0;
    auto suc = root->getSymSuccessor(value);
    return (suc == nullptr) ? 0 : suc->key;
}

const int AvlTree::getSymPredecessor(const int value) {
    if (root == nullptr)
        return 0;
    auto pre = root->getSymPredecessor(value);
    return (pre == nullptr) ? 0 : pre->key;
}

