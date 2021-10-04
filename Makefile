# Makefile for easyXpad
# Standard GNU project directory structure
SRC_FOLDER = src/
BUILD_FOLDER = build/
TRGT_FOLDER = bin/
EXECT = $(TRGT_FOLDER)main.out
# Include headers
INCL = -Iinclude/
# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -c -MMD -g -std=c++17
# Flags to link the objects
LDFLAGS = 
# .cpp, .o, and .d files
SRC_CPP = $(wildcard $(SRC_FOLDER)*.cpp)
SRC_OBJS = $(SRC_CPP:$(SRC_FOLDER)%.cpp=$(BUILD_FOLDER)%.o)
DEPS = $(APP_OBJS:%.o=%.d) $(SRC_OBJS:%.o=%.d)
# Links the object files to build the .out
$(EXECT): $(SRC_OBJS) | $(TRGT_FOLDER)
	$(CXX) -o $@ $^ $(LDFLAGS)
# Creates the target folder
$(TRGT_FOLDER):
	mkdir -p $@
# Compile cpp files and build the object files
$(SRC_OBJS):$(BUILD_FOLDER)%.o: $(SRC_FOLDER)%.cpp | $(BUILD_FOLDER)
	$(CXX) $(CXXFLAGS) $(INCL) $< -o $@
# Creates the object file's folder
$(BUILD_FOLDER):
	mkdir -p $@
# Dependencies
-include $(DEPS)
# Clean
clean:
	rm -f $(EXECT) $(wildcard $(BUILD_FOLDER)*.o) $(wildcard $(BUILD_FOLDER)*.d)
.PHONY: clean