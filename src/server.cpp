#include "server.h"

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <cstring>

#include <iostream>
using namespace std;
void Server::start()
{
    cout << "creating server socket\n";

    server_fd = socket(AF_INET , SOCK_STREAM , 0);

    if(server_fd == -1)
    {
        cerr << "failed to create socket \n";
        return ;
    }

    cout << "socket created successfully\n";

    if(!bindSocket())
    {
        close(server_fd);
        return;
    }

    if(!startListening())
    {
        close(server_fd);
        return ;
    }

    acceptClient();

    close(server_fd);
}

bool Server::bindSocket()
{
    sockaddr_in server_address{};

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(6379);

    if(bind(server_fd,reinterpret_cast<sockaddr*>(&server_address),sizeof(server_address)) == -1)
    {
        cerr << "failed to bind socket\n";
        return false;
    }
    cout << "socket bound to port 6379\n";
    return true;
}

bool Server::startListening()
{
    if(listen(server_fd, 5) == -1)
    {
        cerr << "failed to listen on socket \n";
        return false;
    }

    cout << "server is listening on port 6379 \n";
    return true;
}

void Server::acceptClient()
{
    cout << "waiting for a client...\n";

    client_fd = accept(server_fd , nullptr, nullptr);

    if(client_fd == -1)
    {
        cerr << "failed to accept client\n";
        return ;
    }

    cout << "client connected!\n";

    receiveData();
    
    close(client_fd);
}

void Server::receiveData()
{
    char buffer[1024] = {0};

    int bytes_received = recv(client_fd, buffer , sizeof(buffer) -1 , 0);

    if(bytes_received == -1)
    {
        cerr << "failed to receive data\n";
        return;
    }

    cout << "received " << bytes_received << "bytes\n";
    cout << "message: " << buffer << '\n';
}