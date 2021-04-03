#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for CPU_project
# version 1.5
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
BIN      = $(BIN_DIR)/CPU
BIN_TEST = $(BIN_DIR)/unit_tests

SRC_ALL = CPU.cpp assembler.cpp errors.cpp labels.cpp settings.cpp flags.cpp
OBJ_ALL = CPU.o   assembler.o   errors.o   labels.o   settings.o   flags.o
HDR_ALL = CPU.h   assembler.h   errors.h   labels.h   settings.h   flags.h   $(HEAD_DIR)/stack.h $(HEAD_DIR)/txtlib.h

SRC = $(SRC_ALL) main.cpp
OBJ = $(OBJ_ALL) main.o
HDR = $(HDR_ALL)
LIB = -lstack -ltxtlib

SRC_TEST = $(SRC_ALL) unit_tests.cpp main_tests.cpp
OBJ_TEST = $(OBJ_ALL) unit_tests.o   main_tests.o
HDR_TEST = $(HDR_ALL) unit_tests.h

PROJ_LIB = libCPU.a

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

main.o:          main.cpp       $(HDR)
CPU.o:           CPU.cpp        $(HDR)
assembler.o:     assembler.cpp  $(HDR)  
errors.o:        errors.cpp     $(HDR) 
labels.o:        labels.cpp     $(HDR)
unit_tests.o:    unit_tests.cpp $(HDR) 
settings.o:      settings.cpp   $(HDR)
flags.o:	     flags.cpp      $(HDR)

#
## additional features
.PHONY: clean errors tags rebuild git no_valgrind unit_tests library log full_check_valgrind print_logs

clean:
	$(E) "  CLEAN"
	$(Q) rm -f $(BIN) $(TXT_DIR)/log_Makefile tags *.o

errors:
	$(Q) rm -f makeout
	$(Q) make $(BIN) > $(TXT_DIR)/log_Makefile

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
	$(Q) cat $(TXT_DIR)/dump_CPU.txt
	$(Q) cat $(TXT_DIR)/dump_stack.txt
	$(Q) cat $(TXT_DIR)/dump_labels.txt
	$(Q) cat $(TXT_DIR)/dump_text.txt

#
## generate lib and copy main header to ../include
library: $(PROJ_LIB) $(BIN) CPU.h
	$(E) "  MAKE LIBRARY"
	$(Q) cp CPU.h $(HEAD_DIR)/
	$(Q) mv $(PROJ_LIB) $(LIB_DIR)/

$(PROJ_LIB): $(OBJ)
	$(Q) ar cr $@ $^