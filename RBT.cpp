//
// Created by Kajetan on 09/05/2018.
//
#include <iostream>
#include <string.h>
#include "header.h"

using namespace std;


// initializes NIL node, sets root value to NIL and size to -
RBT::RBT() {
    this->NIL = new RBTNode("", this->NIL, this->NIL, this->NIL);
    this->root = NIL;
    this->size=0;
}

// invokes insert method specific for RBT
void RBT::insert(string s) {
    RBT::insertRBT(s);
}

// if specific for RBT delete method retuns element different to NIL, deletes it, does nothing otherwise
void RBT::deleteelement(string s) {
    RBTNode* tmp = RBT::deleteRBT(s);
    if (tmp!= this->NIL) delete tmp;
}

// if specific for RBT find method retuns element different to NIL, prints 1 to cout, prints 0 otherwise
void RBT::find(string s) {
    if (RBT::findRBT(this->root, s) != this->NIL ) cout<<"1"<<endl;
    else cout<<"0"<<endl;
}

// finds and prints minimum value to cout, prints empty line when such doesn't exist
void RBT::min() {
    RBTNode* tmp = RBT::minRBT(this->root);
    if (tmp!= this->NIL) cout<<tmp->value<<endl;
    else cout<<endl;
}

// finds and prints maximum value to cout, prints empty line when such doesn't exist
void RBT::max() {
    RBTNode* tmp = RBT::maxRBT(this->root);
    if (tmp!= this->NIL) cout<<tmp->value<<endl;
    else cout<<endl;
}

// finds and prints succesor value to cout, prints empty line when such doesn't exist
void RBT::successor(string k) {
    RBTNode* f = RBT::findRBT(this->root,k);
    if(f!= this->NIL) cout<<f->value<<endl;
    else cout<<endl;
}

// prints values of RB tree in order if there are elements, otherwise prints empty line
void RBT::inorder() {
    RBT::inorderRBT(this->root);
    cout<<endl;
}

// performs left rotation on element x
void RBT::rotateLeft(RBTNode *x) {
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left != this->NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == this->NIL) {
        this->root = y;
    }
    else if (x == x->parent->left) {
            x->parent->left = y;
    }
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// performs right rotation on element x
void RBT::rotateRight(RBTNode *x) {
    RBTNode* y = x->left;
    x->left = y->right;
    if (y->right != this->NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == this->NIL) {
        this->root = y;
    }
    else if (x == x->parent->right) {
            x->parent->right = y;
    }
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// inserts specified string value to RBT
void RBT::insertRBT(string str) {
    // z is new element in tree
    RBTNode* z = new RBTNode(str, this->NIL, this->NIL, this->NIL);
    RBTNode* y = this->NIL;
    RBTNode* x = this->root;
    // first regular BST insert

    // finds place where value should be insert (goes down to the leaf of RBT)
    while(x!=this->NIL) {
        y=x;
        if (z->value < x->value) {
            x = x-> left;
        }
        else x = x->right;
    }
    z->parent = y;
    // if y == NIL, means that tree was empty
    if (y==this->NIL) {
        this->root = z;
    }
    // if tree wasn't empty, we need to set parent right/left value to our new element
    else {
        if (z->value < y->value) y->left =z;
        else y->right =z;
    }
    // set right, left and color value of new element
    z->left = this->NIL;
    z->right = this->NIL;
    z->col = RED;
    // after adding element, need to fix colors and balance if needed
    RBT::insertfixup(z);
    // ensure that root parent is always NIL
    this->root->parent = this->NIL;
    // increases RBT size
    this->size++;
}

void RBT::insertfixup(RBTNode *z) {
    RBTNode* y;
    while(z->parent->col == RED) { // z->col=RED
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if (y->col == RED) {
                // case 1
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    // case 2
                    z = z-> parent;
                    rotateLeft(z);
                }
                // case 3
                z->parent->col = BLACK;
                z->parent->parent->col = RED;
                rotateRight(z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if (y->col == RED) {
                // case 1
                z->parent->col = BLACK;
                y->col = BLACK;
                z->parent->parent->col = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    // case 2
                    z = z-> parent;
                    rotateRight(z);
                }
                // case 3
                z->parent->col = BLACK;
                z->parent->parent->col = RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    this->root->col = BLACK;
}
/*
 * case 1 - brother y of z parent is red
 * case 2 - brother y of z parent is black and z is right(left) child
 * case 3 - brother y of z parent is black and is left(right) child
 */

// takes out element of specified value if such exists and return it, returns NIL otherwise
RBTNode* RBT::deleteRBT(string val) {
    RBTNode* z = RBT::findRBT(this->root, val), *y, *x;
    // if find returned NIL, that means that there is no such element in RBT
    if (z == this->NIL) return this->NIL;

    // first we need to select element that will be actually deleted
    // if specified element has 0 or 1 child, then we delete this element,
    // if has two children, then we'll 'delete successor' (but puts its value in z element)
    if (z->left == this->NIL || z->right == this->NIL) y = z;
    else y = RBT::successorRBT(z);
    // if element to delete has child, set it to x (it will always have no more than 1 child!)
    if (y->left != this->NIL) x = y->left;
    else x = y->right;
    // set new x.parent value to element to be deleted parent
    x->parent = y->parent;
    //if y was root, set x as new root
    if (y->parent == this->NIL) this->root = x;
    else {
        // set y parent child value to x (instead of y)
        if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
    }
    // if y was successor of z, then change their values
    if (y!=z) {
        z->value = y->value;
    }
    // after delete ther's need to fix colors and balance
    if (y->col == BLACK) RBT::deletefixup(x);
    this->size--;
    return y;

}

void RBT::deletefixup(RBTNode* x) {
    RBTNode *w;
    while (x!=this->root && x->col == BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;
            if (w->col == RED) {
                // case 1
                w->col = BLACK;
                x->parent->col = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->col == BLACK && w->right->col == BLACK) {
                // case 2
                w->col = RED;
                x=x->parent;
            }
            else {
                if (w->right->col == BLACK) {
                    // case 3
                    w->left->col = BLACK;
                    w->col = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                // case 4
                w->col = x->parent->col;
                x->parent->col = BLACK;
                w->right->col = BLACK;
                rotateLeft(x->parent);
                x = this->root;
            }
        }
        else {
            w = x->parent->left;
            if (w->col == RED) {
                // case 1
                w->col = BLACK;
                x->parent->col = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->col == BLACK && w->left->col == BLACK) {
                // case 2
                w->col = RED;
                x=x->parent;
            }
            else {
                if (w->left->col == BLACK) {
                    // case 3
                    w->right->col = BLACK;
                    w->col = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                // case 4
                w->col = x->parent->col;
                x->parent->col = BLACK;
                w->left->col = BLACK;
                rotateRight(x->parent);
                x = this->root;
            }
        }
    }
     x-> col = BLACK;
}
/*
 * case 1 - brother w of node x is red
 * case 2 - brother w of x node is black, and both children are black
 * case 3 - brother of x node is black, left(right) child is red and right(left) child of w is black
 * case 4 - borther w of x node is black, and right(left) child of w is red
 */

// performs inorder walk on RBT
void RBT::inorderRBT(RBTNode *x) {
    if (x != this->NIL) {
        inorderRBT(x->left);
        cout<<x->value<<" ";
        inorderRBT(x->right);
    }
}

// returns node of specified value below x node if such exists, NIL otherwise
RBTNode* RBT::findRBT(RBTNode *x, string value) {
    while(x!= this->NIL && value != x->value) {
        if (value<x->value) {
            x = x->left;
        }
        else x = x->right;
    }
    return x;
}

// returns minimum element below specified node x
RBTNode* RBT::minRBT(RBTNode *x) {
    if (x == this->NIL) return x;
    while (x->left!=this->NIL) {
        x = x-> left;
    }
    return x;
}

// returns maximum element below specified node x
RBTNode* RBT::maxRBT(RBTNode *x) {
    if (x == this->NIL) return x;
    while (x->right!=this->NIL) {
        x = x-> right;
    }
    return x;
}

// returns successor of specified node x
RBTNode* RBT::successorRBT(RBTNode *x) {
    if (x->right != this->NIL) return minRBT(x->right);
    RBTNode* y = x->parent;
    while (y!=this->NIL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}
// does the same as regular delete, but withour fixing color - it is used when RBT is changed to List in HMap, there is
// no need to care about colors
RBTNode* RBT::deleteWithoutRecolor(RBTNode* z) {
    RBTNode *y, *x;
    if (z == this->NIL) return this->NIL;

    if (z->left == this->NIL || z->right == this->NIL) y = z;
    else y = RBT::successorRBT(z);
    if (y->left != this->NIL) x = y->left;
    else x = y->right;
    x->parent = y->parent;
    if (y->parent == this->NIL) this->root = x;
    else {
        if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
    }
    if (y!=z) {
        z->value = y->value;
    }
    this->size--;
    return y;
}

// returns minimum element from RBT if such exists, nullptr otherwise
DataStructureElement* RBT::getAndDeleteElement() {
    RBTNode* tmp = RBT::minRBT(this->root);
    if (tmp == this->NIL) return nullptr;
    return RBT::deleteRBT(tmp->value);
}

// destructor deletes each element
RBT::~RBT() {
    while(root!=this->NIL) {
        delete RBT::deleteWithoutRecolor(RBT::minRBT(this->root));
    }
}
// returns size of RBT
unsigned RBT::getsize() { return this-> size; }
