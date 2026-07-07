#pragma once
#include "database.h"
#include "resp_parser.h"
#include "resp_encoder.h"
class ClientHandler
{
public:
    ClientHandler(int clientFd, Database& db);

    void handle();

private:
    int client_fd;
    Database& database;
    RespParser respParser;
    RespEncoder encoder;
    void sendResponse(const std::string& message);
};
