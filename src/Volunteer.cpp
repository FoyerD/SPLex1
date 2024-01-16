#include "Volunteer.h"

//Volunteer class
Volunteer::Volunteer(int id, const string& name) : id(id), name(name){}

int Volunteer::getId() const{return this->id;}
const string& Volunteer::getName() const{return this->name;}
int Volunteer::getActiveOrderId() const{return this->activeOrderId;}
int Volunteer::getCompletedOrderId() const{return this->completedOrderId;}


bool Volunteer::isBusy() const{return this->activeOrderId==NO_ORDER;}


//CollectorVolunteer class
CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown) : Volunteer::Volunteer(id,name), coolDown(coolDown){}
