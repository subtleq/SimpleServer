#include "simpleserver_socket.h"
using namespace simpleserver;

#include <netinet/in.h>

/**
 * Socket constructor.
 * @param _protocol the protocol type to be used by this socket
 * @param _role the fole of this socket
 * @param _address the address for this socket to use.  Note: if a CLIENT,
 *   the address for the SERVER to connect to.
 */
Socket::Socket(PROTOCOL _protocol, ROLE _role, string _address, string _port) :
    socket_descriptor(-1) {

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
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return number of bytes actually sent on success, -1 on error
 */
int Socket::send_data(void* data, int size, int millisecond_timeout) {
  // if this socket is not setup correctly or stopped, return error
  if (socket_descriptor == -1)
    return -1;

  int ans = 0, cur = 0, send_cnt = 0;
  // while we send some amount of data and we have not sent everything in the buffer
  do {
    cur = send(socket_descriptor, (void*) (((long long int) data) + send_cnt), size - send_cnt, 0);
  } while (cur > 0 && ((send_cnt += cur)  < size));
  return send_cnt;
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
  s = htons(s);
  return send_data(&s, sizeof(short), millisecond_timeout);
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
  l = htonl(l);
  return send_data(&l, sizeof(long), millisecond_timeout);
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
  // if this socket is not setup correctly or stopped, return error
  if (socket_descriptor == -1)
    return -1;

  int ans = 0, cur = 0, recv_cnt = 0;
  // while we receive some amount of data and we have not filled the buffer
  do {
    cur = recv(socket_descriptor, (void*) (((long long int) data) + recv_cnt), size - recv_cnt, 0);
  } while (cur > 0 && ((recv_cnt += cur)  < size));
  return recv_cnt;
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
  int ans = recv_data(s, sizeof(short), millisecond_timeout);
  *s = ntohs(*s);
  return ans;
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
  int ans = recv_data(l, sizeof(long), millisecond_timeout);
  *l = ntohl(*l);
  return ans;
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
 * @param millisecond_timeout timeout in milliseconds before we exit the function
 *
 * @return 0 on success, -1 on error
 */
int Socket::restart_socket(int millisecond_timeout) {
  return 0;
}
