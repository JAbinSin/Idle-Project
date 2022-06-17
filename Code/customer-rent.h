#pragma once
#include <string>
#include "videos.h"

namespace ns {
    class CustomerRentList {
        private:
            // This Structure would be a Stack
            struct CustomerRentNode {
                int customerId;
                int videoId;
                CustomerRentNode *next;
            };
            CustomerRentNode *top;
            int stackSize;
        public:
           	// The Codes below are a public Function
            CustomerRentList(); // Constructor
            ~CustomerRentList(); // Deconstructor
            void customerRentPush(int cusId, int vidId); // Insertion of Customer Rent
            void customerRentPop(int id, VideoList &v); // Removal of Customer Rent
            void customerRentList(int id, VideoList &v); // Details of Customer Rent
            bool isEmpty(); // Check if the Structure CustomerRentNode is not Empty
    };
}