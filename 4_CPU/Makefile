#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for CPU_project
# version 1.2
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# compiler settings
CXX      = g++
CXXFLAGS = -Wall

# path for directories
HEAD_DIR  = ../include/headers
LIB_DIR   = ../include/libs
OBJ_DIR   = ./obj
BIN_DIR   = ./bin
TXT_DIR   = ./txt
TESTS_DIR = ./unit_tests

# files settings
BINARY  = CPU
SOURCE  = main.cpp CPU.cpp CPU_assembler.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCE))
HEADERS = CPU.h

# unit_tests settings
BIN_TESTS    = unit_tests
SOURCE_TESTS = main_tests.cpp unit_tests.cpp
OBJECTS_TESTS = $(subst .cpp,.o,$(SOURCE))
HEADERS_TESTS = unit_tests.h

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

# make program
.PHONY: all
all: $(BIN_DIR)/$(BINARY)
	
# linking all OBJECTS files and Library for getting BINARY and launch CPU
$(BIN_DIR)/$(BINARY): $(OBJ_DIR)/main.o $(OBJ_DIR)/CPU.o $(OBJ_DIR)/CPU_assembler.o
	$(CXX) -o $(BIN_DIR)/$(BINARY) $^ -L$(LIB_DIR) -ltxtlib -lstack 
	./bin/CPU

# getting all OBJECTS files from SOURCES
$(OBJ_DIR)/%.o: %.cpp $(HEAD_DIR)/$(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(HEAD_DIR)

# installs all the necessary dirs and file for input(source.txt)
.PHONY: install 
install: 
	mkdir -p $(HEAD_DIR) $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR) $(TXT_DIR)
	touch $(TXT_DIR)/source

# making different tests with flag "unit_test"
unit_tests: $(BIN_DIR)/$(BIN_TESTS)

# linking OBJECTS files for unit_tests and Library for getting unit_tests BINARY and launch unit_tests
$(BIN_DIR)/$(BIN_TESTS): $(OBJ_DIR)/CPU.o $(OBJ_DIR)/CPU_assembler.o $(TESTS_DIR)/$(OBJ_DIR)/main_tests.o $(TESTS_DIR)/$(OBJ_DIR)/unit_tests.o
	$(CXX) -o $(BIN_DIR)/$(BIN_TESTS) $^ -L$(LIB_DIR) -ltxtlib -lstack
	./bin/unit_tests

# getting all OBJECTS files from unit_tests SOURCES
$(TESTS_DIR)/$(OBJ_DIR)/main_tests.o: $(TESTS_DIR)/main_tests.cpp $(TESTS_DIR)/headers/$(HEADERS_TESTS) $(HEAD_DIR)/$(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(TESTS_DIR)/headers -I$(HEAD_DIR)

# getting all OBJECTS files from unit_tests SOURCES
$(TESTS_DIR)/$(OBJ_DIR)/unit_tests.o: $(TESTS_DIR)/unit_tests.cpp $(TESTS_DIR)/headers/$(HEADERS_TESTS) $(HEAD_DIR)/$(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(TESTS_DIR)/headers -I$(HEAD_DIR)

# cleans all OBJECTS, LIBS and BINARY files when using the "cleanall" flag
.PHONY: cleanall cleanbin cleanobj cleandump
cleanall: cleanbin cleanobj cleandump 

cleanbin:
	-rm $(BIN_DIR)/$(BINARY) $(BIN_DIR)/$(BIN_TESTS)

cleanobj:
	-rm $(OBJ_DIR)/main.o $(OBJ_DIR)/CPU.o $(OBJ_DIR)/CPU_assembler.o

cleandump:
	-rm $(TXT_DIR)/dump_stack.txt $(TXT_DIR)/dump_txtlib.txt
