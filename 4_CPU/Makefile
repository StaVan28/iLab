#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for CPU_project
# version 1.5
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# choose release or debug mode
LAUNCH_MODE = debug

# path for directories
BIN_DIR  = bin
HEAD_DIR = ../include/headers
LIB_DIR  = ../include/libs

# source
BIN      = $(BIN_DIR)/CPU
BIN_TEST = $(BIN_DIR)/unit_tests

SRC_ALL = CPU.cpp CPU_assembler.cpp labels.cpp
OBJ_ALL = CPU.o   CPU_assembler.o   labels.o
HDR_ALL = CPU.h                     labels.h   $(HEAD_DIR)/stack.h $(HEAD_DIR)/txtlib.h

SRC = $(SRC_ALL) main.cpp
OBJ = $(OBJ_ALL) main.o
HDR = $(HDR_ALL)
LIB = -lstack -ltxtlib

SRC_TEST = $(SRC) unit_tests.cpp main_tests.cpp
OBJ_TEST = $(OBJ) unit_tests.o   main_tests.o
HDR_TEST = $(HDR) unit_tests.h

PROJ_LIB = libCPU.a

# compiler settings
CXX      = g++ 
WARNINGS = -Wall -Werror -Wextra 
CXXFLAGS =   

DEBUG_MODE   = -g3 -O0 
RELEASE_MODE = -g0 -Ofast 

ifeq ($(LAUNCH_MODE),debug)
	CXXFLAGS += $(DEBUG_MODE)
else
	CXXFLAGS += $(RELEASE_MODE)
endif

# defines for OS
#DEFINES  =
#uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')
#
#ifeq ($(uname_S),Linux)
#    DEFINES = -DPOSIX -D_XOPEN_SOURCE=700 
#endif

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

.PHONY: all

#
## launch with valgrind(default)
all: $(BIN)
	valgrind $(BIN)

#
## linking
$(BIN): $(OBJ)
	@ echo "  LINK:  " $@
	@ $(CXX) $^ -L$(LIB_DIR) $(LIB) -o $@  

$(BIN_TEST): $(OBJ_TEST)
	@ echo "  LINK:  " $@
	@ $(CXX) $^ -L$(LIB_DIR) $(LIB) -o $@ 

#
## compiling
.cpp.o:
	@ echo "  C++    " $@
	@ ${CXX} ${CXXFLAGS} $(WARNINGS) -I$(HEAD_DIR) -c $*.cpp 

.c.o:
	@ echo "  C      " $@
	@ ${CXX} ${CXXFLAGS} $(WARNINGS) -I$(HEAD_DIR) -c $*.c 

main.o:          main.cpp $(HDR)
CPU.o:           CPU.cpp $(HDR)
CPU_assembler.o: CPU_assembler.cpp $(HDR)  
labels.o:        labels.cpp $(HDR)
unit_tests.o:    unit_tests.cpp $(HDR) 

#
## additional features
.PHONY: clean errors tags rebuild git no_valgrind unit_tests project

clean:
	@ echo "  CLEAN"
	@ rm -f $(BIN) makeout tags *.o

errors:
	@rm -f makeout
	make $(BIN) > makeout

tags: ${SRC}
	@rm -f tags
	ctags ${SRC}

rebuild: clean all

no_valgrind: $(BIN)
	@ $(BIN)

unit_tests: $(BIN_TEST)
	@ $(BIN_TEST)

git:
	git add --all
	git commit -m "auto commit: 4_CPU"

#
## generate lib and copy main header to ../include
project: $(PROJ_LIB) $(BIN) CPU.h
	@ cp CPU.h    $(HEAD_DIR)/
	@ mv $(PROJ_LIB) $(LIB_DIR)/

$(PROJ_LIB): $(OBJ)
	@ ar cr $@ $^