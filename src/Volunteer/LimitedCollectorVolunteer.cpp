#include "Volunteer.h"

/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param coolDown - process time of 1 order
 * @param maxOrders - number of orders instance can take before being deletet
*/
LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown, int maxOrders):
                                                    CollectorVolunteer::CollectorVolunteer(id,name,coolDown),
                                                    maxOrders(maxOrders),
                                                    ordersLeft(maxOrders){}

LimitedCollectorVolunteer::~LimitedCollectorVolunteer(){}
/**
 * @returns - a new instance of volunteer with same parameters(not busy)
*/
LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const{
    return ordersLeft > 0;
}

/**
 * returns true if volunteer has orders left, is not busy and orderStatus is PENDING
*/
bool LimitedCollectorVolunteer::canTakeOrder(const Order& order) const{
    return hasOrdersLeft() &&
            CollectorVolunteer::canTakeOrder(order);
}

/**
 * !assumes instance can take order
 * accepts an order, updates timeLeft to coolDown and activeOrderId to order.getId()
 * @param order - ref to a order the volunteer is going to handle
*/
void LimitedCollectorVolunteer::acceptOrder(const Order& order){
    CollectorVolunteer::acceptOrder(order);
}

int LimitedCollectorVolunteer::getMaxOrders() const{
    return maxOrders;
}
int LimitedCollectorVolunteer::getNumOrdersLeft() const{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const{
    string strTimeLeft =  getTimeLeft() == 0 ? "None" : std::to_string(getTimeLeft());
    return "\nVolunteerID: " + std::to_string(getId()) + "\n"
           +"isBusy: " + (isBusy() == true ? "true" : "false") + "\n"
           +"OrderID: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(activeOrderId)) + "\n"
           +"timeLeft: " + strTimeLeft + "\n"
           +"ordersLeft: " + std::to_string(ordersLeft) + "\n";
}

/**
 * sets activeOrderId to be NO_ORDER,
 * signaling the complete order was taken
 * decreases ordersLeft by 1
 * @return - ID of the completed order
*/
int LimitedCollectorVolunteer::completeOrder(){
    ordersLeft = --ordersLeft < 0 ? 0 : ordersLeft;
    return Volunteer::completeOrder();
}