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
  Socket *connection = new Socket(TCP, CONNECTION, server);

  // TODO test sending various data types
  char sent_char, recvd_char;
  short sent_short, recvd_short;
  int sent_int, recvd_int;

  // send a message from the client to the server
  client->send_short(10);
  short ans;
  
  connection->recv_short(&ans);
  
  // send a message from the server to the client
  server->send_short(16);

  // TODO test breaking and reestablishing the connection

  return 0;
}

