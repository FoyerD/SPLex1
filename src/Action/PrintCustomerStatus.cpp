#include "Action.h"
#include "WareHouse.h"
PrintCustomerStatus::PrintCustomerStatus(int id):
                                    BaseAction::BaseAction(),
                                    customerId(id){}
PrintCustomerStatus::~PrintCustomerStatus(){}

PrintCustomerStatus* PrintCustomerStatus::clone() const{
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const{
    return "customerStatus " +
            std::to_string(customerId) + " " + 
            statusToString[(int)BaseAction::getStatus()];
}


void PrintCustomerStatus::act(WareHouse& wareHouse){
    Customer& customerToPrint = wareHouse.getCustomer(customerId);
    if(customerToPrint.getId() == -1){
        error("Customer doesn't exist");
        return;
    }

    string strToPrint("CustmerID " + std::to_string(customerId) + "\n");
    for(int currID : customerToPrint.getOrdersIds()){
        strToPrint += wareHouse.getOrder(currID).printStatus() + "\n";
    }
    strToPrint += "numOrdersLeft: " + std::to_string(customerToPrint.getMaxOrders() - customerToPrint.getNumOrders());
    std::cout << strToPrint << std::endl;
}