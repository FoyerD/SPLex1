#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath): isOpen(false), customerCounter(0), volunteerCounter(0), parser(configFilePath){
    proccessConfigFile();
}

void WareHouse::start(){
    open();
    while(isOpen){
        string currInput;
        getline(cin, currInput);
        vector<string> splitedInput = parser.ParseLine(currInput);
        BaseAction* currAction;
        if(splitedInput[0].compare(STEP) == 0){
            currAction = new SimulateStep(stoi(splitedInput[1]));
        }
        if(splitedInput[0].compare(ADDORDER) == 0){
            currAction = new AddOrder(stoi(splitedInput[1]));
        }
        if(splitedInput[0].compare(CUSTOMER) == 0){
            currAction = new AddCustomer(splitedInput[1], splitedInput[2], stoi(splitedInput[3]), stoi(splitedInput[4]));
        }
        if(splitedInput[0].compare(ORDER_STATUS) == 0){
            currAction = new PrintOrderStatus(stoi(splitedInput[1]));
        }
        if(splitedInput[0].compare(CUSTOMER_STATUS) == 0){
            currAction = new PrintCustomerStatus(stoi(splitedInput[1]));
        }
        if(splitedInput[0].compare(VOLUNTEER_STATUS) == 0){
            currAction = new PrintVolunteerStatus(stoi(splitedInput[1]));
        }
        if(splitedInput[0].compare(LOG) == 0){
            currAction = new PrintActionsLog();
        }
        if(splitedInput[0].compare(CLOSE) == 0){
            currAction = new Close();
        }
        if(splitedInput[0].compare(BACKUP) == 0){
            currAction = new BackupWareHouse();
        }
        if(splitedInput[0].compare(RESTORE) == 0){
            currAction = new RestoreWareHouse();
        }
        actionsLog.push_back(currAction);
        currAction->act(*this);
    }
}

void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
    orderCounter++;
}

void WareHouse::addAction(BaseAction* action){
    actionsLog.push_back(action);
}

Customer &WareHouse::getCustomer(int customerId) const{
    if(customerId < 0 || customerId > customerCounter){
        throw invalid_argument(string("no customer with id: " + to_string(customerId)));
    }
    for (auto & customer : customers) {
        if(customer->getId() == customerId) return *customer;
    }
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const{
    for (auto & volunteer : volunteers) {
        if(volunteer->getId() == volunteerId) return *volunteer;
    }
    throw invalid_argument(string("no volunteer with id: " + to_string(volunteerId)));
}

Order &WareHouse::getOrder(int orderId) const{
    for (auto & order : pendingOrders) {
        if(order->getId() == orderId) return *order;
    }
    for (auto & order : inProcessOrders) {
        if(order->getId() == orderId) return *order;
    }
    for (auto & order : completedOrders) {
        if(order->getId() == orderId) return *order;
    }
    throw invalid_argument(string("no Order with id: " + to_string(orderId)));
}

const vector<BaseAction*> &WareHouse::getActions() const{
    return actionsLog;
}

void WareHouse::close(){
    for (auto & order : pendingOrders) {
         cout << (*order).printAfterClose() << endl;
         delete order;
         order = nullptr;
    }
    for (auto & order : inProcessOrders) {
         cout << (*order).printAfterClose() << endl;
         delete order;
         order = nullptr;
    }
    for (auto & order : completedOrders) {
         cout << (*order).printAfterClose() << endl;
         delete order;
         order = nullptr;
    }
    for (auto & customer : customers) {
         delete customer;
         customer = nullptr;
    }
    for (auto & volunteer : volunteers) {
         delete volunteer;
         volunteer = nullptr;
    }
    for (auto & action : actionsLog) {
         delete action;
         action = nullptr;
    }
    isOpen = false;
}

void WareHouse::open(){
    isOpen = true;
    cout << "Warehouse is open!" << endl;
}

int WareHouse::getOrdersNumber() const{
    return orderCounter;
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