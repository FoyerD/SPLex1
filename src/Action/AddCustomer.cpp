#include "Action.h"
#include "WareHouse.h"
AddCustomer::AddCustomer(string customerName, string customerType, int distance, int maxOrders):
                        BaseAction::BaseAction(),
                        customerName(customerName),
                        customerType(stringToType(customerType)),
                        distance(distance),
                        maxOrders(maxOrders){}
AddCustomer::~AddCustomer(){}

AddCustomer* AddCustomer::clone() const{return new AddCustomer(*this);}

string AddCustomer::toString() const{
    return "customer " +
            customerName + " " +
            typeToString[(int)customerType] + " " +
            std::to_string(distance) + " " +
            std::to_string(maxOrders) + " " + 
            statusToString[(int)BaseAction::getStatus()]; 
}

void AddCustomer::act(WareHouse& wareHouse){
    int id = wareHouse.getCustomersNumber();
    switch (customerType)
    {
    case CustomerType::Civilian:
        wareHouse.addCustomer(new CivilianCustomer(id, customerName, distance, maxOrders));
        break;
    case CustomerType::Soldier:
        wareHouse.addCustomer(new SoldierCustomer(id, customerName, distance, maxOrders));
        break;
    default:
        break;
    }
    complete();
}