#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath): isOpen(false), customerCounter(0), volunteerCounter(0), parser(){
    proccessConfigFile(configFilePath);
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
        else if(splitedInput[0].compare(ADDORDER) == 0){
            currAction = new AddOrder(stoi(splitedInput[1]));
        }
        else if(splitedInput[0].compare(CUSTOMER) == 0){
            currAction = new AddCustomer(splitedInput[1], splitedInput[2], stoi(splitedInput[3]), stoi(splitedInput[4]));
        }
        else if(splitedInput[0].compare(ORDER_STATUS) == 0){
            currAction = new PrintOrderStatus(stoi(splitedInput[1]));
        }
        else if(splitedInput[0].compare(CUSTOMER_STATUS) == 0){
            currAction = new PrintCustomerStatus(stoi(splitedInput[1]));
        }
        else if(splitedInput[0].compare(VOLUNTEER_STATUS) == 0){
            currAction = new PrintVolunteerStatus(stoi(splitedInput[1]));
        }
        else if(splitedInput[0].compare(LOG) == 0){
            currAction = new PrintActionsLog();
        }
        else if(splitedInput[0].compare(CLOSE) == 0){
            currAction = new Close();
        }
        else if(splitedInput[0].compare(BACKUP) == 0){
            currAction = new BackupWareHouse();
        }
        else if(splitedInput[0].compare(RESTORE) == 0){
            currAction = new RestoreWareHouse();
        }
        else {
            continue;
        }
        actionsLog.push_back(currAction);
        currAction->act(*this);
    }
}

void WareHouse::addOrder(Order* order){
    if(order->getStatus() == OrderStatus::PENDING || order->getStatus() == OrderStatus::COLLECTING){
        pendingOrders.push_back(order);
    }
    if(order->getStatus() == OrderStatus::DELIVERING){
        inProcessOrders.push_back(order);
    }
    if(order->getStatus() == OrderStatus::COMPLETED){
        completedOrders.push_back(order);
    }
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
    isOpen = false;
}

void WareHouse::open(){
    isOpen = true;
    cout << "Warehouse is open!" << endl;
}

int WareHouse::getOrdersNumber() const{
    return orderCounter;
}

WareHouse::WareHouse(const WareHouse& otherWareHouse): isOpen(otherWareHouse.isOpen), customerCounter(otherWareHouse.customerCounter),
volunteerCounter(otherWareHouse.volunteerCounter), parser(otherWareHouse.parser), orderCounter(otherWareHouse.orderCounter){
    for(auto& action: otherWareHouse.actionsLog){
        actionsLog.push_back(action->clone());
    }
    for(auto& volunteer: otherWareHouse.volunteers){
        volunteers.push_back(volunteer->clone());
    }
    for(auto& customer: otherWareHouse.customers){
        customers.push_back(customer->clone());
    }
    for(auto& pendingOrder: otherWareHouse.pendingOrders){
        pendingOrders.push_back(new Order(*pendingOrder));
    }
    for(auto& inProcessOrder: otherWareHouse.inProcessOrders){
        inProcessOrders.push_back(new Order(*inProcessOrder));
    }
    for(auto& completedOrder: otherWareHouse.completedOrders){
        completedOrders.push_back(new Order(*completedOrder));
    }
}

WareHouse::WareHouse(WareHouse&& otherWareHouse): isOpen(otherWareHouse.isOpen), customerCounter(otherWareHouse.customerCounter),
volunteerCounter(otherWareHouse.volunteerCounter), parser(otherWareHouse.parser), orderCounter(otherWareHouse.orderCounter),
pendingOrders(otherWareHouse.pendingOrders), inProcessOrders(otherWareHouse.inProcessOrders), completedOrders(otherWareHouse.completedOrders),
customers(otherWareHouse.customers), volunteers(otherWareHouse.volunteers), actionsLog(otherWareHouse.actionsLog){
    for (auto & order : otherWareHouse.pendingOrders) {
         order = nullptr;
    }
    for (auto & order : otherWareHouse.inProcessOrders) {
         order = nullptr;
    }
    for (auto & order : otherWareHouse.completedOrders) {
         order = nullptr;
    }
    for (auto & customer : otherWareHouse.customers) {
         customer = nullptr;
    }
    for (auto & volunteer : otherWareHouse.volunteers) {
         volunteer = nullptr;
    }
    for (auto & action : otherWareHouse.actionsLog) {
         action = nullptr;
    }
    otherWareHouse.actionsLog.clear();
    otherWareHouse.customers.clear();
    otherWareHouse.volunteers.clear();
    otherWareHouse.pendingOrders.clear();
    otherWareHouse.inProcessOrders.clear();
    otherWareHouse.completedOrders.clear();
}

WareHouse& WareHouse::operator=(WareHouse&& other){
    if(this != &other){
        this->isOpen = other.isOpen;
        this->orderCounter = other.orderCounter;
        this->customerCounter = other.customerCounter;
        this->volunteerCounter = other.volunteerCounter;
        this->parser = other.parser;
        for (BaseAction* action : actionsLog) {
            delete action;
        }
        for (Volunteer* volunteer : volunteers) {
            delete volunteer;
        }
        for (Order* order : pendingOrders) {
            delete order;
        }
        for (Order* order : inProcessOrders) {
            delete order;
        }
        for (Order* order : completedOrders) {
            delete order;
        }
        for (Customer* customer : customers) {
            delete customer;
        }
        this->pendingOrders = other.pendingOrders;
        this->inProcessOrders = other.inProcessOrders;
        this->completedOrders = other.completedOrders;
        this->actionsLog = other.actionsLog;
        this->customers = other.customers;
        this->volunteers = other.volunteers;
        other.isOpen = false;
        other.customerCounter = 0;
        other.volunteerCounter = 0;
        other.orderCounter = 0;
    }
    return *this;
}

WareHouse::~WareHouse(){
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
    pendingOrders.clear();
    inProcessOrders.clear();
    completedOrders.clear();
    customers.clear();
    volunteers.clear();
    actionsLog.clear();
}

WareHouse& WareHouse::operator=(const WareHouse& other){
    if(&other != this){
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        parser = other.parser;
        orderCounter = other.orderCounter;
        WareHouse::~WareHouse();
        for (auto & order : other.pendingOrders) {
            pendingOrders.push_back(new Order(*order));
        }
        for (auto & order : other.inProcessOrders) {
            inProcessOrders.push_back(new Order(*order));
        }
        for (auto & order : other.completedOrders) {
            completedOrders.push_back(new Order(*order));
        }
        for (auto & customer : other.customers) {
            customers.push_back(customer->clone());
        }
        for (auto & volunteer : other.volunteers) {
            volunteers.push_back(volunteer->clone());
        }
        for (auto & action : other.actionsLog) {
            actionsLog.push_back(action->clone());
        }
    }
    return *this;
}

void WareHouse::addCustomer(Customer* customer){
    this->customers.push_back(customer);
    customerCounter++;
}

void WareHouse::addVolunteer(Volunteer* Volunteer){
    this->volunteers.push_back(Volunteer);
    volunteerCounter++;
}

void WareHouse::proccessConfigFile(const string &configFilePath){
    vector<string> lines =  parser.ParseFile(configFilePath);
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

const vector<Order*>& WareHouse::getPendingOrders() const{
    return pendingOrders;
}

const vector<Order*>& WareHouse::getInProccesOrders() const{
    return inProcessOrders;
}

const vector<Order*>& WareHouse::getCompletedOrders() const{
    return completedOrders;
}

Volunteer* WareHouse::findFreeVolunteer(Order& orderToHandle){
    for(auto& volunteer : volunteers){
        if(volunteer->canTakeOrder(orderToHandle)){
            return volunteer;
        }
    }
    return nullptr;
}

void WareHouse::moveToInProcces(Order* orderToMove){
    pendingOrders.erase(find(pendingOrders.begin(), pendingOrders.end(), orderToMove));
    inProcessOrders.push_back(orderToMove);
}