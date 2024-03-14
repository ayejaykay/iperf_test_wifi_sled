#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

enum {
    PING_SERVER,
    SHORT_IPERF,
    LONG_IPERF,
};

class Client {
    private:
        string client_ip;
        string server_ip;
        string ping_results_file;
        string short_test_results_file;
        string long_test_results_file;
        const string ssh_header = "ssh root@";
        const string iperf_command = "iperf3 -u -b 100M -c ";
        const string long_suffix = "-t 300";
        const string dbl_qt_delim = "\"";
    public:
        Client(string client, string server, string ping_test, string short_test, string long_test);
        string build_iperf_command(int OP_CODE);
        bool test(int OP_CODE);
};

#endif