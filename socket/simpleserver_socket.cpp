#include "simpleserver_socket.h"
using namespace simpleserver;

/**
 * Socket constructor.
 * @param _protocol the protocol type to be used by this socket
 * @param _role the fole of this socket
 * @param _address the address for this socket to use.  Note: if a CLIENT,
 *   the address for the SERVER to connect to.
 */
Socket::Socket(PROTOCOL _protocol, ROLE _role, string _address, string _port) {

}

/**
 * Socket destructor.  Calls stop_socket() and frees any internal resources.
 */
Socket::~Socket() {

}

/**
 * Use this socket object to send a given array of bytes.
 *
 * @param data the data array to be sent
 * @param size the size of the data array to be sent
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return number of bytes actually sent on success, -1 on error
 */
int Socket::send_data(void* data, int size, int millisecond_timeout) {
  return 0;
}

/**
 * Use this socket object to send a short.  Note: will convert the short to
 * network order before sending.
 *
 * @param s the short to be sent
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on failure
 */
int Socket::send_short(short s, int millisecond_timeout) {
  return 0;
}

/**
 * Use this socket object to send a long.  Note: will convert the long to
 * network order before sending.
 *
 * @param l the long to be sent
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on failure
 */
int Socket::send_long(long l, int millisecond_timeout) {
  return 0;
}

/**
 * Use this socket object to receive a given array of bytes.
 * 
 * @param data the data array to receive into
 * @param size the maximum number of bytes to be read
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @param return number of bytes actually received on success, -1 on error
 */
int Socket::recv_data(void* data, int size, int millisecond_timeout) {
  return 0;
}

/**
 * Use this socket object to receive a short.  Note: will convert the short to
 * host order after receiving.
 *
 * @param *s place to store the received short
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on failure
 */
int Socket::recv_short(short *s, int millisecond_timeout) {
  return 0;
}

/**
 * Use this socket object to receive a long.  Note: will convert the long to
 * host order after receiving.
 *
 * @param *l place to store the received long
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on failure
 */
int Socket::recv_long(long *l, int millisecond_timeout) {
  return 0;
}

/**
 * Stop this socket object. If this is a server, no new connections will be
 * accepted.  If this is a client, the connection to the server is broken.
 *
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on error
 */
int Socket::stop_socket(int millisecond_timeout) {
  return 0;
}

/**
 * Restart this socket object.  If this is a server, it is reopened to accept
 * new connections.  If this is a client, the connection to the server is
 * reestablished.
 *
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on error
 */
int Socket::restart_socket(int millisecond_timeout) {
  return 0;
}

