CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = smart_home

SRC = src/main.cpp \
      src/sensor_simulator.cpp \
      src/occupancy.cpp \
      src/hvac_controller.cpp \
      src/logger.cpp \
      src/config.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: tests/test_cases.cpp src/hvac_controller.cpp src/occupancy.cpp
	$(CXX) $(CXXFLAGS) -DTEST_MODE -o test_cases tests/test_cases.cpp src/hvac_controller.cpp src/occupancy.cpp

clean:
	rm -f $(OBJ) $(TARGET) test_cases

.PHONY: all test clean
