#include "Action.h"
#include "WareHouse.h"
AddOrder::AddOrder(int id):
                    BaseAction::BaseAction(),
                    customerId(id){}
AddOrder::~AddOrder(){}

string AddOrder::toString() const{
    return "order " + std::to_string(customerId) + " " + 
            statusToString[(int)BaseAction::getStatus()];;
}

void AddOrder::act(WareHouse& wareHouse){
    Customer& currCustomer = wareHouse.getCustomer(customerId);
    if(currCustomer.getId() == -1 || currCustomer.getMaxOrders() <= currCustomer.getNumOrders()){
        error("Cannot place this order");
        return;
    }
    wareHouse.addOrder(new Order(wareHouse.getOrdersNumber(), customerId, currCustomer.getCustomerDistance()));
    complete();
}

AddOrder *AddOrder::clone() const{
    return new AddOrder(*this);
}