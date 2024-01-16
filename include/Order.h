#pragma once

#include <string>
#include <vector>
#include <sstream>
using namespace std;
using std::string;
using std::vector;



class Volunteer;

enum class OrderStatus {
    PENDING,
    COLLECTING,
    DELIVERING,
    COMPLETED,
};

#define NO_VOLUNTEER -1
#define NONE "None"

vector<string> OrderStatusNames = {"PENDING", "COLLECTING", "DELIVERING", "COMPLETED"};

class Order {

    public:
        Order(int id, int customerId, int distance);
        int getId() const;
        int getCustomerId() const;
        void setStatus(OrderStatus status);
        void setCollectorId(int collectorId);
        void setDriverId(int driverId);
        int getCollectorId() const;
        int getDriverId() const;
        OrderStatus getStatus() const;
        const string toString() const;
        const int getDistance() const;
        const string printStatus() const;
    private:
        const int id;
        const int customerId;
        const int distance;
        OrderStatus status;
        int collectorId; //Initialized to NO_VOLUNTEER if no collector has been assigned yet
        int driverId; //Initialized to NO_VOLUNTEER if no driver has been assigned yet
};