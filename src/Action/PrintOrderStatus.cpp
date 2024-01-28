#include "Action.h"
#include "WareHouse.h"
PrintOrderStatus::PrintOrderStatus(int id):
                                    BaseAction::BaseAction(),
                                    orderId(id){}
PrintOrderStatus::~PrintOrderStatus(){}

PrintOrderStatus* PrintOrderStatus::clone() const{
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const{
    return "orderStatus " +
            std::to_string(orderId) + " " + 
            statusToString[(int)BaseAction::getStatus()];
}


void PrintOrderStatus::act(WareHouse& wareHouse){
    Order& toPrint = wareHouse.getOrder(orderId);
    if(toPrint.getId() == -1){
        error("Order doesn't exist");
        return;
    }
    std::cout << toPrint.toString();
    complete();
}