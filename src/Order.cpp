#include "Order.h"


Order::Order(int id, int customerId, int distance): id(id), customerId(customerId), distance(distance){}

int Order::getId() const
{
    return id;
}

int Order::getCustomerId() const
{
    
}
