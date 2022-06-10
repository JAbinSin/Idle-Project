// This file would all hold the ADT for the Custmer Parent ADT
#pragma once
#include <string>

namespace ns
{
	class CustomerList {
	   private:
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
		    void customerEnqueue(int id, std::string name, std::string address);
		    void customerDetails(int id);
            bool isEmpty();
            int autoCustomerIdIncrement();
    };
}