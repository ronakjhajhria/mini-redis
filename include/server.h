#pragma once
#include <string>
#include "database.h"
#include "parser.h"
#include "resp_parser.h"
#include "resp_encoder.h"
#include <unordered_map>
#include <thread>
#include "client_handler.h"


using namespace std;
class Server
{
public:
    Server();
    void start();

private:
    int server_fd;

    Database database;
    Parser parser;
    RespParser respParser;
    RespEncoder encoder;
    bool bindSocket();
    bool startListening();

    void acceptClients();
    void receiveData();

    void sendResponse(const string& message);

};