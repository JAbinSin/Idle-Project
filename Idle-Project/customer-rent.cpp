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
    // Set the variables to be default for the Customer Rent Stack
    top = NULL;
    stackSize = 0;

    // Local Variables
    string customerId, videoId;
    int cId, vId;

    // Set the path for the customer-rent.txt file/csv
    // File Read
    ifstream file("customer-rent.txt");

    // Check if the file can be access, otherwise not display an error
    if(file.is_open()) {
        // Loop while there is a Node in the Customer Rent Stack
        while(!file.eof()) {
            // Store the data from the customer-rent.txt to the local variables
            getline(file, customerId, ',');
            getline(file, videoId, '\n');

            // If the data is not empty
			if(!customerId.empty()) {
                // Insert the data from the local variable to the Customer Rent Stack
				cId = stoi(customerId);
                vId = stoi(videoId);
				customerRentPush(cId, vId);
			}
        }
    } else {
        // Display an Error when the customersrent-.txt file cannot be accessed
        cout << "\nError customers-rent.txt cannot be opened." << endl;
        system("pause");
    }

    // Close the file
	file.close();
}

// Deconstructor
CustomerRentList::~CustomerRentList()  {
    // Set the variables for the Customer Rent Stack
    CustomerRentNode *nodePtr, *nextNode;
    nodePtr = top;

    // Set the path for the customer-rent.txt file/csv
    // File Write
    ofstream file("customer-rent.txt");

    // Check if the file can be access, otherwise not display an error
    if(file.is_open()) {
        // Loop while there is a Node in the Customer Rent Stack
		while (nodePtr) {
            // Save the data in the format of:
            // Customer Id,Video Id
			file << nodePtr->customerId << "," << nodePtr->videoId << endl;
			nodePtr = nodePtr->next;
		}
	} else {
        // Display an Error when the customersrent-.txt file cannot be accessed
        cout << "\nError customers-rent.txt cannot be opened." << endl;
        system("pause");
    }

    // Close the file
	file.close();
}

// This function is called when the user Rent a Video
void CustomerRentList::customerRentPush(int cusId, int vidId) {
    // Set the variables for the Customer Rent Stack
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

// This function is called when the user Return the Video
void CustomerRentList::customerRentPop(int id, VideoList &v){
    // Local Stack
    stack< int, vector<int> > cStack;
    stack< int, vector<int> > vStack;

    // Set the variables for the Customer Rent Stack
    CustomerRentNode *nodePtr;
    nodePtr = top;

    // Local Variable
    int cId, vId, temp;

    // Display an Error if the Customer Rent Stack is Empty
    if(isEmpty()) {
        cout << "\nCustomer has no Rented Videos." << endl << endl;
        return;
    } else {
        // Traverse through all the Nodes in the Customer Rent Stack 
        for(int i = 0; i < stackSize; i++) {
            cId = top->customerId;
            vId = top->videoId;
            nodePtr = top->next;
            
            // If the Customer Id match the id parameter
            // Display the Video ID and call the function returnVideo 
            if(top->customerId == id) {
                cout << "Video ID: " << top->videoId << endl;
                v.returnVideo(top->videoId);
            } else {
                // Insert the data to the cStack and vStack
                cStack.push(cId);
                vStack.push(vId);
            }
            
            // Remove the Node from the Stack
            // Set the next node as the top
            delete top;
            top = nodePtr;
        }
    }

    // Data to be return to the Stack
    if(!cStack.empty()) {
        // Loop through all the cStack and return it to the Customer Rent Stack
        for(int i = 0; i < cStack.size(); i++) {
            customerRentPush(cStack.top(), vStack.top());
            cStack.pop();
            vStack.pop();
        }
    }
}

// This function traverse to all the nodes in the Customer Rent Queue
// It ask for an argument Customer ID and display all the Video that customer rents
void CustomerRentList::customerRentList(int id, VideoList &v) {
    // Set the variables for the Customer Rent Stack
    CustomerRentNode *nodePtr;
    nodePtr = top;

    // Local Variables
    bool empty = true;
    string temp;

    // Traverse through the Customer Rent Stack
    while (nodePtr) {
        // If the exact Customer Id is found in the Customer Rent Stack
        // Display the Video ID and Movie Title of all the Videos the Customer Rents
        if(nodePtr->customerId == id) {
            temp = v.videoTitle(nodePtr->videoId);
            cout << "Video ID: " << nodePtr->videoId << endl;
            cout << "Movie Title: " << temp <<endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    // Display a message when the Customer has no Rented Video
    if(empty)
        cout << "\nNo Video Rented Found." << endl << endl;
}

// This function is called to check if the Customer Rent Stack is empty
bool CustomerRentList::isEmpty() {
    // Local Variable
    bool status;

    // If there is no Data in the top/first node
    if (!top)
        status = true;
    // If there is a data in the top/first node
    else
        status = false;
        
    return status;
}