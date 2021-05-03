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

# path for directories
HEAD_DIR = ../include/headers
LIB_DIR  = ../include/libs

BIN_DIR  = bin
OBJ_DIR  = obj
TXT_DIR  = txt
HDR_DIR  = $(HEAD_DIR) ./settings ./tree 

# source
BIN = $(BIN_DIR)/tree

SRC  = settings/settings_tree.cpp tree/tree.cpp main.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
DEP  = $(OBJ:%.o=%.d)

vpath %.cpp $(HDR_DIR)
vpath %.hpp ./settings ./tree
vpath %.h   $(HDR_DIR)

PROJ_LIB = libtree.a

# compiler settings
CXX      = g++ -std=c++14
WARNINGS = -Wall -Wextra 
CXXFLAGS = 

DEBUG_MODE   = -g3 -O0 	
RELEASE_MODE = -g0 -Ofast

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all -v

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

.PHONY: debug release default

#
## launch with debug valgrind(default)
default: print_logs

print_logs: $(LAUNCH_MODE)

debug: $(BIN) 
	$(E) "    LAUNCH(DBG): " $(BIN)
	$(Q) valgrind $(BIN)

release: clean  $(BIN)
	$(E) "    LAUNCH_MODENCH(RLS): " $(BIN)
	$(Q) $(BIN)

#
## linking
$(BIN): $(OBJ)
	$(E) "    LINK:        " $@
	$(Q) $(CXX) $(WARNINGS) $^ -L$(LIB_DIR) -o $@  

#
## compiling
$(OBJ_DIR)/%.o: %.cpp
	$(E) "    C++:         " $@
	$(Q) ${CXX}  ${CXXFLAGS} $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/main.o:		main.cpp     settings_tree.h tree.hpp
$(OBJ_DIR)/tree.o:		tree.cpp     settings_tree.h tree.hpp
$(OBJ_DIR)/settings.o:	settings.cpp settings_tree.h

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

unit_tests: $(BIN_TEST)
	$(E) "  UNIT_TESTS:" $(BIN)
	$(Q) $(BIN_TEST)

git:
	$(E) "  AUTO COMMIT  "
	$(Q) git add --all
	$(Q) git commit -m "auto commit: 4_CPU"

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
#
## generate lib and copy main header to ../include
library: $(PROJ_LIB) $(BIN) tree/tree.hpp settings_tree.h
	$(E) "    MAKE LIBRARY"
	$(Q) cp tree/tree.hpp            $(HEAD_DIR)/
	$(Q) cp settings/settings_tree.h $(HEAD_DIR)/
	$(Q) mv $(PROJ_LIB) $(LIB_DIR)/

$(PROJ_LIB): $(OBJ)
	$(Q) ar cr $@ $^


-include $(DEP)