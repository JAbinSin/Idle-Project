// This file would all hold the ADT for the Custmer Parent ADT
#pragma once
#include <string>
#include "videos.h"

namespace ns
{
    class CustomerRentList {
        private:
            struct CustomerRentNode {
                int customerId;
                int videoId;
                CustomerRentNode *next;
            };
            CustomerRentNode *top;
            int stackSize;
        public:
            CustomerRentList();
            ~CustomerRentList();
            void customerRentPush(int cusId, int vidId);
            void customerRentPop(int id, VideoList &v);
            void customerRentList(int id);
            bool isEmpty();
    };
}