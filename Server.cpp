#include <Server.h>

Server::Server()
{
    this->server_thread = thread(&Server::start_server, this);
}

void Server::start_server()
{
    system((this->iperf_server_cmd).c_str());
}

void Server::stop_server()
{
    this->server_thread.join();
    this->server_thread.~thread();
}

Server::~Server()
{
    this->server_thread.join();
    this->server_thread.~thread();
}