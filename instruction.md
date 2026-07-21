fonction extern : 
        Everything in C++ 98.
        socket, close, setsockopt, getsockname,
        getprotobyname, gethostbyname, getaddrinfo,
        freeaddrinfo, bind, connect, listen, accept,
        htons, htonl, ntohs, ntohl, inet_addr, inet_ntoa,
        inet_ntop, send, recv, signal, sigaction,
        sigemptyset, sigfillset, sigaddset, sigdelset,
        sigismember, lseek, fstat, fcntl, poll (or
        equivalent)


Argument : 
        port: The listening port
        password: The connection password

        /ircserv <port> <password>

COMMAND :
        KICK - Eject a client from the channel
        INVITE - Invite a client to a channel
        TOPIC - Change or view the channel topic
        MODE - Change the channel’s mode:
        - i: Set/remove Invite-only channel
        - t: Set/remove the restrictions of the TOPIC command to channel operators
        · k: Set/remove the channel key (password)