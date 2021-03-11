#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for stack_project
# version 1.2
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# compiler settings
CXX      = g++
CXXFLAGS = -Wall

# path for directories
HEAD_DIR = ../include/headers
LIB_DIR  = ../include/libs
OBJ_DIR  = ./obj
BIN_DIR  = ./bin
TXT_DIR = ./txt

# files settings
BINARY  = stack
SOURCE  = main.cpp stack.cpp stack_error.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCE))
HEADERS = stack.h

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

# make program
.PHONY: all
all: $(BIN_DIR)/$(BINARY)

# linking all OBJECTS files and Library for getting BINARY 
$(BIN_DIR)/$(BINARY): $(OBJ_DIR)/main.o $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_error.o $(LIB_DIR)/libstack.a 
	$(CXX) -o $(BIN_DIR)/$(BINARY) $^

# creating a stack library in ../libs
$(LIB_DIR)/libstack.a: $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_error.o
	ar cr $(LIB_DIR)/libstack.a $^

# getting all OBJECTS files from SOURCES
$(OBJ_DIR)/%.o: %.cpp $(HEAD_DIR)/$(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(HEAD_DIR) 

# installs all the necessary dirs
.PHONY: install 
install: 
	mkdir -p $(HEAD_DIR) $(LIB_DIR) $(OBJ_DIR) $(BIN_DIR) $(TXT_DIR)

# cleans all OBJECTS, LIBS and BINARY files when using the "cleanall" flag
.PHONY: cleanall cleanbin cleanobj cleanlib cleandump
cleanall: cleanbin cleanobj cleanlib cleandump

cleanbin:
	-rm $(BIN_DIR)/$(BINARY) 

cleanobj:
	-rm $(OBJ_DIR)/main.o $(OBJ_DIR)/stack.o $(OBJ_DIR)/stack_error.o

cleanlib:
	-rm $(LIB_DIR)/libstack.a

cleandump:
	-rm $(TXT_DIR)/dump_stack.txt
