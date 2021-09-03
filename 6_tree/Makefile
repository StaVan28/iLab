#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for tree_project
# version 1.2
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# choose release or debug mode
LAUNCH_MODE = debug

Q = @  
E = $(Q) echo

# dirs path
BIN_DIR  = bin
HDR_DIR  = src/settings src/tree
SRC_DIR  = $(HDR_DIR) src/main  
OBJ_DIR  = obj
TXT_DIR  = txt

# source
BIN = $(BIN_DIR)/tree
SRC  = src/settings/settings_tree.cpp src/tree/tree.cpp src/main/main.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
DEP  = $(OBJ:%.o=%.d)
LIB  = libtree.a

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

$(OBJ_DIR)/main.o:          main.cpp          settings_tree.hpp tree.hpp
$(OBJ_DIR)/tree.o:          tree.cpp          settings_tree.hpp tree.hpp
$(OBJ_DIR)/settings_tree.o: settings_tree.cpp settings_tree.hpp

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
	$(E) "  GDB:        " $(BIN)
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
	$(Q) cat $(TXT_DIR)/dump_tree.txt
	$(E) "******************************************************"
	$(E) "\t\t\tGraph:\n"
	$(Q) cat $(TXT_DIR)/graph_tree_db.dot
	$(E) "\n******************************************************"
	$(E) "    LAUNCH JPEG  "
	$(Q) fim $(TXT_DIR)/graph_tree_db.jpeg

-include $(DEP)