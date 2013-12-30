/*
simple web server

*/
#ifndef SIMPLESERVER_WEB_H
#define SIMPLESERVER_WEB_H
#include "Socket.h"
#include <pthread.h>

namespace simpleserver {

class WebServer {
  public:
    int init(string address, string port, string base_dir) {
      // verify input parameters TODO

      // start the server
      if (server.init(TCP, SERVER, address, port) != 0) {
        LOG(ERROR, "Couldn't start web server");
        return -1;
      }

      // start the processing loop
      pthread_t thread;
      pthread_create(&thread, NULL, &WebServer::pthread_helper, this);
    };
  private:
    Socket server;
  
    static void* thread_helper(void *v) {
      (WebServer*)v->process();
      return NULL;
    }

    int process() {
      Socket connection;
      char buffer[65536];
      char response[65536];

      // loop forever
      for(;;) {
        // wait for a request
        if (connection.init(TCP, CONNECTION, server) != 0)
          continue;

        // read the request
        connection.recv_data(buffer, sizeof(buffer));

        // fulfill the request TODO

        // send a resonse
        connection.send_data(response, sizeof(response));

        // close the connection
        connection.close_socket();
      }
    }
};
}
#endif // #ifndef SIMPLESERVER_WEB_H
