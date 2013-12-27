#include "simpleserver_log.h"
#include "simpleserver_socket.h"
using namespace simpleserver;

#include <pthread.h>

/**
 * class to mimic a server connection
 */
class Server
{
public:
  Server(string _address, string _port) : server(), connection(), address(_address), port(_port)
  {
    // start the thread helper
    pthread_t thread;
    pthread_create(&thread, NULL, &Server::pthread_helper, this);
  }

  int send(void* data, int size)
  {
    LOG(DEBUG, "sending data of size %d on server", size);
    while(connection.send_data(data, size) != size)
      sleep(1);
    LOG(DEBUG, "server data sent");
    return 0;
  }

private:
  Socket server;
  Socket connection;
  string address;
  string port;

  static void* pthread_helper(void* v)
  {
    Server *s = ((Server*) v);
    // start the server
    while ((s->server.initialize(TCP, SERVER, s->address, s->port)))
      sleep(1);

    // connect to the client
    while (s->connection.initialize(TCP, CONNECTION, &s->server))
      sleep(1);

    // start the receive loop
    s->recv_loop();

    return NULL;
  }

  void recv_loop()
  {
    int data = 0;
    LOG(DEBUG, "Started server recv loop");
    while(1)
    {
      // attempt to receive an int of data
      if (connection.recv_data(&data, sizeof(data)) == sizeof(data))
        LOG(DEBUG, "server received: %d", data);
    }
  }

  void reconnect() {}
};

/**
 * class to mimic a client connection
 */
class Client
{
public:
  Client(string _address, string _port) : client(), address(_address), port(_port)
  {
    // start the thread helper
    pthread_t thread;
    pthread_create(&thread, NULL, &Client::pthread_helper, this);
  }

  int send(void* data, int size)
  {
    LOG(DEBUG, "sending data of size %d on client", size);
    while(client.send_data(data, size) != size)
      sleep(1);
    LOG(DEBUG, "client data sent");
    return 0;
  }

private:
  Socket client;
  string address;
  string port;

  static void* pthread_helper(void* v)
  {
    Client *c = (Client*) v;
    // start the client
    while (c->client.initialize(TCP, CLIENT, c->address, c->port) != 0)
      sleep(1);

    // start the receive loop
    c->recv_loop();

    return NULL;
  }

  void recv_loop()
  {
    int data = 0;
    LOG(DEBUG, "Started server recv loop");
    while(1)
    {
      // attempt to receive an int of data
      if (client.recv_data(&data, sizeof(data)) == sizeof(data))
        LOG(DEBUG, "client received: %d", data);
    }

    LOG(DEBUG, "stopped client recv loop");
  }

  void reconnect() {}
};

int main()
{
  LOG(DEBUG, "Testing Socket Library");
  // test socket library implementation
  LOG(DEBUG, "Creating TCP Server");
  Server *server = new Server("localhost", "24601");
  LOG(DEBUG, "Creating TCP Client");
  Client *client = new Client("localhost", "24601");
  sleep(5);

  int data = 42;
  client->send(&data, sizeof(data));
//  client->recv(&client_data, sizeof(client_data));
  server->send(&data, sizeof(data));
//  server->recv(&server_data, sizeof(server_data));
  sleep(5);

  return 0;
}
