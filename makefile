FLG =
FILE_PREV_FLG = .compilation_options.txt #previous compiler options
FILE_SCIP_COMP = .scip_compilation.txt #

#work in different OS
ifeq ($(OS),Windows_NT)
FILE_READER = type
FILE_ERASER = del
ERASER_OPT = /q
OBJ_TYPE = .lib
EXEC_TYPE = .exe
endif

ifeq ($(OS),UNIX)
FILE_READER = cat
FILE_ERASER = rm
ERASER_OPT = /q
OBJ_TYPE = .o
EXEC_TYPE = 
endif

#standart compiler options
FLG_O = -std=c++14
FLG_D = -MMD
#test execution options
FLG_TEST =

#options in one variable
CUR_FLG = $(strip $(FLG_O) $(FLG_D) $(FLG))
PREV_FLG = $(strip $(shell $(FILE_READER) $(FILE_PREV_FLG)))

#
SCIP_COMP = $(strip $(shell $(FILE_READER) $(FILE_SCIP_COMP)))

#standart folders
EXEC = prog
SRC_DIR = **/src
OBJ_DIR = .obj
TESTS_SRC_DIR = tests
TESTS_EXEC_DIR = tests/exec


SRC = $(filter-out $(SCIP_COMP), $(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(patsubst  %.cpp,$(OBJ_DIR)/%$(OBJ_TYPE),$(notdir $(SRC))) 

TESTS_SRC = $(wildcard $(TESTS_SRC_DIR)/*.cpp)
TESTS_EXEC = $(TESTS_SRC:$(TESTS_SRC_DIR)/%.cpp=$(TESTS_EXEC_DIR)/%$(EXEC_TYPE))


.PHONY: default test clearObj clearTests clearVim clear
###################################################

bld: $(EXEC)$(EXEC_TYPE)
all: release test
deb: debug
del: clear



release: 
ifneq ($(FLG_O) $(FLG_D), $(PREV_FLG))
	make clear
endif
	make $(EXEC)$(EXEC_TYPE) -j 
	make $(TESTS_EXEC)


debug:
ifneq ($(FLG_O) $(FLG_D) -g, $(PREV_FLG))
	make clear
endif
	make $(EXEC)$(EXEC_TYPE) -j FLG=-g
	make $(TESTS_EXEC) FLG=-g

#execute tests (and build tests)
test: $(TESTS_EXEC) 
ifeq ($(OS),Windows_NT)
	@for %%i in ($(subst /,\,$^)) do (%%i $(FLG_TEST))
endif
ifeq ($(OS),UNIX)
	@echo
	@for currentTest in $^; do\
		$$currentTest $(FLG_TEST);\
	done
	@echo
endif

$(EXEC)$(EXEC_TYPE): $(OBJ)
	g++ $(OBJ) main.cpp $(CUR_FLG) -o $(EXEC)$(EXEC_TYPE) 
	@echo $(CUR_FLG) > $(FILE_PREV_FLG)	

start:
	$(EXEC)$(EXEC_TYPE) $(FLG)
	
init:
ifeq ($(OS),Windows_NT)
	-@NUL> $(FILE_PREV_FLG)  
	-@$(shell md $(OBJ_DIR))
endif 
ifeq ($(OS),UNIX)
	-@touch $(FILE_PREV_FLG)
	-@mkdir $(OBJ_DIR)
endif 

###################################################


#build test file from .cpp
$(TESTS_EXEC): $(TESTS_EXEC_DIR)/%$(EXEC_TYPE): $(TESTS_SRC_DIR)/%.cpp $(OBJ)
	g++ $(CUR_FLG) $^ -o $@

#build obj file from .cpp
$(OBJ): 
	g++ $(CUR_FLG) -c $(filter %$(basename $(notdir $@)).cpp, $(SRC)) -o $@
	


clearObj: 
	-@$(FILE_ERASER) $(subst /,\,$(OBJ_DIR)\*) $(ERASER_OPT)
clearTests: 
	-@$(FILE_ERASER) $(EXEC)$(EXEC_TYPE) $(ERASER_OPT)
	-@$(FILE_ERASER) $(subst /,\,$(TESTS_EXEC_DIR)\*) $(ERASER_OPT)
clearVim: 
clear: clearObj clearTests clearVim


include $(wildcard $(TESTS_EXEC_DIR)/*.d)
include $(wildcard $(OBJ_DIR)/*d)
include $(EXEC).d
