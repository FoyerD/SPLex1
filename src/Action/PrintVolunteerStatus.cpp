#include "Action.h"
#include "WareHouse.h"
PrintVolunteerStatus::PrintVolunteerStatus(int id):
                                    BaseAction::BaseAction(),
                                    VolunteerId(id){}
PrintVolunteerStatus::~PrintVolunteerStatus(){}

PrintVolunteerStatus* PrintVolunteerStatus::clone() const{
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const{
    return "customerStatus " +
            std::to_string(VolunteerId) + " " + 
            statusToString[(int)BaseAction::getStatus()];
}


void PrintVolunteerStatus::act(WareHouse& wareHouse){
    Volunteer* toPrint = &wareHouse.getVolunteer(VolunteerId);
    if(toPrint->getId() == -1){
        error("Volunteer doesn't exist");
        return;
    }
    std::cout << toPrint->toString();
}