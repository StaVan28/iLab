#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for list_project
# version 1.0
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# choose release or debug mode
LAUNCH_MODE = debug

Q = @  
E = $(Q) echo

# path for directories
BIN_DIR  = bin
HEAD_DIR = ../include/headers
LIB_DIR  = ../include/libs
TXT_DIR  = txt

# source
BIN = $(BIN_DIR)/list

SRC = list.cpp main.cpp 
OBJ = list.o   main.o
HDR = list.hpp          list_iterators.hpp

PROJ_LIB = liblist.a

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
	$(E) "  LAUNCH(DBG):" $(BIN)
	$(Q) valgrind $(BIN)

release: clean  $(BIN)
	$(E) "  LAUNCH(RLS):" $(BIN)
	$(Q) $(BIN)
	
#
## linking
$(BIN): $(OBJ)
	$(E) "  LINK:       " $@
	$(Q) $(CXX) $^ -L$(LIB_DIR) $(LIB) -o $@  

$(BIN_TEST): $(OBJ_TEST)
	$(E) "  LINK:       " $@
	$(Q) $(CXX) $^ -L$(LIB_DIR) $(LIB) -o $@ 

#
## compiling
.cpp.o:
	$(E) "  C++         " $@
	$(Q) ${CXX}  ${CXXFLAGS} $(WARNINGS) -I$(HEAD_DIR) -c $*.cpp

.c.o:
	$(E) "  C           " $@
	$(Q) ${CXX} ${CXXFLAGS} $(WARNINGS) -I$(HEAD_DIR) -c $*.c 

main.o:   main.cpp   $(HDR)
list.o:   list.cpp   $(HDR)

#
## additional features
.PHONY: clean tags rebuild git no_valgrind unit_tests library log full_check_valgrind print_logs

clean:
	$(E) "  CLEAN"
	$(Q) rm -f $(BIN) $(TXT_DIR)/log_Makefile tags *.o

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
	$(Q) cat $(TXT_DIR)/dump_list.txt
#
## generate lib and copy main header to ../include
library: $(PROJ_LIB) $(BIN) list.h
	$(E) "  MAKE LIBRARY"
	$(Q) cp list.h $(HEAD_DIR)/
	$(Q) mv $(PROJ_LIB) $(LIB_DIR)/

$(PROJ_LIB): $(OBJ)
	$(Q) ar cr $@ $^
