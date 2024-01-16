#include "Order.h"


Order::Order(int id, int customerId, int distance): id(id), customerId(customerId), distance(distance){}

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
    s << "OrderId: " << id + "/nOrderStatus: " << int(status) << 
    "/nCustomerId: " << customerId << "/nCollector: " << collectorId 
    << "/nDriver: " << driverId;
    return s.str();
}
