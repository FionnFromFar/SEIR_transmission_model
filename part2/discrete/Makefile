# Makefile for Lattice SEIR Model
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3

# Target executable name
TARGET = simulation

# Source files
SRCS = main.cpp Agent.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)