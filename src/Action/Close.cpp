#include "Action.h"
#include "WareHouse.h"
Close::Close(): BaseAction::BaseAction(){}
Close::~Close(){}

Close* Close::clone() const{
    return new Close(*this);
}

string Close::toString() const{
    return "close " + statusToString[(int)BaseAction::getStatus()];
}


void Close::act(WareHouse& wareHouse){
    for(Order* currOrder : wareHouse.getPendingOrders()){
        std::cout << currOrder->printAfterClose() << std::endl;
    }
    for(Order* currOrder : wareHouse.getInProccesOrders()){
        std::cout << currOrder->printAfterClose() << std::endl;
    }
    for(Order* currOrder : wareHouse.getCompletedOrders()){
        std::cout << currOrder->printAfterClose() << std::endl;
    }
    wareHouse.close();
}