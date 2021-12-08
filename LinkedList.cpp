#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include "CellData.h"
#include <cmath>

using std::cout;
using std::string;
using std::ostream;

LinkedList::LinkedList() {
    // Implement this function
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
    
}

LinkedList& LinkedList::operator=(const LinkedList& source) 
{
    // Implement this function
    return LinkedList::operator=(source);
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
    this->insert(newNode)''
}

void LinkedList::remove(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y) {
    // Implement this function
}

void LinkedList::clear() {	
    // Implement this function
}

string LinkedList::print() const {
   	// Implement this function
    return "TEST";
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
    // Implement this function
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
string LinkedList::outliers(int fov, int k, int N) {
    // Implement this function
    return "TEST";
}

