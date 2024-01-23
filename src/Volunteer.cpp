#include "Volunteer.h"

//Volunteer class
/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
*/
Volunteer::Volunteer(int id, const string& name):
                    id(id),
                    name(name),
                    completedOrderId(NO_ORDER),
                    activeOrderId(NO_ORDER){}
int Volunteer::getId() const{return id;}
const string& Volunteer::getName() const{return name;}
int Volunteer::getActiveOrderId() const{return activeOrderId;}
int Volunteer::getCompletedOrderId() const{return completedOrderId;}

/**
 * @returns - true if has an active order
*/
bool Volunteer::isBusy() const{return !(activeOrderId == NO_ORDER);}




//CollectorVolunteer class
/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
 * @param coolDown - process time of 1 order
*/
CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown):
                                        Volunteer::Volunteer(id,name),
                                        coolDown(coolDown),
                                        timeLeft(coolDown){}
/**
 * @returns - a new instance of volunteer with same parameters(not busy)
*/
CollectorVolunteer* CollectorVolunteer::clone() const {
    return new CollectorVolunteer(getId(), getName(), coolDown);
}

int CollectorVolunteer::getCoolDown() const {return coolDown;}
int CollectorVolunteer::getTimeLeft() const {return timeLeft;}

/**
 * ment for LimitedCollector
 * @returns - true
*/
bool CollectorVolunteer::hasOrdersLeft() const {return true;}

/**
 * checks if volunteer could handle the order once free
 * @param order - ref to order we check if volunteer can handle
 * @returns - true if the status of order is PENDING
*/
bool CollectorVolunteer::canTakeOrder(const Order& order) const {
    return order.getStatus() == OrderStatus::PENDING;
}

/**
 * a step in the 
*/
void CollectorVolunteer::step(){
    if(decreaseCoolDown()){
         completedOrderId = activeOrderId;
         activeOrderId = NO_ORDER;
    }
}

/**
 * decrease timeLeft by 1,return true if timeLeft=0,false otherwise
*/
bool CollectorVolunteer::decreaseCoolDown(){
    timeLeft = --timeLeft < 0 ? 0 : timeLeft;
    return timeLeft == 0;
}