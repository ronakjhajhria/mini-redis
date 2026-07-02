#pragma once

class Server
{
public:
    void start();

private:
    int server_fd;
    int client_fd;

    bool bindSocket();
    bool startListening();

    void acceptClient();

    void receiveData();
};