#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath): isOpen(false), customerCounter(0), volunteerCounter(0), parser(configFilePath){
    proccessConfigFile();
}

void WareHouse::start(){
    while(true){
        
    }
}

void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
}

void WareHouse::addAction(BaseAction* action){
    actionsLog.push_back(action);
}

Customer &WareHouse::getCustomer(int customerId) const{
    for (auto & element : customers) {
        if(element->getId() == customerId) return *element;
    }
    throw invalid_argument(string("no customer with id: " + to_string(customerId)));
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const{
    for (auto & element : volunteers) {
        if(element->getId() == volunteerId) return *element;
    }
    throw invalid_argument(string("no volunteer with id: " + to_string(volunteerId)));
}

Order &WareHouse::getOrder(int orderId) const{
    for (auto & element : pendingOrders) {
        if(element->getId() == orderId) return *element;
    }
    for (auto & element : inProcessOrders) {
        if(element->getId() == orderId) return *element;
    }
    for (auto & element : completedOrders) {
        if(element->getId() == orderId) return *element;
    }
    throw invalid_argument(string("no Order with id: " + to_string(orderId)));
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

void WareHouse::proccessConfigFile(){
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
            if(currLine[2].compare(COLLECTOR) == 0){
                switch (currLine.size())
                {
                case CASE_COLLECTOR:
                    volunteers.push_back(new CollectorVolunteer(volunteerCounter, currLine[1], stoi(currLine[3])));
                    break;
                case CASE_LCOLLECTOR:
                    volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4])));
                    break;
                }
            }
            else if(currLine[2].compare(DRIVER) == 0){
                switch (currLine.size())
                {
                case CASE_DRIVER:
                    volunteers.push_back(new CollectorVolunteer(volunteerCounter, currLine[1], stoi(currLine[3])));
                    break;
                case CASE_LDRIVER:
                    volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4])));
                    break;
                }
            }
            volunteerCounter++;
        }
    }
}