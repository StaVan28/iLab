#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for tree_project
# version 1.2
#        author: Starchenko Ivan

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
HDR_DIR  = $(HEAD_DIR) ./settings ./akinator ./akinator_tree 

# source
BIN = $(BIN_DIR)/akinator 

SRC  = settings/akinator_settings.cpp akinator/akinator.cpp akinator_tree/akinator_tree.cpp main.cpp
OBJ  = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC)))
OBJ := $(OBJ:%.cpp=%.o)
DEP  = $(OBJ:%.o=%.d)
LIB  = -ltree

vpath %.cpp $(HDR_DIR)
vpath %.hpp $(HDR_DIR)
vpath %.h   $(HDR_DIR)

PROJ_LIB = libakinator.a

# compiler settings
CXX      = g++ -std=c++14
WARNINGS = -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
		   -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs  \
		   -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow        \
		   -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5          \
		   -Wswitch-default -Wundef -Werror -Wno-unused  -pedantic
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
	$(Q) $(CXX) $(WARNINGS) $^ -L$(LIB_DIR) $(LIB) -o $@  

#
## compiling
$(OBJ_DIR)/%.o: %.cpp
	$(E) "    C++:         " $@
	$(Q) ${CXX}  ${CXXFLAGS} $(addprefix -I,$(HDR_DIR)) $< -c -o $@

$(OBJ_DIR)/main.o:              main.cpp              akinator_settings.hpp akinator.hpp 
$(OBJ_DIR)/akinator.o:          akinator.cpp          akinator_settings.hpp akinator.hpp akinator_tree.hpp
$(OBJ_DIR)/akinator_tree.o:     akinator_tree.cpp     akinator_settings.hpp akinator.hpp akinator_tree.hpp 
$(OBJ_DIR)/akinator_settings.o: akinator_settings.cpp akinator_settings.hpp

#
## additional features
.PHONY: clean tags rebuild git no_valgrind unit_tests library log full_check_valgrind print_logs

install:
	$(E) " INSTALL"
	$(Q) mkdir -p $(OBJ_DIR) $(BIN_DIR) $(TXT_DIR)

clean:
	$(E) "  CLEAN"
	$(Q) rm -f $(BIN) tags $(OBJ_DIR)/*.o $(TXT_DIR)/*.jpeg $(TXT_DIR)/*.dot

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
	$(Q) cat $(TXT_DIR)/dump_akinator.txt
	$(E) "******************************************************"
	$(E) "\t\t\tGraph:\n"
	$(Q) cat $(TXT_DIR)/graph_akinator_db.dot
	$(E) "\n******************************************************"
	$(E) "    LAUNCH JPEG  "
	$(Q) fim $(TXT_DIR)/graph_akinator_db.jpeg
#
## generate lib and copy main header to ../include
library: $(PROJ_LIB) $(BIN) akinator/akinator.hpp
	$(E) "    MAKE LIBRARY"
	$(Q) cp akinator/akinator.hpp $(HEAD_DIR)/
	$(Q) mv $(PROJ_LIB) $(LIB_DIR)/

$(PROJ_LIB): $(OBJ)
	$(Q) ar cr $@ $^


-include $(DEP)