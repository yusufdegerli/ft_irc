CPP = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

NAME = ircserv

SRC = Commands/Nick.cpp Commands/User.cpp Commands/Pass.cpp Commands/Join.cpp Commands/Part.cpp Commands/Kick.cpp \
Commands/Quit.cpp Commands/Who.cpp Commands/List.cpp Commands/Privmsg.cpp Commands/Invite.cpp Channel/Channel.cpp \
Server/checkStatus.cpp Client/Client.cpp main.cpp Server/Message.cpp Server/Server.cpp Server/ServerSetGet.cpp

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
