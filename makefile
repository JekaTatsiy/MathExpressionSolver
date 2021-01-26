FLG =
FILE_PREV_FLG = .compilation_options.txt

ifeq ($(OS),Windows_NT)
FILE_READER = type
FILE_ERASER = del
ERASER_OPT = /q
OBJ_TYPE = .lib
PROG_TYPE = .exe
endif

ifeq ($(OS),UNIX)
FILE_READER = cat
FILE_ERASER = rm
ERASER_OPT = /q
OBJ_TYPE = .o
PROG_TYPE = 
endif


FLG_O = -std=c++14
FLG_D = -MMD
FLG_TEST = #-V

CUR_FLG = $(strip $(FLG_O) $(FLG_D) $(FLG))
PREV_FLG = $(strip $(shell $(FILE_READER) $(FILE_PREV_FLG)))

EXEC = prog
SRC_DIR = MathExpr/src Matrix/src
OBJ_DIR = obj
TESTS_SRC_DIR = tests
TESTS_EXEC_DIR = tests/exec

vpath %.cpp = MathExpr/src;Matrix/src
vpath %.$(OBJ_TYPE) = $(OBJ_DIR)
SRC = $(wildcard MathExpr/src/*.cpp) Matrix/src/matrix.cpp
ALL_SRC = main.cpp $(SRC) 
NAMES =$(patsubst Matrix/src/%, %, $(patsubst MathExpr/src/%, %, $(SRC)))
OBJ = $(NAMES:%.cpp=$(OBJ_DIR)/%$(OBJ_TYPE)) 
ALL_OBJ = $(OBJ_DIR)/main$(OBJ_TYPE) $(OBJ)

TESTS_SRC = $(wildcard $(TESTS_SRC_DIR)/*.cpp)
TESTS_EXEC = $(TESTS_SRC:$(TESTS_SRC_DIR)/%.cpp=$(TESTS_EXEC_DIR)/%$(PROG_TYPE))


.PHONY: default test clearObj clearTests clearVim clear
###################################################


default: release test 

release: 
ifneq ($(FLG_O) $(FLG_D), $(PREV_FLG))
	make clear
endif
	make $(EXEC) -j 

debug:
ifneq ($(FLG_O) $(FLG_D) -g, $(PREV_FLG))
	make clear
endif
	make $(EXEC) -j FLG=-g

#execute tests (and build tests)
test: $(TESTS_EXEC) 
ifeq ($(OS),Windows_NT)
	@for %%i in ($(subst /,\,$^)) do %%i $(FLG_TEST)
endif
ifeq ($(OS),UNIX)
	@echo
	@for currentTest in $^; do\
		$$currentTest $(FLG_TEST);\
	done
	@echo
endif

$(EXEC): $(ALL_OBJ)
	g++ $(ALL_OBJ) -o $(EXEC)$(PROG_TYPE) 
	@echo $(CUR_FLG) > $(FILE_PREV_FLG)

	
start:
	$(EXEC)$(PROG_TYPE) $(FLG)
	

$(ALL_OBJ): $(OBJ_DIR)/%$(OBJ_TYPE): %.cpp
	g++ -c $(CUR_FLG) $< -o $@ 

###################################################


#build test file from .cpp
$(TESTS_EXEC): $(TESTS_EXEC_DIR)/%$(PROG_TYPE): $(TESTS_SRC_DIR)/%.cpp $(OBJ)
	g++ $(CUR_FLG) $^ -o $@


clearObj: 
	-@$(FILE_ERASER) $(OBJ_DIR)\* $(ERASER_OPT)
	-@$(FILE_ERASER) $(EXEC)$(PROG_TYPE) $(ERASER_OPT)
clearTests: 
	-@$(FILE_ERASER) $(subst /,\,$(TESTS_EXEC_DIR))\* $(ERASER_OPT)
clearVim: 
clear: clearObj clearTests clearVim


include $(wildcard $(TEST_EXEC_DIR)\*.d)

