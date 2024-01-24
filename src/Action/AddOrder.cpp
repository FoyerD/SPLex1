#include "Action.h"

AddOrder::AddOrder(int id):
                    customerId(id){}
AddOrder::~AddOrder(){}

string AddOrder::toString() const{
    return "order" + std::to_string(customerId);
}

