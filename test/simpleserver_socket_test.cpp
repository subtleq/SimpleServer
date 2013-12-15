#include "simpleserver_log.h"
#include "simpleserver_socket.h"
using namespace simpleserver;

#include <assert.h>
#include <stdio.h>

/**
 * test program for the simplesocket interface
 */
int main()
{
  Socket *server, *client, *connection;
  // create two socket objects
  LOG(DEBUG, "Creating Server Instance");
  server = new Socket();
  while (server->initialize(TCP, SERVER, "localhost", "24600") != 0);
  bool child = !fork();
  // if the child
  if (child) {
    LOG(DEBUG, "Creating Client Instance");
    client = new Socket();
    while (client->initialize(TCP, CLIENT, "localhost", "24600") != 0);
  } else {
    LOG(DEBUG, "Creating Connection Instance");
    connection = new Socket();
    while (connection->initialize(TCP, CONNECTION, server) != 0);
  }

  // TODO test sending various data types
//  char sent_char = 42, recvd_char = 0;
  short sent_short = 42, recvd_short = 0;
//  int sent_int = 42, recvd_int = 0;

  // send a message from the client to the server
  LOG(DEBUG, "Testing send_short()");
  if (child) {
    client->send_short(sent_short);
    client->recv_short(&recvd_short);
    LOG(DEBUG, "Client Received Short: %d", recvd_short);
  } else {
    connection->recv_short(&recvd_short);
    LOG(DEBUG, "Server Received Short: %d", recvd_short);
    connection->send_short(sent_short);
  }

  // TODO test breaking and reestablishing the connection

  return 0;
}

