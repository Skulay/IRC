NAME		= ircserv

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

SRCDIR		= src
INCDIR		= includes

SRCS		= $(SRCDIR)/main.cpp \
			  $(SRCDIR)/Client.cpp \
			  $(SRCDIR)/Server.cpp \
			  $(SRCDIR)/Channel.cpp

OBJS		= $(SRCS:.cpp=.o)

INCLUDES	= -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re