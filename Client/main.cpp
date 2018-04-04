#include "Network/Client.h"


int main(int argc, char *argv[])
{
    if(argc > 2)
    {
        Client client(9000, argv[1]);
        client.run(argv[2]);
    }
        

    
     return 0; 
}