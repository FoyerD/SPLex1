#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath): isOpen(false), customerCounter(0), volunteerCounter(0), parser(configFilePath){}

void WareHouse::start(){
    vector<string> lines =  parser.ParseFile();
    for(int i = 0; i < lines.size(); i++){
        vector<string> currLine = parser.ParseLine(lines[i]);
        if(currLine[0].compare(CUSTOMER) == 0){
            if(currLine[2].compare(SOLDIER) == 0){
                customers.push_back(new SoldierCustomer(customerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4])));
            }
            else if(currLine[2].compare(CIVILIAN) == 0){
                customers.push_back(new CivilianCustomer(customerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4])));
            }
            customerCounter++;
        }
        else if(currLine[0].compare(VOLUNTEER) == 0){
            
        }
    }
    

}

void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
}

void WareHouse::addAction(BaseAction* action){
    actionsLog.push_back(action);
}

Customer &WareHouse::getCustomer(int customerId) const{
    return *customers[customerId];
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const{
    std::sort(volunteers.begin(), volunteers.end(), [](Volunteer & one, Volunteer & two){return one.getId() < two.getId();});
    return *volunteers[volunteerId];
}

Order &WareHouse::getOrder(int orderId) const{
    ;
}

const vector<BaseAction*> &WareHouse::getActions() const{
    return actionsLog;
}

void WareHouse::close(){
    isOpen = false;
}

void WareHouse::open(){
    isOpen = true;
}