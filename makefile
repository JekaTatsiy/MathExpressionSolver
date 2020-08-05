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

.PHONY: clearObj clearTests clear buildTests test

default: $(EXEC) $(TESTS:%.cpp=%) 

exec: $(EXEC)
	clear
	@./$(EXEC)

test: buildTests $(TESTS:%.cpp=%)
	@$(TESTS:%.cpp=%)

###################################################

$(EXEC): $(OBJ)
	g++ $(OBJ) -o $(EXEC) 

$(OBJ_DIR)/%.o: %.cpp
	g++ -c $(FLG_O) $(FLG_D) -o $@ $<

buildTests: $(TESTS:%.cpp=%)
	

$(TEST_DIR)/%: $(TEST_DIR)/%.cpp
	g++ $(FLG_O) $(FLG_D) $^ $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) -o $@


clearObj: ;-rm $(OBJ_DIR)/*  $(EXEC);
clearTests: ;-rm $(TESTS:%.cpp=%) $(TESTS:%.cpp=%.d)
clear: clearObj clearTests


include $(wildcard $(OBJ_DIR)/*.d)
include $(wildcard $(TEST_DIR)/*.d)


