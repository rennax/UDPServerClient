#pragma once
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Debug/Error.h"


struct File
{
    std::vector<char> _data;
    std::vector<char>::iterator _it;
    uint32_t _fileSize;
    

    bool loadFile(std::string filePath)
    {
        //check if path in request exist
        std::ifstream file(filePath, std::ifstream::binary);
        file >> std::noskipws;

        //Copy file into vector
        std::copy(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), std::back_inserter(_data));
        _it = _data.begin();

        //Get file size
        file.seekg(0, file.end);
        _fileSize = file.tellg();
        return _fileSize > 0 ? true : false;
    }
};


class Server
{
public:
    Server(int portno = 9000);
    ~Server();
    void run();
private:
    struct sockaddr_in _addr;
    char _buffer[1000];
    struct sockaddr_in _client;
    int _socketfd;
    int _portno;
};



