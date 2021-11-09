CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN      := bin
INCLUDE  := include
SRC      := source
SRC_UNIT := source/unit
TST		 := test
TST_SPY  := test/spy
TST_UNIT := test/unit
SERVICES := userServices

LIBRARIES  :=
EXECUTABLE := gemapp

# for CppUTest
CPPUTEST_HOME = /usr/local
CXXFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/MemoryLeakDetectorNewMacros.h
LIBRARIES += -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

#all: $(BIN)/$(EXECUTABLE)

# run: clean all clear ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(SRC_UNIT)/*.cpp $(TST)/*.cpp $(TST_SPY)/*.cpp $(TST_UNIT)/*.cpp $(SERVICES)/*.cpp
		$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	rm -f $(BIN)/$(EXECUTABLE)
	rm -rf $(BIN)/*.dSYM
