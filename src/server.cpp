#include "server.h"
#include "parser.h"

#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include<sstream>
#include<persistence.h>
using namespace std;

Server::Server()
    : parser(database)
{
}

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
    Persistence::load(database);
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
    while(true)
    {
        acceptClients();
    }

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

void Server::acceptClients()
{
    cout << "waiting for a client...\n";
    while (true)
    {
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd == -1)
            continue;

        std::thread t(
            [this, client_fd]()
            {
                ClientHandler handler(client_fd, database);
                handler.handle();
            });

        t.detach();
    }
}


