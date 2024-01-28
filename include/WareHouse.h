#pragma once
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "Order.h"
#include "Customer.h"
#include "Parser.h"
#include "Volunteer.h"
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
#define LDRIVER "limited_driver"
#define LCOLLECTOR "limited_collector"
// Warehouse responsible for Volunteers, Customers Actions, and Orders.


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
        const vector<Order*>& getPendingOrders() const;
        const vector<Order*>& getInProccesOrders() const;
        const vector<Order*>& getCompletedOrders() const;
        int getOrdersNumber() const;
        int getVolunteersNumber() const;
        int getCustomersNumber() const;
        void close();
        void open();
        ~WareHouse();
        WareHouse& operator=(const WareHouse& other);
        WareHouse& operator=(WareHouse&& other);
        Volunteer* findFreeVolunteer(Order& orderToHandle);
        void moveToInProcess(Order* orderToMove);
        void moveToCompleted(Order* orderToMove);
        void moveToPending(Order* orderToMove);
        const vector<Volunteer*>& getVolunteers() const;
        void removeVolunteer(Volunteer* volToDel);
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
        void clear();
        Customer* demiCust;
        Volunteer* demiVol;
        Order* demiOrder;
};

extern WareHouse* backup;