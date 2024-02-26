CPP = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = ircserv

SRC = main.cpp Server.cpp Client.cpp Command.cpp Message.cpp Commands/Nick.cpp Commands/User.cpp Commands/Pass.cpp checkStatus.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CPP) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CPP) $(FLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME) $(OBJ)
re: clean all

.PHONY: clean all re
