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

export Q = @  
export E = $(Q)echo

# bins
BIN_ASM = ./bin/assembler
BIN_CPU = ./bin/CPU

# path for recursive directories
export HEAD_DIR = ../../include/headers
export LIB_DIR  = ../../include/libs

export BIN_DIR  = ../bin
export OBJ_DIR  = ../obj
export TXT_DIR  = ../txt
export HDR_DIR  = $(HEAD_DIR) ../CPU ../assembler ../errors ../labels ../settings ../flags 

# modules
MODULES  = CPU assembler errors labels settings flags 
PROJECTS = CPU assembler

# compiler settings
export CXX      = g++ -std=c++14 
export WARNINGS = -Wall -Wextra 
export CXXFLAGS = -MMD

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

.PHONY: $(PROJECTS) default print_logs CPU_launch assembler_launch

#
## launch with debug valgrind(default)
default: print_logs 

print_logs: $(LAUNCH_MODE)

debug: $(PROJECTS) 
	$(E) "    LAUNCH(DBG):" $(BIN_ASM)
	$(E) "    LAUNCH(DBG):" $(BIN_CPU)
	$(Q) valgrind $(BIN_ASM)
	$(Q) valgrind $(BIN_CPU)

release: clean $(PROJECTS)  
	$(E) "    LAUNCH(RLS):" $(BIN_ASM)
	$(E) "    LAUNCH(RLS):" $(BIN_CPU)
	$(Q) $(BIN_ASM)
	$(Q) $(BIN_CPU)

CPU:
	$(E) "    MAKE RECUR(compile):" $(BIN_CPU)
	$(Q) $(MAKE) -C $@

CPU_launch: CPU
	$(E) "    LAUNCH(ONLY):" $(BIN_CPU)
	$(Q) valgrind $(BIN_CPU)

assembler:
	$(E) "    MAKE RECUR(compile):" $(BIN_ASM)
	$(Q) $(MAKE) -C $@	

assembler_launch: assembler
	$(E) "    LAUNCH(ONLY):" $(BIN_ASM)
	$(Q) valgrind $(BIN_ASM)

#
## additional features
.PHONY: clean errors tags rebuild git no_valgrind unit_tests log full_check_valgrind print_logs

clean:
	$(E) "    CLEAN"
	$(Q) rm -f $(BIN_ASM) $(BIN_CPU)  tags ./obj/*.o

tags: ${SRC}
	$(Q) rm -f tags
	$(Q) ctags -R -f .tags

gdb_asm: $(BIN_ASM)
	$(E) "    GDB:        " $(BIN_ASM)
	$(Q) gdb $(BIN_ASM) 

gdb_cpu: $(BIN_CPU)
	$(E) "    GDB:        " $(BIN_CPU)
	$(Q) gdb $(BIN_CPU)

rebuild: clean default

git:
	$(E) "    AUTO COMMIT  "
	$(Q) git add --all
	$(Q) git commit -m "auto commit: 4_CPU"

log:
	$(Q) git log --oneline --all --graph

print_logs:
	$(Q) cat .txt/dump_CPU.txt
	$(Q) cat .txt/dump_stack.txt
	$(Q) cat .txt/dump_labels.txt
	$(Q) cat .txt/dump_text.txt
