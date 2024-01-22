#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "Order.h"
#include "Customer.h"
#include "Parser.h"
#include "Volunteer.h"
#include "Action.h"
class BaseAction;
class Volunteer;
#define CUSTOMER "customer"
#define VOLUNTEER "volunteer"
#define SOLDIER "soldier"
#define CIVILIAN "civilian"
#define COLLECTOR "collector"
#define DRIVER "driver"
#define STEP "step"
#define ADDORDER "order"
#define ORDER_STATUS "orderStatus"
#define CUSTOMER_STATUS "customerStatus"
#define VOLUNTEER_STATUS "volunteerStatus"
#define LOG "log"
#define CLOSE "close"
#define BACKUP "backup"
#define RESTORE "restore"
#define DOES_NOT_EXIST -1
#define CASE_DRIVER 5
#define CASE_LDRIVER 6
#define CASE_COLLECTOR 4
#define CASE_LCOLLECTOR 5
// Warehouse responsible for Volunteers, Customers Actions, and Orders.
extern WareHouse* backup;

class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(const WareHouse& otherWareHouse);
        WareHouse(WareHouse&& otherWareHouse);
        void start();
        void addOrder(Order* order);
        void addCustomer(Customer* customer);
        void addVolunteer(Volunteer* Volunteer);
        void addAction(BaseAction* action);
        Customer &getCustomer(int customerId) const;
        Volunteer &getVolunteer(int volunteerId) const;
        Order &getOrder(int orderId) const;
        const vector<BaseAction*> &getActions() const;
        vector<Order*>& getPendingOrders();
        vector<Order*>& getInProccesOrders();
        vector<Order*>& getCompletedOrders();
        int getOrdersNumber() const;
        void close();
        void open();
        ~WareHouse();
        WareHouse& operator=(const WareHouse& other);
        WareHouse& operator=(WareHouse&& other);
    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        Parser parser;
        void proccessConfigFile(const string &configFilePath);
        int orderCounter;
};