#include "Action.h"


/**
 * @param numOfSteps - number of steps te action simulates
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
void SimulateStep::singleStep(WareHouse& wareHouse){
    phase1(wareHouse);
    phase2(wareHouse);
    phase3(wareHouse);
    phase4(wareHouse);
}

/**
 * Iterates on all pending orders,
 * attempts to handle each one to a proper volunteer
 * than asked the wareHouse to move the order to the proper vector
 * @param wareHouse - ref to the wareHouse to simulate on
*/
void SimulateStep::phase1(WareHouse& wareHouse){
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
            case OrderStatus::COLLECTING:
                currOrder->setDriverId(freeVolunteer->getId());
                currOrder->setStatus(OrderStatus::DELIVERING);
            default:
                break;
        };

        ordersToMove.push_back(currOrder);
    }

    for(Order* currOrder : ordersToMove){
        wareHouse.moveToInProcess(currOrder);
    }
}

void SimulateStep::phase2(WareHouse& wareHouse){
    for(Volunteer* currVolunteer : wareHouse.getVolunteers()){//!TODO
        currVolunteer->step();
    }
}

void SimulateStep::phase3(WareHouse& wareHouse){
    for(Volunteer* currVolunteer : wareHouse.getVolunteers()){//!TODO
        if(currVolunteer->getCompletedOrderId() == NO_ORDER) continue;
        Order& currOrder(wareHouse.getOrder(currVolunteer->getCompletedOrderId()));

        currVolunteer->completeOrder();
    }
}

