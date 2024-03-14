#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Client.h>
#include <Server.h>
#include <Analyzer.h>
using namespace std;

string client_ip = "";
string server_ip = "";
const string ping_ip_file = "ping_result.txt";
const string short_test_results = "short_test_results.txt";
const string long_test_results = "long_test_results.txt";


int main(int argc, char *argv[])
{

    for(int i = 0; i < argc; i++)
    {
        if(!strcmp(argv[i], "-c"))
        {
            client_ip += argv[i+1];
        }
        else if(!strcmp(argv[i], "-s"))
        {
            server_ip += argv[i+1];
        }
        else
        {
            ;
        }
    }    

    if(!strcmp(client_ip.c_str(), ""))
    {
        cout << "ERROR: No client IP provided.  Canceling execution" << endl;
        cout << "To enter ip address, enter: iperf_test -c <ip address>" << endl;
        return 0;
    }
    else
    {
        cout << "Client IP Address: " << client_ip << endl;
    }

    if(!strcmp(server_ip.c_str(), ""))
    {
        cout << "ERROR: No server IP provided.  Canceling execution" << endl;
        cout << "To enter ip address, enter: iperf_test -s <ip address>" << endl;
        return 0;
    }
    else
    {
        cout << "Server IP Address: " << server_ip << endl;
    }

    cout << "Starting main thread execution" << endl;

    cout << "Initializing Results Analyzer" << endl;

    Analyzer analyzer(ping_ip_file, short_test_results, long_test_results);

    cout << "Initializing Client" << endl;

    Client client(client_ip, server_ip, ping_ip_file, short_test_results, long_test_results);
    if(client.test(PING_SERVER))
    {
        if(analyzer.analyze(PING_SERVER))
        {
            cout << "Server Found. Beginning iperf testing" << endl;
        }
        else 
        {
            cout << "Server not found.  Stopping execution" << endl;
            return 0;
        }
    }

    cout << "Starting iperf3 Server" << endl;

    Server server;

    if(client.test(SHORT_IPERF))
    {
        if(analyzer.analyze(SHORT_IPERF))
        {
            cout << "Short test passed.  Bitrate in range" << endl;
            cout << "Continuing to long interval iperf test" << endl;
            cout << "Stopping server" << endl;
        }
        else
        {
            cout << "Bitrate out of range!! Stopping testing" << endl;
            return 0;
        }
    }

    Server server_restart;

    if(client.test(LONG_IPERF))
    {
        if(analyzer.analyze(LONG_IPERF))
        {
            cout << "Long test passed.  Bitrate in rage" << endl;
        }
        else
        {
            cout << "Bitrate out of range!! Stopping testing" << endl;
            return 0;
        }
    }

    return 0;
}