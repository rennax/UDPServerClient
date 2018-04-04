#include "Client.h"


Client::Client(int portno, const char *ip)
{
    _socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(_socketfd == -1)
        Debug::error("socket() failed");
    
    bzero((char*) &_srvAddr, sizeof(_srvAddr));
    _srvAddr.sin_family = AF_INET;
    server = gethostbyname(ip);
    if(server == NULL)
    {
       Debug::error("Error, no such host exist");
    }

    bcopy((char *)server->h_addr,
            (char *)&_srvAddr.sin_addr.s_addr,
            server->h_length);
    _srvAddr.sin_port = htons(portno);
    bzero(_buffer, 1000);

}


Client::~Client()
{

}

void Client::run(char* command)
{
    std::string cmd(command);
    std::cout << "\n";

    socklen_t addrlen = sizeof(_srvAddr);
    int err = sendto(_socketfd, cmd.data(), cmd.length(), 0, 
                    (struct sockaddr *) &_srvAddr, addrlen);
    if(err == -1)
        Debug::error("sendto() ");

    int recvLen = recvfrom(_socketfd, _buffer, 1000, 0, 
                    (struct sockaddr *) &_srvAddr, &addrlen);
    if(err == -1)
        Debug::error("recvfrom() ");
    
    std::string rtrnStr(_buffer, recvLen);
    std::cout << rtrnStr << std::endl;
    bzero(_buffer, 1000);
    
}