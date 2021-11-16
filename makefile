# Makefile for easyXpad project
# Standard GNU project directory structure
APP_FOLDER = app/
SRC_FOLDER = src/
BUILD_FOLDER = build/
TRGT_FOLDER = bin/
LIB_FOLDER = lib/
EXECT = $(TRGT_FOLDER)main.out
SHARED_LIB = $(LIB_FOLDER)libeXpad.so
# Include headers
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
$(EXECT): $(SRC_OBJS) $(APP_OBJS) $(SHARED_LIB) | $(TRGT_FOLDER)
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
	mkdir /usr/local/include/easyXpad/
	cp include/eXpad.h /usr/local/include/easyXpad/
	cp lib/libeXpad.so /usr/local/lib/
uninstall:
	rm -f /usr/local/include/easyXpad /usr/local/lib/libeXpad.so
# Clean
clean:
	rm -f $(EXECT) $(wildcard $(BUILD_FOLDER)*.o) $(wildcard $(BUILD_FOLDER)*.d) $(wildcard $(LIB_FOLDER)*.so)
.PHONY: clean