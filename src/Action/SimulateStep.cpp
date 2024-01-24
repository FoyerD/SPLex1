#include "Action.h"


/**
 * @param numOfSteps - number of steps the action simulates
*/
SimulateStep::SimulateStep(int numOfSteps):
                        BaseAction::BaseAction(),
                        numOfSteps(numOfSteps){}
SimulateStep::~SimulateStep(){}

SimulateStep* SimulateStep::clone() const{
    return new SimulateStep(*this);
}

string SimulateStep::toString() const{
    return "simulateStep " + std::to_string(numOfSteps);
}


/**
 * calles singleStep numOfSteps times
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::act(WareHouse& wareHouse){
    for(int i = 0; i < numOfSteps;i++){
        singleStep(wareHouse);
    }
}


/**
 * simply calles each of the 4 phases of a step in order
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::singleStep(WareHouse& wareHouse) const{
    phase1(wareHouse);
    phase2(wareHouse);
    phase3(wareHouse);
    phase4(wareHouse);
}

/**
 * Iterates on all pending orders,
 * attempts to hand each one to a proper volunteer
 * than asked the wareHouse to move the orders handed to the proper vector
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::phase1(WareHouse& wareHouse) const{
    Volunteer* freeVolunteer = nullptr;
    vector<Order*> ordersToMove;

    for(Order* currOrder : wareHouse.getPendingOrders()){

        if(currOrder->getStatus() != OrderStatus::COLLECTING || currOrder->getStatus() != OrderStatus::PENDING) continue;//ensuring we deal with packeges of right status
        freeVolunteer = wareHouse.findFreeVolunteer(*currOrder);
        if(freeVolunteer == nullptr) continue;//ensuring we have a free volunteer
        
        freeVolunteer->acceptOrder(*currOrder);
        switch (currOrder->getStatus()){
            case OrderStatus::PENDING:
                currOrder->setCollectorId(freeVolunteer->getId());
                currOrder->setStatus(OrderStatus::COLLECTING);
                break;
            case OrderStatus::COLLECTING:
                currOrder->setDriverId(freeVolunteer->getId());
                currOrder->setStatus(OrderStatus::DELIVERING);
                break;
            default:
                break;
        };

        ordersToMove.push_back(currOrder);
    }

    for(Order* currOrder : ordersToMove){
        wareHouse.moveToInProcess(currOrder);
    }
}

/**
 * iterates over all volunteers, performs one step for each(see volunteer for step)
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::phase2(WareHouse& wareHouse) const{
    for(Volunteer* currVolunteer : wareHouse.getVolunteers()){//!TODO
        currVolunteer->step();
    }
}

/**
 * iterates over all volunteers, for each check if he has completed order
 * if he does, move collected order to pending, delivered order to completed and change status
 * if volunteer is limited decreas the ordersLeft field
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::phase3(WareHouse& wareHouse) const{
    int currOrderID = 0;
    for(Volunteer* currVolunteer : wareHouse.getVolunteers()){//!TODO
        if(currVolunteer->getCompletedOrderId() == NO_ORDER) continue;

        currOrderID = currVolunteer->completeOrder();
        Order& currOrder(wareHouse.getOrder(currOrderID));

        if(currOrder.getStatus() == OrderStatus::COLLECTING){
            wareHouse.moveToPending(&currOrder);
        }

        if(currOrder.getStatus() == OrderStatus::DELIVERING){
            currOrder.setStatus(OrderStatus::COMPLETED);
                wareHouse.moveToCompleted(&currOrder);
        }
    }
}

/**
 * iterates over all volunteers and tell warehouse
 * to remove each one that have no orders left
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::phase4(WareHouse& wareHouse) const{
    for(Volunteer* currVolunteer : wareHouse.getVolunteers()){
        if(!currVolunteer->hasOrdersLeft()) wareHouse.removeVolunteer(currVolunteer);
    }
}

