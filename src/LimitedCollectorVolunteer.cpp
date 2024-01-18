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

/**
 * @returns - a new instance of volunteer with same parameters(not busy)
*/
LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const{
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const{
    return ordersLeft != 0;
}

/**
 * returns true if volunteer has orders left, is not busy and orderStatus is PENDING
*/
bool LimitedCollectorVolunteer::canTakeOrder(const Order& order) const{
    return hasOrdersLeft() && order.getStatus() == OrderStatus::PENDING && !isBusy();
}

/**
 *  * !assumes instance can take order
 * accepts an order, updates timeLeft and activeOrderId
 * decreases ordersLeft by 1 
 * @param order - ref to a order the volunteer is going to handle
*/
void LimitedCollectorVolunteer::acceptOrder(const Order& order){
    CollectorVolunteer::acceptOrder(order);
    ordersLeft--;  
}

int LimitedCollectorVolunteer::getMaxOrders() const{
    return maxOrders;
}
int LimitedCollectorVolunteer::getNumOrdersLeft() const{
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const{
    string strTimeLeft =  getTimeLeft() == 0 ? "None" : std::to_string(getTimeLeft());
    return "VolunteerID: " + std::to_string(getId()) + "\n"
           +"isBusy: " + std::to_string(isBusy()) + "\n"
           +"OrderID: " + std::to_string(activeOrderId) + "\n"
           +"timeLeft: " + strTimeLeft + "\n"
           +"ordersLeft: " + std::to_string(ordersLeft);
}
