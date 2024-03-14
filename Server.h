#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
using namespace std;

class Server {
    private:
        thread server_thread;
        const string iperf_server_cmd = "iperf3 -s -1";
    public:
        Server();
        void start_server();
        void stop_server();
        ~Server();
};

#endif