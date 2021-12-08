#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include "CellData.h"
#include <cmath>

using std::cout;
using std::ostream;

LinkedList::LinkedList() {
    this->head = nullptr;
}

LinkedList::~LinkedList() {
    Node *tmp = this->head;
    Node *temp;
    while(tmp) {
        temp = tmp->next;
        delete tmp;
        tmp = temp;
    }
    tmp = temp = NULL;
}

LinkedList::LinkedList(const LinkedList& source) {
    if(source.head == nullptr)
        return;

    Node* dummyHead = new Node();
    Node* curr = dummyHead;
    Node* temp = source.head;
    while (temp != nullptr) { // deep copy
        Node* newNode = new Node(temp->data.id,temp->data.fov,temp->data.volume,temp->data.center_x,temp->data.center_y,temp->data.min_x,temp->data.max_x,temp->data.min_y,temp->data.max_y);
        curr->next = newNode;
        curr = curr->next;
        temp = temp->next;
    }
    this->head = dummyHead->next;
    delete curr;
    delete dummyHead;
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
    if (this == &source) return *this; // self-assignment

    Node **tmp = &head;
    for (Node *src = source.head; src; src = src->next) {
        Node *temp = new Node;
        temp->data = src->data;
        temp->next = nullptr;

        *tmp = temp;
        tmp = &temp->next;
    }

    return *this;
}

void LinkedList::insert(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y) {
    /*CellData curr; // ID, fov,volume,center_x,center_y,min_x,max_x,min_y,max_y
    curr.id = id;
    curr.fov = fov;
    curr.volume = volume;
    curr.center_x = center_x;
    curr.center_y = center_y;
    curr.min_x = min_x;
    curr.min_y = min_y;
    curr.max_x = max_x;
    curr.max_y = max_y;*/
    Node* newNode = new Node(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);

    Node *tmp = this->head;
    Node *temp;
    while(tmp) {
        temp = tmp->next;
        tmp = temp;
    }
    tmp->next = newNode;
}

void LinkedList::remove(std::string id) {
    Node *tmp = this->head;
    Node *temp;
    while(tmp) {
        if(tmp->next->data.id == id) {
            if(tmp->next->next != nullptr) {
                delete temp->next;
                tmp->next = tmp->next->next;
            }
        }
        temp = tmp->next;
        tmp = temp;
    }
}

void LinkedList::clear() {
    Node *tmp = this->head;
    Node *temp;
    while(tmp) {
        temp = tmp->next;
        delete tmp;
        tmp = temp;
    }
    delete temp;
    tmp = temp = NULL;
    this->head = nullptr;
}

std::string LinkedList::print() const {
    std::string ret = "id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y";
   	Node *tmp = this->head;
    while(tmp) {
        //ret = ret + std::to_string(tmp->data.id) + std::to_string(tmp->data.fov) + std::to_string(tmp->data.volume) + std::to_string(tmp->data.center_x) + std::to_string(tmp->data.center_y) + std::to_string(tmp->data.min_x) + std::to_string(tmp->data.max_x) + std::to_string(tmp->data.min_y) + std::to_string(tmp->data.max_y) + "\n";
        tmp = tmp->next;
    }
    return ret;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}

// given a fov number, count the cells observed in that fov
int LinkedList::countN(int fov) {
	/* Do not modify this function */
    int count = 0;
    Node* cur = head;
    while (cur)
    {
        if (cur->data.fov == fov)
            count++;
        cur = cur->next;
    }
    return count;
}

/* given a fov number, compute the average volume of all the cells observed in
 * that fov
 */
double LinkedList::average(int fov) {
    int count = countN(fov);
    int sum = 0;
    if (count == 0)
        return -1;

    Node* cur = head;
    while (cur)
    {
        if (fov == cur->data.fov){
            sum += (cur->data.volume);
        }
            
        cur = cur->next;
    }

    return sum/count;
    return 0;
}

/* given a fov number, compute the variance volume of all the cells observed in
 * that fov
 */
double LinkedList::variance(int fov) {
	/* Do not modify this function */
    double sum = 0;
    double avg = average(fov);
    int count = countN(fov);

    if (count == 0)
        return -1;

    Node* cur = head;
    while (cur)
    {
        if (fov == cur->data.fov)
            sum += (cur->data.volume - avg) * (cur->data.volume - avg);
        cur = cur->next;
    }

    return sum/count;
}

/* given a fov number, remove outliers
 */
std::string LinkedList::outliers(int fov, int k, int N) {
    int rem = 0;
    if( countN(fov) < N) {
        return "Less than " + std::to_string(N) + "cells in fov " + std::to_string(k);
    } else {
        Node *tmp = this->head;
        Node *temp;
        while(tmp) {
            if(tmp->next->data.fov == fov) {
                if(
                    (tmp->next->data.volume >= average(fov) - k * std::sqrt( variance(fov) )) ||
                    (tmp->next->data.volume <= average(fov) + k * std::sqrt( variance(fov) ))
                ) {
                    delete temp->next;
                    tmp->next = tmp->next->next;
                }
            }
            temp = tmp->next;
            tmp = temp;
        }
    }
    return std::to_string(rem) + " cells are removed";
}

