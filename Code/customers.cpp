#include <iostream>
#include <fstream>
#include "customers.h"

using namespace std;
using namespace ns;

// Constructor
CustomerList::CustomerList(void) {
    // Set the variables to be default for the Customer Queue
    front = NULL;
    rear = NULL;
    queueSize = 0;

    // Local Variables
    string id, name, address;
    int cId;

    // Set the path for the customer.txt file/csv
    // File Read
    ifstream file("customers.txt");

    // Check if the file can be access, otherwise not display an error
    if(file.is_open()) {
        // Loop while there is a Node in the Customer Queue
        while(!file.eof()) {
            // Store the data from the customer.txt to the local variables
            getline(file, id, ',');
            getline(file, name, ',');
            getline(file, address, '\n');

            // If the data is not empty
            if(!id.empty()) {
                // Insert the data from the local variable to the Customer Queue
                cId = stoi(id);
                customerEnqueue(cId, name, address);
            }
        }
    } else {
        // Display an Error when the customers.txt file cannot be accessed
        cout << "\nError customers.txt cannot be opened." << endl;
        system("pause");
    }

    // Close the file
    file.close();
}

// Deconstructor
CustomerList::~CustomerList() {
    // Set the variables for the Customer Queue
    CustomerNode *nodePtr, *nextNode;
    nodePtr = front;

    // Set the path for the customer.txt file/csv
    // File Write
    ofstream file("customers.txt");

    // Check if the file can be access, otherwise not display an error
    if(file.is_open()) {
        // Loop while there is a Node in the Customer Queue
        while (nodePtr) {
            // Save the data in the format of:
            // Id,Name,Address
            file << nodePtr->customerId << "," << nodePtr->customerName << "," << nodePtr->customerAddress << endl;
            nodePtr = nodePtr->next;
        }
    } else {
        // Display an Error when the customers.txt file cannot be accessed
        cout << "\nError customers.txt cannot be opened." << endl;
        system("pause");
    }

    // Close the file
    file.close();
}

// Used for the Auto Incremention of the Customer ID
int CustomerList::autoCustomerIdIncrement() {
    // Set the variables for the Customer Queue
    CustomerNode *nodePtr;
    nodePtr = front;

    // Local Variable
    int id = 0;

    // Traverse through the Customer Queue
    while(nodePtr) {
        // Loop and get the Highest Customer Id
        if(nodePtr->customerId > id)
            id = nodePtr->customerId;
        nodePtr = nodePtr->next;
    }

    // Return the highest id with an increment
    return id+1;
}

// This function is called when the user Insert a Customer
void CustomerList::customerEnqueue(int cusId, string name, string address) {
    // Set the variables for the Customer Queue
    CustomerNode *newNode;

    // Local Vatiable 
    int id;

    // The cusId default value when inserting is 0
    // But when getting the data from the customer.txt it would diretcly insert the data
    if(cusId == 0) {
        //Get the next Customer ID
        id = autoCustomerIdIncrement();
    } else {
        // Get the direct value
        id = cusId;
    }

    // Allocate a new node & store the Data
    newNode = new CustomerNode;
    newNode->customerId = id;
    newNode->customerName = name;
    newNode->customerAddress = address;
    newNode->next = NULL;

    // If there are no nodes in the Customer Queue
    // Insert the data into the front/first node
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        // Else insert to the next node
        rear->next = newNode;
        rear = newNode;
    }
    queueSize++;
}

// This function traverse to all the nodes in the Customer Queue
// It ask for an argument Customer ID and display the details of the equivalent Customer ID
void CustomerList::customerDetails(int id) {
    // Set the variables for the Customer Linked List
    CustomerNode *nodePtr;
    nodePtr = front;

    // Local Variable
    bool empty = true;

    // Traverse through the Customer Queue
    while (nodePtr) {
        // If the exact Customer Id is found in the Customer Queue
        // Display all the details of that Customer
        if(nodePtr->customerId == id) {
            cout << "Name: " << nodePtr->customerName << endl;
            cout << "Address: " << nodePtr->customerAddress << endl;
            empty = false;
        }
        nodePtr = nodePtr->next;
    }

    // Display an Error when there is no Matching Customer ID Found
    if(empty)
        cout << "\nNo Matching Customer ID Found." << endl << endl;
}

// This function is called to check if the Customer Queue is empty
bool CustomerList::isEmpty() {
    // Local Variable
    bool status;

    // If the Customer is Greater than 0
    if (queueSize > 0)
        status = false;
    // If the Customer is 0 or less than
    else
        status = true;
    
    return status;
}