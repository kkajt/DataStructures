//
// Created by Kajetan on 08/05/2018.
//

#ifndef ZAD1_HEADER_H
#define ZAD1_HEADER_H
#include <iostream>
#include <string>
using namespace std;

enum color { BLACK, RED };

struct counter {

    double time_total;
    double time_executing;
    double time_load;
    unsigned insert_num;
    unsigned delete_num;
    unsigned load_num;
    unsigned find_num;
    unsigned min_num;
    unsigned max_num;
    unsigned inorder_num;
    unsigned successor_num;
    unsigned max_elem_num;
    unsigned end_elem_num;

    counter() {
        this->time_total = 0.0;
        this->time_executing = 0.0;
        this->time_load = 0.0;
        this-> insert_num=0;
        this-> delete_num=0;
        this-> load_num=0;
        this-> find_num=0;
        this-> min_num=0;
        this-> max_num=0;
        this-> inorder_num=0;
        this-> successor_num=0;
        this-> max_elem_num=0;
        this-> end_elem_num=0;
    }
};


struct DataStructureElement {
    string value;
};

struct listElement:DataStructureElement {
    struct listElement *next;
};

struct BSTNode:DataStructureElement {
    BSTNode *left;
    BSTNode *right;
    BSTNode *parent;
    BSTNode(string val) {
        this->value = val;
    }

    BSTNode(string val, BSTNode *left, BSTNode *right) {
        this->value = val;
        this->left = left;
        this->right = right;
        this->parent = NULL;
    }
};


struct RBTNode:DataStructureElement {

    enum color col;
    RBTNode *left;
    RBTNode *right;
    RBTNode *parent;
    RBTNode(string val) {
        this->value = val;
    }

    RBTNode(string val, RBTNode *left, RBTNode *right, RBTNode *parent) {
        this->value = val;
        this->left = left;
        this->right = right;
        this->parent = parent;
        this->col = BLACK;
    }
};

class DataStructure {
private:
    unsigned size;
public:

    virtual unsigned getsize() = 0;
    virtual void insert(string) = 0;
    virtual void deleteelement(string) = 0;
    virtual void find(string) = 0;
    virtual void min() = 0;
    virtual void max() = 0;
    virtual void successor(string) = 0;
    virtual void inorder() = 0;
    virtual DataStructureElement* getAndDeleteElement() = 0;
};

class BST:public DataStructure {

private:
    unsigned size;

public:
    virtual void insert(string) override;
    virtual void deleteelement(string) override;
    virtual void find(string) override;
    virtual void min() override;
    virtual void max() override;
    virtual void successor(string) override;
    virtual void inorder() override;
    virtual DataStructureElement* getAndDeleteElement() override;
    virtual unsigned getsize() override;

    BST();
    BSTNode *root = NULL;
    void insertBST(string str);
    void deleteBST(string val);
    BSTNode* findBST(BSTNode *x, string value);
    BSTNode* minBST(BSTNode *x);
    BSTNode* maxBST(BSTNode *x);
    BSTNode* successorBST(BSTNode *x);
    void inorderBST(BSTNode *x);

};

class RBT:public DataStructure {

private:
    void rotateLeft(RBTNode*);
    void rotateRight(RBTNode*);
    void insertfixup(RBTNode*);
    void deletefixup(RBTNode* x);
    RBTNode* deleteWithoutRecolor(RBTNode*);
    unsigned size;
    RBTNode* NIL;

public:
    RBTNode *root;

    RBT();
    virtual unsigned getsize() override;
    virtual void insert(string) override;
    virtual void deleteelement(string) override;
    virtual void find(string) override;
    virtual void min() override;
    virtual void max() override;
    virtual void successor(string) override;
    virtual void inorder() override;
    virtual DataStructureElement* getAndDeleteElement() override;

    void insertRBT(string str);
    RBTNode* deleteRBT(string val);
    RBTNode* findRBT(RBTNode *x, string value);
    RBTNode* minRBT(RBTNode *x);
    RBTNode* maxRBT(RBTNode *x);
    RBTNode* successorRBT(RBTNode *x);
    void inorderRBT(RBTNode *x);
    ~RBT();

};

class HMap:public DataStructure {

private:
    string prepareString(string str);
    int nt;
    unsigned size;

public:

    DataStructure *T[128];
    HMap();
    ~HMap();


    virtual unsigned getsize() override;
    virtual void insert(string) override;
    virtual void deleteelement(string) override;
    virtual void find(string) override;
    virtual void min() override;
    virtual void max() override;
    virtual void successor(string) override;
    virtual void inorder() override;
    virtual DataStructureElement* getAndDeleteElement() override;

    void listToRBTree(int index);
    void RBTreeToList(int index);
    void setnt(int nt);


};


class List:public DataStructure {
private:
    unsigned size;
    listElement* head;
public:
    List();
    ~List();

    listElement* findElement(string);
    void deleteFirstElement();

    virtual unsigned getsize() override;
    virtual void insert(string) override;
    virtual void deleteelement(string) override;
    virtual void find(string) override;
    virtual void min() override;
    virtual void max() override;
    virtual void successor(string) override;
    virtual void inorder() override;
    virtual DataStructureElement* getAndDeleteElement() override;
};




#endif //ZAD1_HEADER_H
