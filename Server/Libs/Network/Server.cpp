#include "Network/Server.h"


Server::Server(int portno)
{
    _socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero((char*) &_addr, sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = INADDR_ANY;
    _addr.sin_port = htons(portno);
    //Bind socket, throw error if it fails
    if (bind(_socketfd, (struct sockaddr *) &_addr, sizeof(_addr)) < 0) 
        Debug::error("ERROR on binding socket");
    bzero(_buffer, 1000);
    run();
}

Server::~Server()
{
    //Close socket and free resources if any is allocated
    close(_socketfd);
}

void Server::run()
{
    while(true)
    {
        std::cout << "Waiting for request..." << std::endl;
        //Accept client
        socklen_t addlen = sizeof(_client);
        int recvLen = recvfrom(_socketfd, _buffer, 1000, 0, 
                        (struct sockaddr *) &_client, &addlen);

        if(recvLen == -1)
            Debug::error("recvFrom");
        
        std::cout << _buffer << std::endl;
        struct File file;
        std::string cmd(_buffer, recvLen);
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
        std::string filePath;
        if(cmd == "u")
        {
            filePath = "/proc/uptime";
        }
        else if(cmd == "l")
        {
            filePath = "/proc/loadavg";
        }
        if(!file.loadFile(filePath))
        {
            //File doesn't exist
            //Inform client about and close connection
            std::string clistr("Filepath doesn't exist or couldn't be opened\nPlease try again");
            std::cout << "Failed find file client requested at location: " << _buffer << std::endl;
            bzero(_buffer, 1000);
            continue;
        }

        std::string returnString(file._data.begin(), file._data.end());
        std::cout << returnString << std::endl;

        int err = sendto(_socketfd, returnString.data(), returnString.length(), 0, 
                        (struct sockaddr *) &_client, addlen);
        if(err == -1)
            Debug::error("sendto ");
        
        bzero(&_client, sizeof(_client));
        bzero(_buffer, 1000);
    }
}