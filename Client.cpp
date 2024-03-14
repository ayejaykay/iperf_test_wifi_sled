#include <Client.h>

Client::Client(string client_ip, string server_ip, string ping_test_file, string short_test_file, string long_test_file)
{
    this->client_ip = client_ip;
    this->server_ip = server_ip;
    this->ping_results_file = ping_test_file;
    this->short_test_results_file = short_test_file;
    this->long_test_results_file = long_test_file;
}

string Client::build_iperf_command(int OP_CODE)
{
    switch(OP_CODE){
        case PING_SERVER:
            return 
            this->ssh_header + 
            this->client_ip + " " + 
            this->dbl_qt_delim + 
            "ping -c 2 " + 
            this->server_ip + 
            this->dbl_qt_delim + 
            " > " + 
            this->ping_results_file;
        case SHORT_IPERF:
            return 
            this->ssh_header + 
            this->client_ip + " " + 
            this->dbl_qt_delim + 
            this->iperf_command + 
            this->server_ip +
            this->dbl_qt_delim + 
            " > " +
            this->short_test_results_file;
        case LONG_IPERF:
            return 
            this->ssh_header + 
            this->client_ip + " " + 
            this->dbl_qt_delim + 
            this->iperf_command + 
            this->server_ip +
            " " +
            this->long_suffix + 
            this->dbl_qt_delim + 
            " > " +
            this->long_test_results_file;
        default:
            return "INVALID";
    } 
}

// Should make this into an int function that can return system() err codes if not 0
bool Client::test(int OP_CODE)
{
    if(!system(this->build_iperf_command(OP_CODE).c_str()))
    {
        return true;
    }
    return false;
}