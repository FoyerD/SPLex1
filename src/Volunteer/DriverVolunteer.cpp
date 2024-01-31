#include "Volunteer.h"

/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param maxDistance - The maximum distance of ANY order the volunteer can take
 * @param distancePerStep - The distance the volunteer does in one step
*/
DriverVolunteer::DriverVolunteer(int id,string name, int maxDistance, int distancePerStep):
                                Volunteer::Volunteer(id,name),
                                maxDistance(maxDistance),
                                distancePerStep(distancePerStep),
                                distanceLeft(0){}
DriverVolunteer* DriverVolunteer::clone() const{
    return new DriverVolunteer(*this);
}
DriverVolunteer::~DriverVolunteer(){}

int DriverVolunteer::getDistanceLeft() const{return distanceLeft;}
int DriverVolunteer::getMaxDistance() const{return maxDistance;}
int DriverVolunteer::getDistancePerStep() const{return distancePerStep;}

/**
 * Decrease distanceLeft by distancePerStep,return true if distanceLeft<=0,false otherwise
 * if lower than 0 after change, set to 0
*/
bool DriverVolunteer::decreaseDistanceLeft(){
    distanceLeft = distanceLeft - distancePerStep < 0 ? 0 : distanceLeft - distancePerStep;
    return distanceLeft <= 0;
}

/**
 * returns true
*/
bool DriverVolunteer::hasOrdersLeft() const{return true;}

/**
 * Signal if the volunteer is not busy and the order is within the maxDistance
 * @param order - referance, the order we want to check if instance can handle now
*/
bool DriverVolunteer::canTakeOrder(const Order& order) const{
    return !isBusy() &&
            order.getStatus() == OrderStatus::COLLECTING &&
            maxDistance >= order.getDistance();
}

/**
 * !assumes instance can take order
 * Assign distanceLeft to order's distance and decrease ordersLeft
 * @param order - ref to a order the volunteer is going to handle
*/
void DriverVolunteer::acceptOrder(const Order& order){
    activeOrderId  = order.getId();
    distanceLeft = order.getDistance();
}


/**
 * Decrease distanceLeft by distancePerStep
 * and only allows current order
 * to be completed if completedOrderId == NO_ORDER
 * If ditanceLeft is 0, set completeOrderId to activeOrderId
 * and set activeOrderId to NO_ORDER
*/
void DriverVolunteer::step(){
    if(decreaseDistanceLeft() && completedOrderId == NO_ORDER){
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
    }
}

string DriverVolunteer::toString() const{
    string strDistanceLeft =  distanceLeft == 0 ? "None" : std::to_string(distanceLeft);
    return "\nVolunteerID: " + std::to_string(getId()) + "\n"
           +"isBusy: " + (isBusy() == true ? "true" : "false") + "\n"
           +"OrderID: " + (activeOrderId == NO_ORDER ? "None" : std::to_string(activeOrderId)) + "\n"
           +"timeLeft: " + strDistanceLeft + "\n"
           +"ordersLeft: No Limit\n";
}


