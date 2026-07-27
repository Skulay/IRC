fonction extern : 

        Everything in C++ 98.
        socket : crée un socket pour communiquer sur le réseau.
        close : ferme un descripteur de fichier ou un socket.
        setsockopt : configure les options d'un socket.
        getsockname : récupère l'adresse locale associée à un socket.
        getprotobyname : récupère les informations d'un protocole réseau par son nom.
        gethostbyname : récupère l'adresse IP correspondant à un nom d'hôte.
        getaddrinfo : convertit un nom d'hôte et un service en informations d'adressage réseau.
        freeaddrinfo : libère les informations obtenues avec getaddrinfo.
        bind : associe un socket à une adresse IP et un port.
        connect : établit une connexion avec un serveur distant.
        listen : met un socket en attente de connexions entrantes.
        accept : accepte une connexion entrante et crée un nouveau socket pour le client.
        htons : convertit un entier 16 bits de l'ordre des octets de l'hôte vers le réseau.
        htonl : convertit un entier 32 bits de l'ordre des octets de l'hôte vers le réseau.
        ntohs : convertit un entier 16 bits de l'ordre réseau vers celui de l'hôte.
        ntohl : convertit un entier 32 bits de l'ordre réseau vers celui de l'hôte.
        inet_addr : convertit une adresse IPv4 en notation texte vers un entier réseau.
        inet_ntoa : convertit une adresse IPv4 binaire en chaîne de caractères.
        inet_ntop : convertit une adresse IP binaire en représentation texte.
        send : envoie des données via un socket connecté.
        recv : reçoit des données depuis un socket.
        signal : associe une fonction à la réception d'un signal système.
        sigaction : configure précisément le comportement du programme lors d'un signal.
        sigemptyset : initialise un ensemble de signaux vide.
        sigfillset : remplit un ensemble avec tous les signaux.
        sigaddset : ajoute un signal à un ensemble.
        sigdelset : retire un signal d'un ensemble.
        sigismember : vérifie si un signal appartient à un ensemble.
        lseek : déplace la position de lecture/écriture dans un fichier.
        fstat : récupère les informations concernant un fichier ou un descripteur.
        fcntl : manipule les propriétés d'un descripteur de fichier.
        poll : surveille plusieurs descripteurs pour détecter des événements d'entrée/sortie.


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

Architecture du dossier :

        irc/
        ├── Makefile
        ├── README.md
        │
        ├── include/
        │   ├── commands/
        │   │
        │   └── utils/
        │
        ├── src/
        │   ├── server/
        │   │
        │   ├── client/
        │   │
        │   ├── channel/
        │   │
        │   ├── message/
        │   │
        │   ├── commands/
        │   │
        │   └── utils/
        │
        └── tests/