NAME        = ircserv
CXX         = c++
CXXFLAGS    = -std=c++98

SRCDIR      = srcs
INCDIR      = includes

SRCS        = $(SRCDIR)/main.cpp \
              $(SRCDIR)/server.cpp \
              $(SRCDIR)/Client.cpp

OBJS        = $(SRCS:.cpp=.o)
INCLUDES    = -I$(INCDIR)

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