*This project has been created as part of the 42 curriculum by alehamad, amkhelif.*

# ft_irc

## Description

`ft_irc` is a custom implementation of an **IRC (Internet Relay Chat) server**, written from scratch in **C++98**. The goal of this project is to understand and implement the core mechanics of a real-time, text-based communication protocol: handling multiple simultaneous client connections, parsing raw IRC commands, and managing the state of users and channels.

The server does **not** implement an IRC client, nor server-to-server communication — it is a standalone server designed to be used with an existing reference IRC client (e.g. irssi, WeeChat, or HexChat).

All I/O is handled through a single non-blocking, event-driven loop (using `epoll`), meaning the server can accept and serve many clients at once without forking and without ever blocking on a read or write.

### Features implemented

- Authentication with a server password (`PASS`)
- Nickname and username registration (`NICK`, `USER`)
- Channel joining and leaving (`JOIN`, `PART`)
- Private messages and channel messages (`PRIVMSG`)
- Connection keep-alive (`PING` / `PONG`)
- Client capability negotiation (`CAP`)
- Regular users and channel **operators**
- Operator-only commands:
  - `KICK` — eject a client from a channel
  - `INVITE` — invite a client to a channel
  - `TOPIC` — view or change the channel topic
  - `MODE` — change channel modes (see detail below)
- Aggregation of partial/fragmented TCP packets before parsing a command

### Channel modes (`MODE`)

The following channel modes are supported, following the classic IRC `MODE <channel> <+|-><mode> [param]` syntax:

| Mode | Name | Effect |
|------|------|--------|
| `i` | Invite-only | When set, only users who received an `INVITE` from an operator can `JOIN` the channel. |
| `t` | Topic protection | When set, only channel operators can change the topic with `TOPIC`. When unset, any member can change it. |
| `k` | Channel key | Sets or removes a password required to join the channel (`MODE #chan +k <password>` / `MODE #chan -k`). Clients must supply the key via `JOIN #chan <key>`. |
| `o` | Operator privilege | Grants or revokes operator status for a given user on the channel (`MODE #chan +o <nick>` / `MODE #chan -o <nick>`). Operators can use `KICK`, `INVITE`, `TOPIC` (if `+t`), and `MODE`. |
| `l` | User limit | Sets or removes a maximum number of clients allowed in the channel (`MODE #chan +l <limit>` / `MODE #chan -l`). Once the limit is reached, further `JOIN` attempts are rejected. |

Modes can be combined in a single command (e.g. `MODE #chan +itk secretpass`), and the server replies with the appropriate numeric/notification so all channel members see the change.

### Bonus

Both bonus features have been implemented:

- **File transfer (DCC):** clients can send files to one another through the server. Tested and validated end-to-end between two `irssi` instances.
- **Bot:** an in-server bot that clients can interact with via `PRIVMSG` or dedicated commands.

## Instructions

### Compilation

```bash
make
```

This builds the `ircserv` executable. Available Makefile rules: `all`, `clean`, `fclean`, `re`.

### Execution

```bash
./ircserv <port> <password>
```

- `port`: the TCP port the server listens on for incoming connections
- `password`: the password clients must provide to connect

Example:

```bash
./ircserv 6667 mypassword
```

### Connecting with a client

Connect using any standard IRC client, for example with `irssi`:

```
/connect 127.0.0.1 6667 mypassword
```

Or test raw command handling with `nc`:

```bash
nc -C 127.0.0.1 6667
```

## Resources

- [RFC 1459 — Internet Relay Chat Protocol](https://www.rfc-editor.org/rfc/rfc1459)
- [RFC 2812 — Internet Relay Chat: Client Protocol](https://www.rfc-editor.org/rfc/rfc2812)
- [modern IRC client protocol documentation](https://modern.ircdocs.horse/)
- `man` pages for `poll`/`epoll`, `socket`, `bind`, `listen`, `accept`, `fcntl`

### AI usage

AI was used punctually as a support tool during this project, mainly to:
- Get explanations and clarifications on IRC protocol details (command formats, numeric replies) before implementing them ourselves
- Discuss and validate architectural choices for the epoll-based non-blocking event loop

All AI-assisted suggestions were reviewed, tested, and understood before being integrated, and the core logic and code were written and debugged by us.