#include "simpleserver_socket.h"
using namespace simpleserver;

#include <assert.h>
#include <stdio.h>

/**
 * test program for the simplesocket interface
 */
int main()
{
  // create two socket objects
  Socket *server = new Socket(TCP, SERVER, "localhost", "24600");
  Socket *client = new Socket(TCP, CLIENT, "localhost", "24600");
  // send a message from the client to the server
  server->send_short(16);
  client->send_short(10);
  // send a message from the server to the client

  // TODO test breaking and reestablishing the connection

  return 0;
}

