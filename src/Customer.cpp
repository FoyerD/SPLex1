#include "Customer.h"

Customer::Customer(int id, const string &name, int locationDistance, int maxOrders): id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders){}

const string &Customer::getName() const{
    return name;
}
int Customer::getId() const{
    return id;
}
int Customer::getCustomerDistance() const{
    return locationDistance;
}

//Returns maxOrders
int Customer::getMaxOrders() const{
    return maxOrders;
} 

//Returns num of orders the customer has made so far
int Customer::getNumOrders() const{
    return ordersId.size();
} 

 //Returns true if the customer didn't reach max orders
bool Customer::canMakeOrder() const{
    return (getNumOrders() < maxOrders) ? true : false;
}

//Returns all orders id's in a vector
const vector<int> &Customer::getOrders() const{
    return ordersId;
}

///return OrderId if order was added successfully, -1 otherwise
int Customer::addOrder(int orderId){
    if(canMakeOrder()){
        ordersId.push_back(orderId);
        return orderId;
    }
    else return -1;
} 


SoldierCustomer::SoldierCustomer(int id, string name, int locationDistance, int maxOrders): Customer(id,name,locationDistance,maxOrders){}

//return a SoldierCustomer object that is a clone to the current SoldierCustomer
SoldierCustomer* SoldierCustomer::clone() const {
   return new SoldierCustomer(getId(), getName(), getCustomerDistance(), getMaxOrders());
}

CivilianCustomer::CivilianCustomer(int id, string name, int locationDistance, int maxOrders): Customer(id,name,locationDistance,maxOrders){}

//return a CivilianCustomer object that is a clone to the current CivilianCustomer
CivilianCustomer* CivilianCustomer::clone() const {
    return new CivilianCustomer(getId(), getName(), getCustomerDistance(), getMaxOrders());
}
