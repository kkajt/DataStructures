#include <iostream>
#include "header.h"

using namespace std;

// sets size to 0
BST::BST() {
    this->size = 0;
}

// invokes specific for BST insert method
void BST::insert(string s) {
    BST::insertBST(s);
}

// invokes specific for BST delete method
void BST::deleteelement(string s) {
    BST::deleteBST(s);
}

// if specified string is found in BST prints 1, 0 otherwise
void BST::find(string s) {
    if (BST::findBST(this->root, s)!= nullptr) cout<<"1"<<endl;
    else cout<<"0"<<endl;
}

// prints minimum value in BST if such exists, empty line otherwise
void BST::min() {
    BSTNode* tmp = BST::minBST(this->root);
    if (tmp!=nullptr) cout<<tmp->value<<endl;
    else cout<<endl;
}

// prints maximum value in BST if such exists, empty line otherwise
void BST::max() {
    BSTNode* tmp = BST::maxBST(this->root);
    if (tmp!=nullptr) cout<<tmp->value<<endl;
    else cout<<endl;
}

void BST::successor(string k) {
    BSTNode* f = BST::findBST(this->root,k);
    if(f!= nullptr) cout<<f->value<<endl;
    else cout<<endl;
}
// invokes specific for BST inorder method on root
void BST::inorder() {
    BST::inorderBST(this->root);
    cout<<endl;
}

// inserts specified string value to BST
void BST::insertBST(string str) {
    BSTNode* y = nullptr;
    BSTNode* x = this -> root;
    // first finds place where to insert (finds parent)
    while(x!=nullptr) {
        y = x;
        if (str<x->value) {
            x = x->left;
        }
        else x = x->right;
    }
    // creates new node with specified value
    BSTNode *toAdd = new BSTNode(str, nullptr, nullptr);
    // set found parent as new element parent
    toAdd->parent= y;
    // if BST is empty, set new element as root
    if (y == nullptr) {
        this->root = toAdd;
    }
    else {
        // if element is greater or equal to parent, set is as right son, set is as left otherwise
        if (str<y->value) {
            y->left = toAdd;
        }
        else y->right = toAdd;
    }
    this->size++;
}

// deletes single occurence of specified value from BST if such exists, does nothing otherwise
void BST::deleteBST(string val) {
    // find specified element
    BSTNode* z = findBST(this->root, val);
    // if such doesn't exist, return
    if (z==nullptr) return;
    BSTNode *y, *x;
    // select element to be deleted - this is element of our value or its successor if it has 2 children
    if (z->left == nullptr || z->right ==nullptr) {
        y = z;
    }
    else y = successorBST(z);
    // set x as child of element to be deleted, if such exists
    if (y->left != nullptr) {
        x = y->left;
    }
    else x= y->right;
    // if that child existed, set it parent to parent of element to be deleted
    if (x!=nullptr) {
        x->parent = y->parent;
    }
    // if element to be deleted parent was nullptr, that means that he was root and we need to reset it
    if (y->parent == nullptr) {
        this->root = x;
    }
    else {
        // if y was left(right) child, set y child as left(right) parent child
        if (y== y->parent->left) {
            y->parent->left = x;
        }
        else y->parent->right = x;
    }
    // if element to be deleted was successor of element with specified value, swap those values
    if (y!=z) {
        z->value = y->value;
    }
    this->size--;
    delete y;
}

// returns BSTNode of specified value if such exists, nullptr otherwise
BSTNode* BST::findBST(BSTNode *x, string value) {
    while(x!= nullptr && value!=x->value) {
        if (value<x->value) {
            x = x->left;
        }
        else x = x->right;
    }
    return x;
}

// returns minimum element from BST if such exists, nullptr otherwise
BSTNode* BST::minBST(BSTNode *x) {
    if (x == nullptr) return x;
    while (x->left!=nullptr) {
        x = x-> left;
    }
    return x;
}
// returns maximum element from BST if such exists, nullptr otherwise
BSTNode* BST::maxBST(BSTNode *x) {
    if (x == nullptr) return x;
    while (x->right!=nullptr) {
        x = x-> right;
    }
    return x;
}

// returns successor of specified node if such exists, nullptr otherwise
BSTNode* BST::successorBST(BSTNode *x) {
    if (x->right != nullptr) return minBST(x->right);
    BSTNode* y = x->parent;
    while (y!=nullptr && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// performs inorder walk on specified node, prints it to cout
void BST::inorderBST(BSTNode *x) {
    if (x != nullptr) {
        inorderBST(x->left);
        cout<<x->value<<" ";
        inorderBST(x->right);
    }
}

// does nothing, this method is never used
DataStructureElement* BST::getAndDeleteElement() {
    return nullptr;
}

// returns size of BST
unsigned BST::getsize() { return this-> size; }