#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for akinator_project
# version 1.0
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# choose release or debug mode
LAUNCH_MODE = debug

Q = @  
E = $(Q) echo

# dirs path
BIN_DIR  = Bin
HDR_DIR  = Src/Settings Src/Tree Src/Akinator Src/Parsing_text
SRC_DIR  = $(HDR_DIR) Src/Main
OBJ_DIR  = Obj
TXT_DIR  = Txt

# source
BIN = $(BIN_DIR)/akinator
SRC  = Src/Settings/settings.cpp Src/Tree/tree.cpp Src/Akinator/akinator.cpp \
       Src/Main/main.cpp Src/Parsing_text/parsing_text.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
DEP  = $(OBJ:%.o=%.d)
LIB  = libakinator.a

# find a *.hpp files 
vpath %.cpp $(SRC_DIR)
vpath %.hpp $(HDR_DIR)

# compiler settings
CXX      = g++ -std=c++14
WARNINGS = -Wall -Wextra 
CXXFLAGS = 

DEBUG_MODE   = -g3 -O0
RELEASE_MODE = -g0 -O2

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all -v

ifeq ($(LAUNCH_MODE),debug)
	CXXFLAGS += $(DEBUG_MODE)
else
	CXXFLAGS += $(RELEASE_MODE)
endif

#--------------------------------------------------------------------------------------
# RULES
#--------------------------------------------------------------------------------------

.PHONY: debug release default

#
## launch with debug valgrind(default)
default: print_logs

print_logs: $(LAUNCH_MODE)

debug: $(BIN) 
	$(E) "    LAUNCH(DBG): " $(BIN)
	$(Q) valgrind $(BIN)

release: clean  $(BIN)
	$(E) "    LAUNCH_MODE(RLS): " $(BIN)
	$(Q) $(BIN)

#
## linking
$(BIN): $(OBJ)
	$(E) "    LINK:        " $@
	$(Q) $(CXX) $(WARNINGS) $^ -o $@  

#
## compiling
$(OBJ_DIR)/%.o: %.cpp
	$(E) "    C++:         " $@
	$(Q) ${CXX} -c ${CXXFLAGS} $(addprefix -I,$(HDR_DIR)) $< -o $@

$(OBJ_DIR)/main.o:          main.cpp                            settings.hpp
$(OBJ_DIR)/akinator.o:      akinator.cpp      akinator.hpp      settings.hpp 
$(OBJ_DIR)/tree.o:          tree.cpp          tree.hpp          settings.hpp parsing_text.hpp
$(OBJ_DIR)/parsing_text.o:  parsing_text.cpp  parsing_text.hpp  settings.hpp 
$(OBJ_DIR)/settings.o:      settings.cpp                        settings.hpp

#
## additional features
.PHONY: clean tags rebuild git no_valgrind unit_tests library log full_check_valgrind print_logs

install:
	$(E) " INSTALL"
	$(Q) mkdir -p $(OBJ_DIR) $(BIN_DIR)

clean:
	$(E) "  CLEAN"
	$(Q) rm -f $(BIN)  tags $(OBJ_DIR)/*.o

tags: ${SRC}
	$(Q) rm -f tags
	$(Q) ctags -R -f .tags

gdb: $(BIN)
	$(E) "    GDB:        " $(BIN)
	$(Q) gdb $(BIN) 

rebuild: clean default

no_valgrind: $(BIN)
	$(E) "  LAUNCH STD: " $(BIN)
	$(Q) $(BIN)

full_check_valgrind: $(BIN)
	$(E) "  LAUNCH FULL:" $(BIN)
	$(Q) valgrind  $(VALGRIND_FLAGS) $(BIN)

log:
	$(Q) git log --oneline --all --graph

print_logs:
	$(E) "    PRINT LOGS  "

-include $(DEP)