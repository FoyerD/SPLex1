#include "../include/WareHouse.h"
/**
 * @brief Construct a new Ware House:: Ware House object
 * 
 * @param configFilePath - the path to the configuration file given by the user
 */
WareHouse::WareHouse(const string &configFilePath): isOpen(false), customerCounter(0), volunteerCounter(0), parser(), demiCust(new CivilianCustomer(DOES_NOT_EXIST, "", DOES_NOT_EXIST, DOES_NOT_EXIST)), demiVol(new CollectorVolunteer(DOES_NOT_EXIST, "", DOES_NOT_EXIST)), demiOrder(new Order(DOES_NOT_EXIST, DOES_NOT_EXIST, DOES_NOT_EXIST)){
    proccessConfigFile(configFilePath);
}

//this function runs a loop that gets the user input and acts accordingly
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

/**
 * @brief this function adds an order to the pending orders list
 * 
 * @param order - the order to add to the pending orders list
 */
void WareHouse::addOrder(Order* order){
    if(order->getStatus() == OrderStatus::PENDING){
        pendingOrders.push_back(order);
        orderCounter++;
    }
}

/**
 * @brief this function adds an action to the actions log list
 * 
 * @param action - the action we want to add
 */
void WareHouse::addAction(BaseAction* action){
    actionsLog.push_back(action);
}

/**
 * @brief - this functions gets a customer with the id, customerId
 * 
 * @param customerId - the id of the customer we want to get
 * @return - a reference to the customer if found, else returns a demi customer (needs to be deleted by caller)
 */
Customer &WareHouse::getCustomer(int customerId) const{
    if(customerId < 0 || customerId > customerCounter){
        return *demiCust;
    }
    for (auto & customer : customers) {
        if(customer->getId() == customerId) return *customer;
    }
}

/**
 * @brief - this function gets a volunteer with the id, volunteerId
 * 
 * @param volunteerId - the id of the volunteer we want to get 
 * @return - a reference to the volunteer if found, else returns a demi volunteer (needs to be deleted by caller)
 */
Volunteer &WareHouse::getVolunteer(int volunteerId) const{
    for (auto & volunteer : volunteers) {
        if(volunteer->getId() == volunteerId) return *volunteer;
    }
    return *demiVol;
}

/**
 * @brief - this function gets an order with the id, orderId
 * 
 * @param orderId - the id of the order we want to get
 * @return - a reference to the order if found, else returns a demi Order (needs to be deleted by caller)
 */
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
    return *demiOrder;
}

const vector<BaseAction*> &WareHouse::getActions() const{
    return actionsLog;
}

/**
 * @brief - this function closes the warehosue
 * 
 */
void WareHouse::close(){
    isOpen = false;
}

/**
 * @brief - this function opens the warehouse
 * 
 */
void WareHouse::open(){
    isOpen = true;
    cout << "Warehouse is open!" << endl;
}

int WareHouse::getOrdersNumber() const{
    return orderCounter;
}

int WareHouse::getVolunteersNumber() const{
    return volunteerCounter;
}

int WareHouse::getCustomersNumber() const{
    return customerCounter;
}

/**
 * @brief Construct a new Ware House:: Ware House object
 * 
 * @param otherWareHouse - a reference to a warehouse object
 */
WareHouse::WareHouse(const WareHouse& otherWareHouse): isOpen(otherWareHouse.isOpen), customerCounter(otherWareHouse.customerCounter),
volunteerCounter(otherWareHouse.volunteerCounter), parser(otherWareHouse.parser), orderCounter(otherWareHouse.orderCounter), demiCust(new CivilianCustomer(DOES_NOT_EXIST, "", DOES_NOT_EXIST, DOES_NOT_EXIST)), demiVol(new CollectorVolunteer(DOES_NOT_EXIST, "", DOES_NOT_EXIST)), demiOrder(new Order(DOES_NOT_EXIST, DOES_NOT_EXIST, DOES_NOT_EXIST)){
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

/**
 * @brief Construct a new Ware House:: Ware House object
 * 
 * @param otherWareHouse - a rvalue of type WareHosue
 */
WareHouse::WareHouse(WareHouse&& otherWareHouse): isOpen(otherWareHouse.isOpen), customerCounter(otherWareHouse.customerCounter),
volunteerCounter(otherWareHouse.volunteerCounter), parser(otherWareHouse.parser), orderCounter(otherWareHouse.orderCounter),
pendingOrders(otherWareHouse.pendingOrders), inProcessOrders(otherWareHouse.inProcessOrders), completedOrders(otherWareHouse.completedOrders),
customers(otherWareHouse.customers), volunteers(otherWareHouse.volunteers), actionsLog(otherWareHouse.actionsLog),
demiCust(otherWareHouse.demiCust), demiVol(otherWareHouse.demiVol), demiOrder(otherWareHouse.demiOrder){
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
    demiCust = nullptr;
    demiVol = nullptr;
    demiOrder = nullptr;
    otherWareHouse.actionsLog.clear();
    otherWareHouse.customers.clear();
    otherWareHouse.volunteers.clear();
    otherWareHouse.pendingOrders.clear();
    otherWareHouse.inProcessOrders.clear();
    otherWareHouse.completedOrders.clear();
}

/**
 * @brief - a move operator
 * 
 * @param other - a rvalue of type WareHosue
 * @return - a reference tp this after changing it's values to the values of other
 */
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

/**
 * @brief Destroy the Ware House:: Ware House object
 * 
 */
WareHouse::~WareHouse(){
    clear();
    delete demiCust;
    delete demiVol;
}

/**
 * @brief - assignment operator
 * 
 * @param other - a reference to a WareHouse object
 * @return - a reference to this after changing it's values to other values 
 */
WareHouse& WareHouse::operator=(const WareHouse& other){
    if(&other != this){
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        parser = other.parser;
        orderCounter = other.orderCounter;
        clear();
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

void WareHouse::clear(){
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

/**
 * @brief - this function adds a customer to the customers vector
 * 
 * @param customer - a pointer to the customer we want to add
 */
void WareHouse::addCustomer(Customer* customer){
    this->customers.push_back(customer);
    customerCounter++;
}

/**
 * @brief - this function adds a volunteer to the volunteers vector
 * 
 * @param volunteer - a pointer to the volunteer we want to add
 */
void WareHouse::addVolunteer(Volunteer* Volunteer){
    this->volunteers.push_back(Volunteer);
    volunteerCounter++;
}

/**
 * @brief - this functions proccesses the configuration file and adds all the customers and volunteers listed in it to the warehouse
 * 
 * @param configFilePath - the path to the configuration file given by the user
 */
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
            else{
                return;
            }
            customerCounter++;
        }
        else if(currLine[0].compare(VOLUNTEER) == 0){
            if(currLine[2].compare(COLLECTOR) == 0){
                volunteers.push_back(new CollectorVolunteer(volunteerCounter, currLine[1], stoi(currLine[3])));
            }
            else if(currLine[2].compare(LCOLLECTOR) == 0){
                volunteers.push_back(new LimitedCollectorVolunteer(volunteerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4])));
            }
            else if(currLine[2].compare(DRIVER) == 0){
                volunteers.push_back(new DriverVolunteer(volunteerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4])));
            }
            else if(currLine[2].compare(LDRIVER) == 0){
                volunteers.push_back(new LimitedDriverVolunteer(volunteerCounter, currLine[1], stoi(currLine[3]), stoi(currLine[4]), stoi(currLine[5])));
            }
            else{
                return;
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

/**
 * @brief - this function finds the first volunteer that is not processing an order
 * 
 * @param orderToHandle - he order we will give the volunteer
 * @return - a pointer to the volunteer we found
 */
Volunteer* WareHouse::findFreeVolunteer(Order& orderToHandle){
    for(auto& volunteer : volunteers){
        if(volunteer->canTakeOrder(orderToHandle)){
            return volunteer;
        }
    }
    return nullptr;
}

/**
 * @brief - this functions removes an order from the pending orders and moves it to the in process orders
 * 
 * @param orderToMove - the order to move from pending to in process
 */
void WareHouse::moveToInProcess(Order* orderToMove){
    pendingOrders.erase(find(pendingOrders.begin(), pendingOrders.end(), orderToMove));
    inProcessOrders.push_back(orderToMove);
}

/**
 * @brief - this functions removes an order from the in process orders and moves it to the completed orders
 * 
 * @param orderToMove - the order to move from in process to completed
 */
void WareHouse::moveToCompleted(Order* orderToMove){
    inProcessOrders.erase(find(inProcessOrders.begin(), inProcessOrders.end(), orderToMove));
    completedOrders.push_back(orderToMove);
}

/**
 * @brief - this functions removes an order from the in process orders and moves it to the pending orders
 * 
 * @param orderToMove - the order to move from in process to pending
 */
void WareHouse::moveToPending(Order* orderToMove){
    inProcessOrders.erase(find(inProcessOrders.begin(), inProcessOrders.end(), orderToMove));
    pendingOrders.push_back(orderToMove);
}

const vector<Volunteer*>& WareHouse::getVolunteers() const{
    return volunteers;    
}

/**
 * @brief - this function removes a volunteers from the volunteers list and deletes it from the heap
 * 
 * @param volToDel - the volunteer to delete
 */
void WareHouse::removeVolunteer(Volunteer* volToDel){
    volunteers.erase(find(volunteers.begin(), volunteers.end(), volToDel));
    delete volToDel;
}