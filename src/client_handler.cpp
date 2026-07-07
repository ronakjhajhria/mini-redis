#include "client_handler.h"
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include "persistence.h"
ClientHandler::ClientHandler(int clientFd, Database& db)
    : client_fd(clientFd), database(db)
{
}

void ClientHandler::handle()
{
    while(true)
    {
        
        char buffer[1024] = {0};
    
        int bytes_received = recv(client_fd, buffer , sizeof(buffer) -1 , 0);
    
        if(bytes_received == -1)
        {
            cerr << "failed to receive data\n";
            return;
        }
    
        cout << "received " << bytes_received << "bytes\n";
        string command(buffer);
        vector<string> tokens = respParser.parse(command);

        if(tokens.empty())
            return;

        string cmd = tokens[0];

        if(cmd == "PING")
        {
           sendResponse(encoder.simpleString("PONG"));
        }
        else if(cmd == "SET")
        {
            string key, value;
            key = tokens[1];
            value = tokens[2];
            database.set(key, value);
            Persistence::save(database);
            sendResponse(encoder.simpleString("OK"));
    
        }
        else if(cmd == "GET")
        {
            string key;
            key = tokens[1];

            auto value = database.get(key);

            sendResponse(encoder.bulkString(value));
        }
        else if(cmd == "DEL")
        {
            string key;
            key = tokens[1];

            bool deleted = database.del(key);

            if(deleted)
                sendResponse(encoder.integer(1));
            else
                sendResponse(encoder.integer(0));
        }
        else if(cmd == "EXISTS")
        {
            string key;
            key = tokens[1];
            if(database.exists(key))
                sendResponse(encoder.integer(1));
            else
                sendResponse(encoder.integer(0));
        }
        else if(cmd == "KEYS")
        {
            sendResponse(encoder.bulkString(database.keys()));
        }
        else if(cmd == "FLUSHALL")
        {
            database.flushAll();
            sendResponse(encoder.simpleString("OK"));
        }
        else if(cmd == "SIZE")
        {
            sendResponse(encoder.bulkString(to_string(database.size())));
        }
        else   
        {
           sendResponse(encoder.error("Unknown command"));
        }
        while(!command.empty() && (command.back() == '\r' || command.back() == '\n'))
        {
            command.pop_back();
        }
    }
}

void ClientHandler::sendResponse(const std::string& message)
{
    send(client_fd, message.c_str(), message.size(), 0);
}