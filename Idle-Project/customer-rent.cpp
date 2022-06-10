#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "customer-rent.h"
#include "videos.h"

using namespace std;
using namespace ns;

// Constructor
CustomerRentList::CustomerRentList() {
    top = NULL;
    stackSize = 0;

    ifstream file("customer-rent.txt");
    string customerId, videoId;
    int cId, vId;

    if(file.is_open()) {
        while(!file.eof()) {
            getline(file, customerId, ',');
            getline(file, videoId, '\n');

			if(!customerId.empty()) {
				cId = stoi(customerId);
                vId = stoi(videoId);
				customerRentPush(cId, vId);
			}
        }
    }
	file.close();
}

CustomerRentList::~CustomerRentList()  {
    ofstream file("customer-rent.txt");
    CustomerRentNode *nodePtr, *nextNode;
    nodePtr = top;
    if(file.is_open()) {
		while (nodePtr) {
			file << nodePtr->customerId << "," << nodePtr->videoId << endl;
			nodePtr = nodePtr->next;
		}
	}
	file.close();
}

void CustomerRentList::customerRentPush(int cusId, int vidId) {
    CustomerRentNode *newNode;

    // Allocate a new node & store data
    newNode = new CustomerRentNode;
    newNode->customerId = cusId;
    newNode->videoId = vidId;

    // If there are no nodes in the list
    // make newNode the first node
    if (isEmpty()) {
        top = newNode;
        newNode->next = NULL;
    } else {
    // Otherwise, insert NewNode before top
        newNode->next = top;
        top = newNode;
    }
    stackSize++;
}

void CustomerRentList::customerRentPop(int id, VideoList &v){
    stack< int, vector<int> > cStack;
    stack< int, vector<int> > vStack;

    int cId, vId,oSize = stackSize, temp;
    CustomerRentNode *nodePtr;
    nodePtr = top;

    if(isEmpty()) {
        cout << "\nCustomer has no Rented Videos." << endl << endl;
        return;
    } else {
        for(int i = 0; i < oSize; i++) {
            cId = top->customerId;
            vId = top->videoId;
            nodePtr = top->next;

            if(top->customerId == id) {
                cout << "Video ID: " << top->videoId << endl;
                v.returnVideo(top->videoId);
            } else {
                cStack.push(cId);
                vStack.push(vId);
            }
            delete top;
            top = nodePtr;
        }
    }

    // Data to be return to the Stack
    if(!cStack.empty()) {
        for(int i = 0; i < cStack.size(); i++) {
            customerRentPush(cStack.top(), vStack.top());
            cStack.pop();
            vStack.pop();
        }
    }
}

void CustomerRentList::customerRentList(int id) {
    VideoList v;
    bool empty = true;
	CustomerRentNode *nodePtr;
    nodePtr = top;
    string temp;

    while (nodePtr) {
        if(nodePtr->customerId == id) {
            temp = v.videoTitle(nodePtr->videoId);
            cout << "Video ID: " << nodePtr->videoId << endl;
            cout << "Movie Title: " << temp <<endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    if(empty)
        cout << "\nNo Video Rented Found." << endl << endl;
}

bool CustomerRentList::isEmpty() {
    bool status;
    if (!top)
        status = true;
    else
        status = false;
    return status;
}