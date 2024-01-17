#include "Customer.h"
Customer::Customer(int id, const string &name, int locationDistance, int maxOrders): id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders){}

const string &Customer::getName() const{

}
int Customer::getId() const{
    return id;
}
int Customer::getCustomerDistance() const{
    return locationDistance;
}

int Customer::getMaxOrders() const{
    return maxOrders;
} //Returns maxOrders

int Customer::getNumOrders() const{
    return ordersId.size();
} //Returns num of orders the customer has made so far

bool Customer::canMakeOrder() const{
    return (getNumOrders() < maxOrders) ? true : false;
} //Returns true if the customer didn't reach max orders

vector<int> &Customer::getOrders() const{
    ;
}

int Customer::addOrder(int orderId){
    if(canMakeOrder()){
        ordersId.push_back(orderId);
        return orderId;
    }
    else return -1;
} //return OrderId if order was added successfully, -1 otherwise
