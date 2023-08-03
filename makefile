# Makefile for easyXpad project
# Standard GNU project directory structure
APP_FOLDER = app/
SRC_FOLDER = src/
BUILD_FOLDER = build/
TRGT_FOLDER = bin/
LIB_FOLDER = lib/
EXECT = $(TRGT_FOLDER)main.out
SHARED_LIB = $(LIB_FOLDER)libeXpad.so
# Include headers - this tells the compiler where to find .h files
INCLUDES = -Iinclude/
# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -c -MMD -g -std=c++17 -fPIC
# Flags to link the objects
LDFLAGS = 
# Flags to create shared libraries
SHLFLAGS = -shared
# .cpp, .o, and .d files
SRC_CPP = $(wildcard $(SRC_FOLDER)*.cpp)
APP_CPP = $(wildcard $(APP_FOLDER)*.cpp)
SRC_OBJS = $(SRC_CPP:$(SRC_FOLDER)%.cpp=$(BUILD_FOLDER)%.o)
APP_OBJS = $(APP_CPP:$(APP_FOLDER)%.cpp=$(BUILD_FOLDER)%.o)
DEPS = $(SRC_OBJS:%.o=%.d) $(APP_OBJS:%.o=%.d)
# Links the object files to build the .out
$(EXECT): $(APP_OBJS) $(SHARED_LIB) | $(TRGT_FOLDER)
	$(CXX) -o $@ $^ $(LDFLAGS)
# Creates the target folder
$(TRGT_FOLDER):
	mkdir -p $@
# Creating shared library for easyXpad
$(SHARED_LIB): $(SRC_OBJS) | $(LIB_FOLDER)
	$(CXX) $(SHLFLAGS) -o $(SHARED_LIB) $(SRC_OBJS)
# Creates the lib folder
$(LIB_FOLDER):
	mkdir -p $@
# Compile cpp files and build the object files
$(SRC_OBJS):$(BUILD_FOLDER)%.o: $(SRC_FOLDER)%.cpp | $(BUILD_FOLDER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@
$(APP_OBJS):$(BUILD_FOLDER)%.o: $(APP_FOLDER)%.cpp | $(BUILD_FOLDER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@
# Creates the object file's folder
$(BUILD_FOLDER):
	mkdir -p $@
# Dependencies
-include $(DEPS)
# Install
install:
	mkdir -p /usr/local/include/easyXpad/
	cp include/eXpad.h /usr/local/include/easyXpad/
	cp include/eXpad.h /usr/include/easyXpad/
	cp lib/libeXpad.so /usr/local/lib/
	cp lib/libeXpad.so /usr/lib/
uninstall:
	rm -f /usr/local/include/easyXpad /usr/local/lib/libeXpad.so
# Clean
clean:
	rm -f $(EXECT) $(wildcard $(BUILD_FOLDER)*.o) $(wildcard $(BUILD_FOLDER)*.d) $(wildcard $(LIB_FOLDER)*.so)
.PHONY: clean
# The result produced by this makefile is:
# 1 # g++ -c -MMD -g -std=c++17 -fPIC -Iinclude/ app/main.cpp -o build/main.o
# 2 # g++ -c -MMD -g -std=c++17 -fPIC -Iinclude/ src/eXpad.cpp -o build/eXpad.o
# 3 # g++ -shared -o lib/libeXpad.so build/eXpad.o
# 4 # g++ -o bin/main.out build/main.o lib/libeXpad.so 
# -------------------------------------------------------------------
# Line 1: compile object for main.o from cpp code main.cpp
# Line 2: compile object for eXpad.o from eXpad.cpp code
# Line 3: compile the sharedlib libeXpad.so from the eXpad.o file
# Line 4: compile the executable main.out from the main.o object and the libeXpad.so share lib
# Line 4 could be also the following if the .header is included on /usr/local/include/ or /usr/include/
# and the share library "libeXpad.so" is included on /usr/local/lib/ or /usr/lib/
# Line 4 fancy # g++ -o bin/main.out build/main.o -leXpad
