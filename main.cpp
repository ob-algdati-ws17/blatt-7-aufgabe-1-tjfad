#include <iostream>
#include <fstream>
#include <sstream>

#include "AvlTree.h"

using namespace std;

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v);

int main(int argc, const char *argv[]) {
    auto treeToPng = [](AvlTree *tree) {
        ofstream myfile;
        myfile.open("tree.dot");
        myfile << *tree;
        myfile.close();
        system("dot -Tpng tree.dot -o tree.png");
    };
    int val;
    AvlTree *tree = new AvlTree();
    for (int i = 1; i < argc; i++) {
        std::istringstream iss(argv[i]);
        iss >> val;
        tree->insert(val);
    }
    char action = '\0';
    treeToPng(tree);
    while (action != 'q') {
        switch (action) {
            case '\0': // dummy
                break;
            case 's':
                cout << "Search: ";
                cin >> val;
                cout << (tree->search(val) ? "" : "not ") << "found" << endl;
                break;
            case 'd':
                cout << "Delete: ";
                cin >> val;
                tree->remove(val);
                break;
            case 'i':
                cout << "Insert: ";
                cin >> val;
                tree->insert(val);
                break;
            case 't':
                char order;
                cout << "p(o)storder, (i)norder, p(r)eorder? ";
                cin >> order;
                vector<int> *vec;
                switch (order) {
                    case 'o':
                        vec = tree->postorder();
                        if (vec == nullptr)
                            cout << "emoty tree" << endl;
                        else
                            cout << *vec << endl;
                        break;
                    case 'i':
                        vec = tree->inorder();
                        if (vec == nullptr)
                            cout << "emoty tree" << endl;
                        else
                            cout << *vec << endl;
                        break;
                    case 'r':
                        vec = tree->preorder();
                        if (vec == nullptr)
                            cout << "emoty tree" << endl;
                        else
                            cout << *vec << endl;
                        break;
                    default:
                        cout << "Order unknown" << endl;
                        break;
                }
                break;
            default:
                cout << "Unknown command: " << action << endl;
                break;
        }
        if (action == 'i' || action == 'd')
            treeToPng(tree);
        cout << "(s)earch, (d)elete, (i)nsert, (t)raverse, (q)uit: ";
        cin >> action;
    }
    cout << "Cheerio!" << endl;
    return 0;
}

template<typename T>
ostream &operator<<(ostream &out, const vector<T> &v) {
    out << "[";
    size_t last = v.size() - 1;
    for (size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << "]";
    return out;
}
