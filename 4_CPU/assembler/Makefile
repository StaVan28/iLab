#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for assembler_modul
# version 1.6
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# source
BIN  = ../bin/assembler
SRC  = assembler.cpp ../labels/labels.cpp ../settings/settings.cpp ../flags/flags.cpp ../ram/ram.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)

SRC_ALL  = $(SRC) main_assembler.cpp
OBJ_ALL  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_ALL)))
OBJ_ALL := $(OBJ_ALL:%.cpp=%.o)
DEP_ALL  = $(OBJ_ALL:%.o=%.d)
LIB_ALL  = -ltxtlib

vpath %.cpp $(HDR_DIR)
vpath %.h   $(HDR_DIR)

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

#
## linking
$(BIN): $(OBJ_ALL)
	$(E) "    LINK:       " $@
	$(Q) $(CXX) $(WARNINGS) $^ -L$(LIB_DIR) $(LIB_ALL) -o $@  

#
## compiling
$(OBJ_DIR)/%.o: %.cpp
	$(E) "    C++:         " $@
	$(Q) ${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/main_assembler.o: main_assembler.cpp
$(OBJ_DIR)/assembler.o:      assembler.cpp
$(OBJ_DIR)/labels.o:         labels.cpp
$(OBJ_DIR)/settings.o:       settings.cpp
$(OBJ_DIR)/flags.o:	         flags.cpp
$(OBJ_DIR)/ram.o:            ram.cpp

-include ${DEP_ALL} 