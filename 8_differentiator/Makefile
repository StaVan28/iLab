#--------------------------------------------------------------------------------------
# ANNOTATION
#--------------------------------------------------------------------------------------

# Makefile for differenciator_project
# version 1.0
#		author: Starchenko Ivan

#--------------------------------------------------------------------------------------
# SETTINGS
#--------------------------------------------------------------------------------------

# choose release or debug mode
LAUNCH_MODE = debug

Q = @  
E = $(Q) echo

# include source
-include Makefile_src

# find a *.hpp files 
vpath %.cpp $(SRC_DIR)
vpath %.hpp $(HDR_DIR)
vpath %.h   $(HDR_DIR)

# compiler settings
CXX      = g++ -std=c++11
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
default: $(BIN)

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

$(OBJ_DIR)/%.o: %.hpp
	$(E) "    C++:         " $@
	$(Q) ${CXX} -c ${CXXFLAGS} $(addprefix -I,$(HDR_DIR)) $< -o $@

#include dependens for rules
-include Makefile_deps

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

-include $(DEP)