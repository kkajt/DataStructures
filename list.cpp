//
// Created by Kajetan on 10/05/2018.
//

#include <iostream>
#include "header.h"

using namespace std;

// constructor sets size to 0 and head to nullptr
List::List() {
    this->size = 0;
    this->head = nullptr;
}

// inserts specified string to list
void List::insert(string s) {
    listElement* n = new listElement();
    n -> value = s;
    if (this->head == nullptr) {
        n->next = nullptr;
    }
    else n->next = head;
    this->head = n;
    this->size++;

    /*
     * if want to add to the end, use below:
    n -> next = nullptr;
    listElement *tmp = this -> head;
    if (this -> size != 0) {
        while(tmp -> next) {
            tmp = tmp -> next;
        }
        tmp -> next = n;
    }
    else {
        this -> head = n;
    }
    this -> size++;*/
}

// delets specified string from list if such exists, otherwise does nothing
void List::deleteelement(string s) {
    listElement* tmp = this -> head;
    if (tmp == nullptr) {
        return ;
    }
    if (tmp->value == s) {
        this -> head = tmp->next;
        delete tmp;
        this->size--;
        return ;
    }
    else if (tmp->next == nullptr) {
        return;
    }
    listElement *prev;
    while(tmp->next != nullptr) {
        if (tmp->next->value == s) {
            prev = tmp;
            tmp = tmp->next;
            prev->next = tmp->next;
            delete tmp;
            this->size--;
            return;
        }
        tmp = tmp->next;
    }
}

// finds and returns element of specified string value if such exists, nullptr otherwise
listElement* List::findElement(string s) {
    listElement* tmp = this -> head;
    while(tmp != nullptr) {
        if (tmp -> value == s) return tmp;
        tmp = tmp -> next;
    }
    return nullptr;
}

// deletes first (head) element from list
void List::deleteFirstElement() {
    listElement* tmp = this->head;
    if (tmp != nullptr) {
        this->head = tmp->next;
    }
    delete tmp;
}

// does nothing (is not neccessary for this programme because is used only in hmap which has no order)
void List::successor(string s) {
    return;
}

// does nothing (is not neccessary for this programme because is used only in hmap which has no order)
void List::inorder() {

}

// does nothing (is not neccessary for this programme because is used only in hmap which has no order)
void List::max() {

}

// does nothing (is not neccessary for this programme because is used only in hmap which has no order)
void List::min() {

}

// prints 1 if specified string value is found in list, 0 otherwise
void List::find(string s) {
    listElement* tmp = List::findElement(s);
    if (tmp != nullptr) cout<<"1"<<endl;
    else cout<<"0"<<endl;
}

// deletes all list elements
List::~List() {
    while(this->head != nullptr) {
        deleteFirstElement();
    }
}

// takes out and returns first element from list if such exists, returns nullptr otherwise
DataStructureElement* List::getAndDeleteElement() {
    listElement* tmp = this -> head;
    if (tmp != nullptr) this->head = tmp->next;
    return tmp;
}

// returns list size
unsigned List::getsize() { return this-> size; }