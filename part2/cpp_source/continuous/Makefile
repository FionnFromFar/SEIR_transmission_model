#Adding in the variables
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2 #O2 optimisation
TARGET = simulation
OBJS = main.o Agent.o

all: $(TARGET) 

$(TARGET): $(OBJS)
#tells what files to compile and into what result ie agent.cpp and main.cpp into simualtion
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp Agent.hpp	
#main.o depends on main.cpp and Agent.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Agent.o: Agent.cpp Agent.hpp
#Agent.o depends on Agent.cpp and Agent.hpp
	$(CXX) $(CXXFLAGS) -c Agent.cpp

#Cleaning up the directory
clean: 
	rm -f $(OBJS) $(TARGET)
