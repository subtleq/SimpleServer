#include "simpleserver_socket.h"
using namespace simpleserver;

Socket::Socket() : socket_descriptor(-1) {}

/**
 * Socket constructor.
 * @param _protocol the protocol type to be used by this socket
 * @param _role the fole of this socket
 * @param _address the address for this socket to use.  Note: if a CLIENT,
 *   the address for the SERVER to connect to.
 */
int Socket::init(PROTOCOL _protocol, ROLE _role, string _address, string _port) {
  protocol = _protocol;
  role = _role;
  address = _address;
  port = _port;

  struct addrinfo hints, *servinfo, *p;
  int status;

  LOG(DEBUG, "Creating %s With Address = '%s', Port = '%s'", 
      role == SERVER ? "Server" : "Client", address.c_str(), port.c_str());

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TODO based on PROTOCOL
  hints.ai_flags = AI_PASSIVE; // fill in IP address for me
  
  // getaddrinfo
  if ((status = getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
    LOG(ERROR, "Socket getaddrinfo() Error:");
    fprintf(stderr, "%s\n", gai_strerror(status));
    return -1;
  }

  // loop through all the results and bind to the first we can
  for (p = servinfo; p != NULL; p = p->ai_next) {
    // socket
    if ((socket_descriptor = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      LOG(ERROR, "socket() Error: %s", strerror(errno));
      continue;
    }

    // TODO setsockopt
    int yes = 1;
    if (setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("Socket setsockopt() Error");
      continue;
    }

    // if server, bind
    if (role == SERVER &&
        bind(socket_descriptor, p->ai_addr, p->ai_addrlen) == -1) {
      close(socket_descriptor);
      LOG(ERROR, "bind() Error: %s", strerror(errno));
      continue;
    }

    // if server, listen
    if (role == SERVER && listen(socket_descriptor, SERVER_LISTEN_COUNT) == -1) {
      close(socket_descriptor);
      LOG(ERROR, "listen() Error: %s", strerror(errno));
      continue;
    }

    // if TCP client, connect
    if ((protocol == TCP && role == CLIENT) &&
        connect(socket_descriptor, p->ai_addr, p->ai_addrlen) == -1) {
      close(socket_descriptor);
      LOG(ERROR, "connect() Error: %s", strerror(errno));
      continue;
    }

    break;
  }

  if (p == NULL)
    return -1;

  // freeaddrinfo
  freeaddrinfo(servinfo);

  LOG(DEBUG, "Created Socket With Address: '%s', Port: '%s', Descriptor: %d",
      _address.c_str(), _port.c_str(), socket_descriptor);
  return 0;
}

int Socket::init(PROTOCOL _protocol, ROLE _role, Socket* _server) {
  protocol = _protocol;
  role = _role;
  server = _server;

  // if this is a TCP connection
  if (protocol == TCP && role == CONNECTION) {
    // if the server has a valid socket and is a TCP SERVER
    if (_server->socket_descriptor != -1 &&
        _server->protocol == TCP && _server->role == SERVER)
      socket_descriptor = accept(_server->socket_descriptor, NULL, NULL);
    else {
      LOG(ERROR, "Error Creating Server Connection: Invalid Server");
      return -1;
    }
    if (socket_descriptor == -1) {
      LOG(ERROR, "Error Creating Server Connection: Accept Call Failed: %s",
          strerror(errno));
      return -1;
    }
  } else {
    LOG(ERROR, "Error Creating Server Connection: not a TCP CONNECTION");
    return -1;
  }
    return 0;
}

/**
 * Socket destructor.  Calls stop_socket() and frees any internal resources.
 */
Socket::~Socket() {
  stop_socket();
}

/**
 * Use this socket object to send a given array of bytes.
 *
 * @param data the data array to be sent
 * @param size the size of the data array to be sent
 *
 * @return number of bytes actually sent on success, -1 on error
 */
int Socket::send_data(void* data, int size) {
  // if this socket is not setup correctly or stopped, return error
  if (socket_descriptor == -1)
    return -1;

  int cur = 0, send_cnt = 0;
  // while we send some amount of data and we have not sent everything in the buffer
  do {
    cur = send(socket_descriptor, (void*) (((long long int) data) + send_cnt),
        size - send_cnt, 0);
  } while (cur > 0 && ((send_cnt += cur)  < size));
  return send_cnt;
}

/**
 * Use this socket object to receive a given array of bytes.
 * 
 * @param data the data array to receive into
 * @param size the maximum number of bytes to be read
 *
 * @param return number of bytes actually received on success, -1 on error
 */
int Socket::recv_data(void* data, int size) {
  // if this socket is not setup correctly or stopped, return error
  if (socket_descriptor == -1)
    return -1;

  int cur = 0, recv_cnt = 0;
  // while we receive some amount of data and we have not filled the buffer
  do {
    cur = recv(socket_descriptor, (void*) (((long long int) data) + recv_cnt),
        size - recv_cnt, 0);
  } while (cur > 0 && ((recv_cnt += cur)  < size));
  return recv_cnt;
}

/**
 * Stop this socket object. If this is a server, no new connections will be
 * accepted.  If this is a client, the connection to the server is broken.
 *
 * @return 0 on success, -1 on error
 */
int Socket::stop_socket() {
  if (socket_descriptor == -1)
    return -1;
  close(socket_descriptor);
  return 0;
}

/**
 * Restart this socket object.  If this is a server, it is reopened to accept
 * new connections.  If this is a client, the connection to the server is
 * reestablished.
 *
 * @return 0 on success, -1 on error
 */
int Socket::restart_socket() {
  stop_socket();
  if (role == CONNECTION)
    init(protocol, role, server);
  else
    init(protocol, role, address, port);
  return 0;
}
