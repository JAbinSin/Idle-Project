#include <iostream>
#include <fstream>
#include "customers.h"

using namespace std;
using namespace ns;

// Constructor
CustomerList::CustomerList(void) {
    front = NULL;
    rear = NULL;
    queueSize = 0;

    ifstream file("customers.txt");
    string id, name, address;
    int cId;

    if(file.is_open()) {
        while(!file.eof()) {
            getline(file, id, ',');
            getline(file, name, ',');
            getline(file, address, '\n');

			if(!id.empty()) {
				cId = stoi(id);
				customerEnqueue(cId, name, address);
			}
        }
    }
	file.close();
}

// Deconstructor
CustomerList::~CustomerList() {
    ofstream file("customers.txt");
    CustomerNode *nodePtr, *nextNode;
    nodePtr = front;

    if(file.is_open()) {
		while (nodePtr) {
			file << nodePtr->customerId << "," << nodePtr->customerName << "," << nodePtr->customerAddress << endl;
			nodePtr = nodePtr->next;
		}
	}
	file.close();
}

// Used for the Auto Incremention of the Video ID
int CustomerList::autoCustomerIdIncrement() {
    int id = 0;
	CustomerNode *nodePtr;
    nodePtr = front;
    while(nodePtr) {
        id = nodePtr->customerId;
		nodePtr = nodePtr->next;
    }
    return id+1;
}

void CustomerList::customerEnqueue(int cusId, string name, string address) {
    int id;
    if(cusId == 0) {
		//Get the next Video ID
    	id = autoCustomerIdIncrement();
	} else {
		id = cusId;
	}

    CustomerNode *newNode;
    newNode = new CustomerNode;
    newNode->customerId = id;
    newNode->customerName = name;
    newNode->customerAddress = address;
    newNode->next = NULL;
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
    rear->next = newNode;
    rear = newNode;
    }
    queueSize++;
}

void CustomerList::customerDetails(int id) {
    bool empty = true; // Use to check if there is a Video found or not
	CustomerNode *nodePtr;
    nodePtr = front;

    while (nodePtr) {
        if(nodePtr->customerId == id) {
            cout << "Name: " << nodePtr->customerName << endl;
            cout << "Address: " << nodePtr->customerAddress << endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    if(empty)
        cout << "\nNo Matching Customer ID Found." << endl << endl;
}

bool CustomerList::isEmpty() {
    bool status;

    if (queueSize)
        status = false;
    else
        status = true;
    return status;
}