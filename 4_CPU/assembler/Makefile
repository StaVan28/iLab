#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for assembler_modul
# version 1.5
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# source
BIN  = ../bin/assembler
SRC  = assembler.cpp ../labels/labels.cpp \
		../settings/settings.cpp ../flags/flags.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
DEP := $(OBJ:%.o=%.d)
HDR := $(SRC:%.cpp=%.h)

SRC_ALL = $(SRC)            main_assembler.cpp
OBJ_ALL = $(OBJ) $(OBJ_DIR)/main_assembler.o
DEP_ALL = $(DEP) $(OBJ_DIR)/main_assembler.d
HDR_ALL = $(HDR) $(HEAD_DIR)/txtlib.h 
LIB_ALL = -ltxtlib

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


$(OBJ_DIR)/main_assembler.o: main_assembler.cpp assembler.h
$(OBJ_DIR)/assembler.o:      assembler.cpp      assembler.h  txtlib.h
$(OBJ_DIR)/labels.o:         labels.cpp         labels.h
$(OBJ_DIR)/settings.o:       settings.cpp       CPU.h settings.h
$(OBJ_DIR)/flags.o:	         flags.cpp          CPU.h flags.h

-include ${DEP_ALL} 