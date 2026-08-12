NAME        = ircserv
CXX         = c++
CXXFLAGS    = -std=c++98 -g3

SRCDIR      = srcs
INCDIR      = includes

SRCS        = $(SRCDIR)/main.cpp \
              $(SRCDIR)/server/server.cpp \
              $(SRCDIR)/server/ServerNetwork.cpp \
              $(SRCDIR)/server/ServerParser.cpp \
              $(SRCDIR)/client/Client.cpp \
              $(SRCDIR)/channel/Channel.cpp \
              $(SRCDIR)/command/pass.cpp \
              $(SRCDIR)/command/Nick.cpp \
              $(SRCDIR)/command/User.cpp \
			  $(SRCDIR)/command/Cap.cpp \
              $(SRCDIR)/command/Join.cpp \
              $(SRCDIR)/command/Ping.cpp \
              $(SRCDIR)/command/Mode.cpp \
              $(SRCDIR)/command/Privmsg.cpp \
              $(SRCDIR)/command/Kick.cpp \
              $(SRCDIR)/server/UtilsServer.cpp\
              $(SRCDIR)/command/Invite.cpp\
              $(SRCDIR)/command/Topic.cpp\
              $(SRCDIR)/server/poubelle.cpp
			  
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