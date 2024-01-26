all: clean bin/warehouse

bin/warehouse: bin/main.o bin/Customer.o bin/Order.o bin/CollectorVolunteer.o bin/DriverVolunteer.o \
	bin/LimitedCollectorVolunteer.o bin/LimitedDriverVolunteer.o bin/Volunteer.o
	#bin/WareHouse.o bin/AddOrder.o bin/BaseAction.o bin/SimulateStep.o bin/AddCustomer.o bin/PrintOrderStatus.o \
	#bin/PrintCustomerStatus.o bin/PrintVolunteerStatus.o bin/PrintActionsLog.o bin/Close.o \
	#bin/BackupWareHouse.o bin/RestoreWareHouse.o

bin/main.o: src/main.cpp
	g++	-g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp

bin/Customer.o: src/Customer.cpp
	g++	-g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Customer.o src/Customer.cpp

bin/Order.o: src/Order.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Order.o src/Order.cpp

bin/CollectorVolunteer.o: src/Volunteer/CollectorVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/CollectorVolunteer.o src/Volunteer/CollectorVolunteer.cpp

bin/DriverVolunteer.o: src/Volunteer/DriverVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/DriverVolunteer.o src/Volunteer/DriverVolunteer.cpp

bin/LimitedCollectorVolunteer.o: src/Volunteer/LimitedCollectorVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/LimitedCollectorVolunteer.o src/Volunteer/LimitedCollectorVolunteer.cpp

bin/LimitedDriverVolunteer.o: src/Volunteer/LimitedDriverVolunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/LimitedDriverVolunteer.o src/Volunteer/LimitedDriverVolunteer.cpp

bin/Volunteer.o: src/Volunteer/Volunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Volunteer.o src/Volunteer/Volunteer.cpp

#bin/WareHouse.o: src/WareHouse.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/WareHouse.o src/WareHouse.cpp

#bin/AddOrder.o: src/Action/AddOrder.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/AddOrder.o src/Action/AddOrder.cpp

#bin/BaseAction.o: src/Action/BaseAction.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/BaseAction.o src/Action/BaseAction.cpp

#bin/SimulateStep.o: src/Action/SimulateStep.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/SimulateStep.o src/Action/SimulateStep.cpp

#bin/AddCustomer.o: src/Action/AddCustomer.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/AddCustomer.o src/Action/AddCustomer.cpp

#bin/PrintOrderStatus.o: src/Action/PrintOrderStatus.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintOrderStatus.o src/Action/PrintOrderStatus.cpp

#bin/PrintCustomerStatus.o: src/Action/PrintCustomerStatus.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintCustomerStatus.o src/Action/PrintCustomerStatus.cpp

#bin/PrintVolunteerStatus.o: src/Action/PrintVolunteerStatus.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintVolunteerStatus.o src/Action/PrintVolunteerStatus.cpp

#bin/PrintActionsLog.o: src/Action/PrintActionsLog.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/PrintActionsLog.o src/Action/PrintActionsLog.cpp

#bin/Close.o: src/Action/Close.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Close.o src/Action/Close.cpp

#bin/BackupWareHouse.o: src/Action/BackupWareHouse.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/BackupWareHouse.o src/Action/BackupWareHouse.cpp

#bin/RestoreWareHouse.o: src/Action/RestoreWareHouse.cpp
	#g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/RestoreWareHouse.o src/Action/RestoreWareHouse.cpp

clean:
	rm -f bin/*

valgrind:
	valgrind --leak-check=full --show-reachable=yes bin/warehouse



