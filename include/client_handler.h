#pragma once

#include "database.h"

class ClientHandler
{
public:
    ClientHandler(int clientFd, Database& db);

    void handle();

private:
    int client_fd;
    Database& database;
};
