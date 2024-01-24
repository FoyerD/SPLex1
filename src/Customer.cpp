#include "Customer.h"
//Customer class

/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param locationDistance - the distance from the warehouse to th customer
 * @param maxOrders - the max number of orders the client can make
*/
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

int Customer::getMaxOrders() const{
    return maxOrders;
} 

/**
 * @returns - the number of orders the customer has made so far
*/
int Customer::getNumOrders() const{
    return ordersId.size();
} 

/**
 * @returns - true if the customer didn't reach max orders else, false
*/
bool Customer::canMakeOrder() const{
    return (getNumOrders() < maxOrders) ? true : false;
}

/**
 * @returns - all orders id's in a vector
*/
const vector<int> &Customer::getOrdersIds() const{
    return ordersId;
}

/**
 * @returns - OrderId if order was added successfully, -1 otherwise
*/
int Customer::addOrder(int orderId){
    if(canMakeOrder()){
        ordersId.push_back(orderId);
        return orderId;
    }
    else return -1;
} 

//SoldierCustomer class
/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param locationDistance - the distance from the warehouse to th customer
 * @param maxOrders - the max number of orders the client can make
*/
SoldierCustomer::SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders): Customer(id,name,locationDistance,maxOrders){}

/**
 * @returns - a SoldierCustomer object that is a clone to the current SoldierCustomer
*/
SoldierCustomer* SoldierCustomer::clone() const {
   return new SoldierCustomer(*this);
}

//CivilianCustomer class
/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param locationDistance - the distance from the warehouse to th customer
 * @param maxOrders - the max number of orders the client can make
*/
CivilianCustomer::CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders): Customer(id,name,locationDistance,maxOrders){}

/**
 * @returns - a CivilianCustomer object that is a clone to the current CivilianCustomer
*/
CivilianCustomer* CivilianCustomer::clone() const{
    return new CivilianCustomer(*this);
}
