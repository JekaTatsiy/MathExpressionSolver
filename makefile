EXEC = prog
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(OBJ_DIR)/main.o $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) 
DEP = $($(OBJ):%.o=%.d)
FLG_O = 
FLG_D = -MMD

vpath %.cpp $(SRC_DIR)
vpath %.o $(OBJ_DIR)

.PHONY: default clear

default: $(EXEC)

exec: $(EXEC)
	clear
	@echo start executing $(EXEC)
	@./$(EXEC)
	@echo end executing $(EXEC)

prog: $(OBJ)
	g++ $(OBJ) -o $(EXEC) 

obj/%.o: %.cpp
	g++ -c $(FLG_O) $(FLG_D) -o $@ $<

clear:
	rm  $(OBJ_DIR)/*

include $(DEP)
