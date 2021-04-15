#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for CPU_modul
# version 1.6
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# source
BIN  = ../bin/CPU
SRC  = CPU.cpp ../errors/errors.cpp ../settings/settings.cpp ../flags/flags.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)

SRC_ALL  = $(SRC) main_CPU.cpp
OBJ_ALL  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_ALL)))
OBJ_ALL := $(OBJ_ALL:%.cpp=%.o)
DEP_ALL  = $(OBJ_ALL:%.o=%.d)
LIB_ALL  = -lstack -ltxtlib

PROJ_LIB = libCPU.a

vpath %.cpp $(HDR_DIR)
vpath %.h   $(HDR_DIR)

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

default: $(BIN)

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

$(OBJ_DIR)/main_CPU.o: main_CPU.cpp 
$(OBJ_DIR)/CPU.o:      CPU.cpp      
$(OBJ_DIR)/errors.o:   errors.cpp   
$(OBJ_DIR)/settings.o: settings.cpp 
$(OBJ_DIR)/flags.o:	   flags.cpp    

-include ${DEP_ALL} 