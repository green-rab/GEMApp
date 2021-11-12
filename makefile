# flags
CXXCMD   := g++
CXXFLAGS := -std=c++17 -ggdb

# exe
EXECUTABLE := gemapp
BIN        := bin

# path
INCLUDE    := include
SRC        := source/*.cpp
SRC_UNIT   := source/unit/*.cpp
SERVICE    := userServices/*.cpp
TST        := test/*.cpp
TST_UNIT   := test/unit/*.cpp
TST_SPY    := test/spy/*.cpp

LIBRARIES  :=

# for CppUTest - only for debug build
CPPUTEST_HOME = /usr/local

# all: clean debug

# debug
debug:	$(BIN)/debug/$(EXECUTABLE)
debug:	CXXCMD    += -DDEBUG -g
debug:	CXXCMD    += -DTESTMODE
debug:	CXXFLAGS  += -I$(CPPUTEST_HOME)/include
# debug: CXXFLAGS  += -include $(CPPUTEST_HOME)/include/MemoryLeakDetectorNewMacros.h
debug:	LIBRARIES += -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

# rpi
rpi:	$(BIN)/rpi/$(EXECUTABLE)
rpi:	CXXCMD    += -O

# debug
$(BIN)/debug/$(EXECUTABLE): $(SRC) $(SRC_UNIT) $(SERVICE) $(TST) $(TST_UNIT) $(TST_SPY)
		@ mkdir -p $(BIN)/debug
		$(CXXCMD) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

# rpi
$(BIN)/rpi/$(EXECUTABLE): $(SRC) $(SRC_UNIT) $(SERVICE)
		@ mkdir -p $(BIN)/rpi
		$(CXXCMD) $(CXXFLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	rm -rf $(BIN)/debug
	rm -rf $(BIN)/rpi
