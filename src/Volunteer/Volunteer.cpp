#include "Volunteer.h"

/**
 * @param id - id of the new volunteer, given from counter
 * @param name - name of the volunteer
*/
Volunteer::Volunteer(int id, const string& name):
                    id(id),
                    name(name),
                    completedOrderId(NO_ORDER),
                    activeOrderId(NO_ORDER){}
Volunteer::~Volunteer(){}
int Volunteer::getId() const{return id;}
const string& Volunteer::getName() const{return name;}
int Volunteer::getActiveOrderId() const{return activeOrderId;}
int Volunteer::getCompletedOrderId() const{return completedOrderId;}

/**
 * @returns - true if has an active order, or completed order waiting
*/
bool Volunteer::isBusy() const{
    return activeOrderId != NO_ORDER;
}

/**
 * sets activeOrderId to be NO_ORDER,
 * signaling the complete order was taken
 * @return - ID of the completed order
*/
int Volunteer::completeOrder(){
    int retID = activeOrderId;
    activeOrderId = NO_ORDER;
    return retID;
}