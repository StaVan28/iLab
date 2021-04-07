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
SRC  = CPU.cpp ../errors/errors.cpp \
		../settings/settings.cpp ../flags/flags.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
HDR := $(SRC:%.cpp=%.h)

SRC_ALL = $(SRC)            main_CPU.cpp
OBJ_ALL = $(OBJ) $(OBJ_DIR)/main_CPU.o
HDR_ALL = $(HDR) $(HEAD_DIR)/stack.h $(HEAD_DIR)/txtlib.h 
LIB_ALL = -lstack -ltxtlib

vpath %.h   $(HDR_DIR)
vpath %.o   $(OBJ_DIR)
vpath %.cpp $(MODULES)

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

$(BIN): $(OBJ_ALL)
	$(E) "  LINK:       " $@
	$(Q) $(CXX) $^ -L$(LIB_DIR) $(LIB_ALL) -o $@  


$(OBJ_DIR)/main_CPU.o: main_CPU.cpp CPU.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/CPU.o: CPU.cpp CPU.h settings.h flags.h 
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/errors.o: ../errors/errors.cpp CPU.h errors.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/settings.o: ../settings/settings.cpp CPU.h settings.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/flags.o:	../flags/flags.cpp CPU.h flags.h
	${CXX}  ${CXXFLAGS} $(WARNINGS) $(addprefix -I,$(HDR_DIR)) $< -c -o $@