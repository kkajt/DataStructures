//
// Created by Kajetan on 10/05/2018.
//
#include <iostream>
#include "header.h"
#include <functional>


using namespace std;

// constructor initializes array with linked lists, and sets default constant nt value to 130
HMap::HMap() {
    for (int i=0; i<128; i++) {
        this->T[i] = new List();
        //this->T[i] = new RBT();
    }
    this->size=0;
    this->nt=130;
}

// destructor deletes each element of array
HMap::~HMap() {
    for (int i=0; i<128; i++) {
        delete T[i];
    }
}

// sets constant nt value
void HMap::setnt(int nt) {
    this->nt = nt;
}

// inserts specified string to hmap
void HMap::insert(string s) {
    hash<string> hf;
    int i = hf(s) % 128;
    T[i] -> insert(s);
    this->size++;
    if (T[i]->getsize() == this->nt ) {
        HMap::listToRBTree(i);
    }
}

// deletes specified string from hmap if such exists, otherwise does nothing
void HMap::deleteelement(string s) {
    hash<string> hf;
    int i = hf(s) % 128;
    int s1 = T[i]->getsize();
    T[i] -> deleteelement(s);
    int s2= T[i]->getsize();
    if (s1>s2) this->size--;
    if (T[i]->getsize()== this->nt -10) this->RBTreeToList(i);
}

// invokes find function on array element - this would print 1 when element is found, 0 otherwise
void HMap::find(string s) {
    hash<string> hf;
    int i = hf(s) % 128;
    T[i] -> find(s);
}

// does nothing - there's no order in hmap
void HMap::min() {
    cout<<endl;
}

// does nothing - there's no order in hmap
void HMap::max() {
    cout<<endl;
}

// does nothing - there's no order in hmap
void HMap::successor(string s) {
    cout<<endl;
}

// does nothing - there's no order in hmap
void HMap::inorder() {
    cout<<endl;
}

// transformates T[index] array element from list to RBTree (invoked when T[i].size = nt after inserting element)
void HMap::listToRBTree(int index) {
    DataStructureElement* tmp = T[index]->getAndDeleteElement();
    RBT* tree = new RBT();
    while(tmp != nullptr) {
        tree->insertRBT(tmp->value);
        delete tmp;
        tmp = T[index]->getAndDeleteElement();
    }
    DataStructure* old = T[index];
    T[index] = tree;
    delete old;
}
// transformates T[index] array element from RBTree to List (invoked when T[i].size = nt-10 after deleting element)
void HMap::RBTreeToList(int index) {
    DataStructureElement* tmp = T[index]->getAndDeleteElement();
    List* list = new List();
    while(tmp != nullptr) {
        list->insert(tmp->value);
        delete tmp;
        tmp = T[index]->getAndDeleteElement();
    }
    DataStructure* old = T[index];
    T[index] = list;
    delete old;
}
// does nothing
DataStructureElement* HMap::getAndDeleteElement() {
    return nullptr;
}

//returns total size of hmap
unsigned HMap::getsize() { return this-> size; }
