/*
improvements:
-enable UDP
-verify all inputs are valid
-look into appropriate socket options
-look into enabling RAW sockets
*/

#ifndef SIMPLESERVER_SOCKET_H
#define SIMPLESERVER_SOCKET_H

#include "simpleserver_log.h"

#include <string>
using std::string;

#include <unistd.h>
#include <errno.h>
#include <netdb.h>

#define SERVER_LISTEN_COUNT 100

/**
 * A simple socket interface to allow easier access to socket communcation
 */
namespace simpleserver
{
/**
 * Protocol type for a Socket object.
 * 
 * TCP - use the TCP protocol
 * UDP - use the UDP protocol
 * 
 * TODO possible future protocols
 * RAW - use a RAW socket
 */
enum PROTOCOL { DEFAULT_PROTOCOL, TCP, UDP };

/**
 * Role of a Socket object.
 * 
 * CLIENT - should run as a client, also used for server connection
 * SERVER - should run as a server
 * CONNECTION - used for established connections on the server
 */
enum ROLE { DEFAULT_ROLE, CLIENT, SERVER, CONNECTION };

/**
 * A Socket object is used to simplify the use of sometype of socket object,
 *  typically used for internet traffic.  This class is in place to make 
 * platform independent socket usage simple.
 */
class Socket
{
public:
  Socket();

  /**
   * Socket constructor.
   * @param _protocol the protocol type to be used by this socket
   * @param _role the fole of this socket
   * @param _address the address for this socket to use.  Note: if a CLIENT,
   *   the address for the SERVER to connect to.
   * @param _server server socket connection to get connection from
   *
   * @return 
   */
  int init(PROTOCOL _protocol, ROLE _role, string _address, string _port);
  int init(PROTOCOL _protocol, ROLE _role, Socket* _server);

  /**
   * Socket destructor.  Calls stop_socket() and frees any internal resources.
   */
  virtual ~Socket();

  /**
   * Use this socket object to send a given array of bytes.
   *
   * @param data the data array to be sent
   * @param size the size of the data array to be sent
   *
   * @return number of bytes actually sent on success, -1 on error
   */
  int send_data(void* data, int size);

  /**
   * Use this socket object to receive a given array of bytes.
   * 
   * @param data the data array to receive into
   * @param size the maximum number of bytes to be read
   *
   * @param return number of bytes actually received on success, -1 on error
   */
  int recv_data(void* data, int size);

  /**
   * Stop this socket object. If this is a server, no new connections will be
   * accepted.  If this is a client, the connection to the server is broken.
   *
   * @return 0 on success, -1 on error
   */
  int stop_socket();

  /**
   * Restart this socket object.  If this is a server, it is reopened to accept
   * new connections.  If this is a client, the connection to the server is
   * reestablished.
   *
   * @return 0 on success, -1 on error
   */
  int restart_socket();
private:
  int socket_descriptor; // file descriptor for this socket object.
  PROTOCOL protocol;
  ROLE role;
  string address;
  string port;
  Socket *server;
};
}
#endif // #ifndef SIMPLESERVVER_SOCKET_H
