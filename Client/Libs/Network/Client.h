#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Debug/Error.h"

class Client
{
public:
    Client(int portno = 9000, const char *ip = "localhost");
    ~Client();
    void run(char * command);
private:
    char _buffer[1000];
    struct sockaddr_in _srvAddr;
    struct hostent *server;
    int _socketfd;
};