#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for CPU_modul
# version 1.5
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# source
BIN  = ../bin/CPU
SRC  = CPU.cpp ../errors/errors.cpp \
		../settings/settings.cpp ../flags/flags.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
DEP := $(OBJ:%.o=%.d)
HDR := $(SRC:%.cpp=%.h)

SRC_ALL = $(SRC)            main_CPU.cpp
OBJ_ALL = $(OBJ) $(OBJ_DIR)/main_CPU.o
DEP_ALL = $(DEP) $(OBJ_DIR)/main_CPU.d
HDR_ALL = $(HDR) $(HEAD_DIR)/stack.h $(HEAD_DIR)/txtlib.h 
LIB_ALL = -lstack -ltxtlib

vpath %.cpp $(HDR_DIR)
vpath %.h   $(HDR_DIR)

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

#
## linking
$(BIN): $(OBJ_ALL)
	$(E) "    LINK:        " $@
	$(Q) $(CXX) $(WARNINGS) $^ -L$(LIB_DIR) $(LIB_ALL) -o $@  

#
## compiling
$(OBJ_DIR)/%.o: %.cpp
	$(E) "    C++:         " $@
	$(Q) ${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/main_CPU.o: main_CPU.cpp CPU.h
$(OBJ_DIR)/CPU.o:      CPU.cpp      CPU.h settings.h flags.h 
$(OBJ_DIR)/errors.o:   errors.cpp   CPU.h errors.h
$(OBJ_DIR)/settings.o: settings.cpp CPU.h settings.h
$(OBJ_DIR)/flags.o:	   flags.cpp    CPU.h flags.h

-include ${DEP_ALL} 