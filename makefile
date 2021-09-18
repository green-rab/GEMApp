CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := bin
SRC     := src
TST		:= test
TST_SPY := test/spy
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := gema

# for CppUTest
CPPUTEST_HOME = /usr/local
CXXFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/MemoryLeakDetectorNewMacros.h
# CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LIBRARIES += -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

all: $(BIN)/$(EXECUTABLE)

run: clean all clear ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(TST)/*.cpp $(TST_SPY)/*.cpp
		$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	rm $(BIN)/*
