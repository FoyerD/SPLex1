#include "Order.h"


Order::Order(int id, int customerId, int distance): id(id), customerId(customerId), distance(distance), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER), status(OrderStatus::PENDING){}

int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    return customerId;
}

void Order::setStatus(OrderStatus status){
    this->status = status;
}

void Order::setCollectorId(int collectorId){
    this->collectorId = collectorId;
}

void Order::setDriverId(int driverId){
    this->driverId = driverId;
}

int Order::getCollectorId() const{
    return collectorId;
}

int Order::getDriverId() const{
    return driverId;
}

OrderStatus Order::getStatus() const{
    return status;
}

const string Order::toString() const{
    ostringstream s;
    string coltId = (collectorId != NO_VOLUNTEER) ? to_string(collectorId) : NONE;
    string drvId = (driverId != NO_VOLUNTEER) ? to_string(driverId) : NONE;
    s << "OrderId: " << id + "/nOrderStatus: " << OrderStatusNames[int(status)] << 
    "/nCustomerId: " << customerId << "/nCollector: " << coltId 
    << "/nDriver: " << drvId;
    return s.str();
}

const int Order::getDistance() const{
    return distance;
}

const string Order::printStatus() const{
    ostringstream s;
    s << "OrderId: " << id + "/nOrderStatus: " << OrderStatusNames[int(status)];
    return s.str();
}

const string Order::printAfterClose() const{
    ostringstream s;
    s << "OrderId: " << id + ", CustomerID: " << customerId << ", OrderStatus: " << OrderStatusNames[int(status)];
    return s.str();
}
