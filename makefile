EXEC = prog

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(OBJ_DIR)/main.o $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
TESTS = $(wildcard $(TEST_DIR)/*.cpp)

FLG_O = -std=c++14
FLG_D = -MMD

vpath %.cpp $(SRC_DIR)
vpath %.o $(OBJ_DIR)

.PHONY: clearObj clearTests clearVim clear buildTests test

default: $(EXEC) test 

#execute main file
exec: $(EXEC)
	clear
	@./$(EXEC)

#execute tests (and build tests)
test: buildTests 
	@echo
	@for currentTest in $(TESTS:%.cpp=%); do\
		$$currentTest;\
	done
	@echo
###################################################

#build main file
$(EXEC): $(OBJ)
	g++ $(OBJ) -o $(EXEC) 

#compile .cpp file
$(OBJ_DIR)/%.o: %.cpp
	g++ -c $(FLG_O) $(FLG_D) -o $@ $<

#build all tests
buildTests: $(TESTS:%.cpp=%)
	
#build test file from .cpp
$(TEST_DIR)/%: $(TEST_DIR)/%.cpp
	g++ $(FLG_O) $(FLG_D) $^ $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) -o $@


clearObj: ;-rm $(OBJ_DIR)/*  $(EXEC)
clearTests: ;-rm $(TESTS:%.cpp=%) $(TESTS:%.cpp=%.d)
clearVim: 
clear: clearObj clearTests


include $(wildcard $(OBJ_DIR)/*.d)
include $(wildcard $(TEST_DIR)/*.d)


