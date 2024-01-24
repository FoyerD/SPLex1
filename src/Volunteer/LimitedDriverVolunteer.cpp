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


LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const{
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const{return maxOrders;}
int LimitedDriverVolunteer::getNumOrdersLeft() const{return ordersLeft;}


bool LimitedDriverVolunteer::hasOrdersLeft() const{
    ordersLeft != 0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order& order) const{
    return !isBusy() &&
            order.getStatus() == OrderStatus::COLLECTING &&
            getMaxDistance() < order.getDistance() &&
            hasOrdersLeft();
}

void acceptOrder