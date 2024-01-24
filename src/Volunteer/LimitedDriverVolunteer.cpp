#include "Volunteer.h"

/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param maxDistance - The maximum distance of ANY order the volunteer can take
 * @param distancePerStep - The distance the volunteer does in one step
 * @param maxOrders - The number of orders the volunteer can process in the whole simulation
*/
LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):
                                                DriverVolunteer::DriverVolunteer(id,name,maxDistance, distancePerStep),
                                                maxOrders(maxOrders),
                                                ordersLeft(maxOrders){}


LimitedDriverVolunteer::~LimitedDriverVolunteer(){}
LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const{
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const{return maxOrders;}
int LimitedDriverVolunteer::getNumOrdersLeft() const{return ordersLeft;}


bool LimitedDriverVolunteer::hasOrdersLeft() const{
    ordersLeft != 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order& order) const{
    return DriverVolunteer::canTakeOrder(order) &&
            hasOrdersLeft();
}

/**
 * if !canTakeOrder(order) than return without doing anything
 * Assign distanceLeft to order's distance and decrease ordersLeft
 * Decreases ordersLeft by 1
 * @param order - ref to a order the volunteer is going to handle
*/
void LimitedDriverVolunteer::acceptOrder(const Order& order){
    if(!canTakeOrder(order)) return;
    DriverVolunteer::acceptOrder(order);
}

string LimitedDriverVolunteer::toString() const{
    string strDistanceLeft =  getDistanceLeft() == 0 ? "None" : std::to_string(getDistanceLeft());
    return "VolunteerID: " + std::to_string(getId()) + "\n"
           +"isBusy: " + std::to_string(isBusy()) + "\n"
           +"OrderID: " + std::to_string(activeOrderId) + "\n"
           +"timeLeft: " + strDistanceLeft + "\n"
           +"ordersLeft: " + std::to_string(ordersLeft);
}

/**
 * sets activeOrderId to be NO_ORDER,
 * signaling the complete order was taken
 * decreases ordersLeft by 1
*/
void LimitedDriverVolunteer::completeOrder(){
    Volunteer::completeOrder();
    ordersLeft = --ordersLeft < 0 ? 0 : ordersLeft;
}