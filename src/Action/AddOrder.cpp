#include "Action.h"

AddOrder::AddOrder(int id):
                    customerId(id){}
AddOrder::~AddOrder(){}

string AddOrder::toString() const{
    return "order" + std::to_string(customerId);
}

void AddOrder::act(WareHouse& wareHouse){
    Customer& currCustomer = wareHouse.getCustomer(customerId);
    if(currCustomer.getId() == -1 || currCustomer.getMaxOrders() <= currCustomer.getNumOrders()){
        error("Cannot place this order");
        return;
    }

    wareHouse.addOrder(new Order(wareHouse.getOrdersNumber(), customerId, currCustomer.getCustomerDistance()));
}