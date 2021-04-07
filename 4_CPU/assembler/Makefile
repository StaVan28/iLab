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
SRC  = assembler.cpp ../labels/labels.cpp \
		../settings/settings.cpp ../flags/flags.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
HDR := $(SRC:%.cpp=%.h)

SRC_ALL = $(SRC)            main_assembler.cpp
OBJ_ALL = $(OBJ) $(OBJ_DIR)/main_assembler.o
HDR_ALL = $(HDR) $(HEAD_DIR)/txtlib.h 
LIB_ALL = -ltxtlib

vpath %.h   $(HDR_DIR)
vpath %.o   $(OBJ_DIR)
vpath %.cpp $(MODULES)

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

$(BIN): $(OBJ_ALL)
	$(E) "  LINK:       " $@
	$(Q) $(CXX) $^ -L$(LIB_DIR) $(LIB_ALL) -o $@  


$(OBJ_DIR)/main_assembler.o: main_assembler.cpp assembler.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/assembler.o: assembler.cpp assembler.h  txtlib.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/labels.o: ../labels/labels.cpp labels.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/settings.o: ../settings/settings.cpp CPU.h settings.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/flags.o:	../flags/flags.cpp CPU.h flags.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@