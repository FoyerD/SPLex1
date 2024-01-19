#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath): isOpen(false), customerCounter(0), volunteerCounter(0), parser(configFilePath){}

void WareHouse::start(){
    vector<string> lines =  parser.ParseFile();
    for(int i = 0; i < lines.size(); i++){
        vector<const string> currLine = parser.ParseLine(lines[i]);
        if(currLine[0].compare(CUSTOMER) == 0){
            if(currLine[2].compare(SOLDIER) == 0){

            }
            else if(currLine[2].compare(CIVILIAN) == 0){
                
            }
        }
    }

}

void WareHouse::addOrder(Order* order){

}

void WareHouse::addAction(BaseAction* action){

}

Customer &WareHouse::getCustomer(int customerId) const{

}

Volunteer &WareHouse::getVolunteer(int volunteerId) const{

}

Order &WareHouse::getOrder(int orderId) const{

}

const vector<BaseAction*> &WareHouse::getActions() const{

}

void WareHouse::close(){
    isOpen = false;
}

void WareHouse::open(){
    isOpen = true;
}