#include "Volunteer.h"

//Volunteer class
Volunteer::Volunteer(int id, const string& name):
                    id(id),
                    name(name)
                    {completedOrderId = NO_ORDER;
                    activeOrderId = NO_ORDER;}

int Volunteer::getId() const{return id;}
const string& Volunteer::getName() const{return name;}
int Volunteer::getActiveOrderId() const{return activeOrderId;}
int Volunteer::getCompletedOrderId() const{return completedOrderId;}


bool Volunteer::isBusy() const{return !(activeOrderId == NO_ORDER);}




//CollectorVolunteer class
CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown):
                                        Volunteer::Volunteer(id,name),
                                        coolDown(coolDown)
                                        {timeLeft = coolDown;}
CollectorVolunteer* CollectorVolunteer::clone() const {
    return new CollectorVolunteer(getId(), getName(), coolDown);
}

int CollectorVolunteer::getCoolDown() const {return coolDown;}
int CollectorVolunteer::getTimeLeft() const {return timeLeft;}

bool CollectorVolunteer::hasOrdersLeft() const {return true;}
bool CollectorVolunteer::canTakeOrder(const Order& order) const {
    return order.getStatus() == OrderStatus::PENDING && hasOrdersLeft();
}
void CollectorVolunteer::step(){
    if(decreaseCoolDown()){
         completedOrderId = activeOrderId;
         activeOrderId = NO_ORDER;
    }
}
void CollectorVolunteer::decreaseCoolDown(){
    
}