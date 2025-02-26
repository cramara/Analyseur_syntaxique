# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g
NAME = program
SRC = main.cpp lexer.cpp symbole.cpp state.cpp auto.cpp
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
HEADERS = lexer.h symbole.h state.h auto.h
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# Règles
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-debug: $(NAME)
	$(VALGRIND) --trace-children=yes --track-fds=yes ./$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind valgrind-debug
