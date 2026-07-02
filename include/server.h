#pragma once
#include <string>
#include "parser.h"
class Server
{
public:
    void start();

private:
    int server_fd;
    int client_fd;

    Parser parser;
    bool bindSocket();
    bool startListening();

    void acceptClient();
    void receiveData();

    void sendResponse(const std::string& message);

};