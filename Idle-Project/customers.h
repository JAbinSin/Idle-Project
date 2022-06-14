#pragma once
#include <string>

namespace ns
{
	class CustomerList {
	   private:
            // This Structure would be a Queue
            struct CustomerNode {
                int customerId;
                std::string customerName;
                std::string customerAddress;
                struct CustomerNode *next;
            };
            CustomerNode *front;
            CustomerNode *rear;
            int queueSize;
        public:
			// The Codes below are a public Function
	        CustomerList(void); // Constructor
		    ~CustomerList(); // Deconstructor
		    void customerEnqueue(int id, std::string name, std::string address); // Insertion of the customer
		    void customerDetails(int id); // Display all the customer details
            bool isEmpty(); // Check if the Structure CustomerNode is not Empty
            int autoCustomerIdIncrement(); // For the Auto Generation of Video ID
    };
}