FLG =
FILE_PREV_FLG = .prev_options.txt

FLG_O = -std=c++14
FLG_D = -MMD

CUR_FLG = $(strip $(FLG_O) $(FLG_D) $(FLG))
PREV_FLG = $(strip $(shell cat $(FILE_PREV_FLG)))

EXEC = prog

SRC_DIR = src
OBJ_DIR = obj
TESTS_SRC_DIR = tests
TESTS_EXEC_DIR = tests/exec

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
OBJ_ALL = $(OBJ_DIR)/main.o $(OBJ)
TESTS_SRC = $(wildcard $(TESTS_SRC_DIR)/*.cpp)
TESTS_EXEC = $(TESTS_SRC:$(TESTS_SRC_DIR)/%.cpp=$(TESTS_EXEC_DIR)/%)




.PHONY: default test clearObj clearTests clearVim clear
###################################################

default: $(EXEC) test 

#build execute file
#ifeq ($(CUR_FLG), $(PREV_FLG))
$(EXEC): $(OBJ_ALL)
	g++ $(OBJ_ALL) -o $(EXEC) 
#else
#$(EXEC): clearObj $(OBJ_ALL)
#	@echo $(CUR_FLG) > $(FILE_PREV_FLG)
#	g++ $(OBJ_ALL) -o $(EXEC) 
#endif

debug:
	make prog -j FLG=-g

#execute tests (and build tests)
test: $(TESTS_EXEC) 
	@echo
	@for currentTest in $^; do\
		$$currentTest;\
	done
	@echo

###################################################


#compile .cpp file
vpath %.cpp $(SRC_DIR)
$(OBJ_ALL): $(OBJ_DIR)/%.o: %.cpp
	g++ -c $(CUR_FLG) $< -o $@ 

#build test file from .cpp
$(TESTS_EXEC): $(TESTS_EXEC_DIR)/%: $(TESTS_SRC_DIR)/%.cpp $(OBJ)
	g++ $(CUR_FLG) $^ -o $@


clearObj: ;-rm $(OBJ_DIR)/*  $(EXEC)
clearTests: ;-rm $(TESTS_EXEC_DIR)/*
clearVim: 
clear: clearObj clearTests clearVim


include $(wildcard $(OBJ_DIR)/*.d)
include $(wildcard $(TEST_EXEC_DIR)/*.d)


