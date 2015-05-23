#include "string.h"
#include "../include/iv_remote.h"
#include <stdio.h>

/**
 *      @author         Sergey Ivanychev
 *      @mainpage
 *      
 *      @brief          Matrix determinant calculation farm
 *      
 *      @par            Client uses broadcasting to search for servers available
 *                      in the network it is connected. The job consists of few
 *                      steps. 
 *                      
 *                      1. Broadcasting to get server IPs. Let the number be N
 *                      2. N threads are established to communicate with each 
 *                         server. 
 *                      3. Each thread sends matrix to related server.
 *                      4. Package resolving:
 *                      
 *                         - Pipe with tasks. Threads can read and write.
 *                         - Semaphore. 0 when all of threads are finished
 *                         - Thread decreases semaphor by one? if it has 
 *                           finished its task or the connection has failed
 *                        
 */




int server(int argc, char const *argv[]);
int client(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
//        print_error(CT_ALLOC_FAIL);
        
        if (argc == 1) {
                printf( "Matrix determinant remote calculation\n"
                        "\n"
                        "Call structure is:\n "
                        "remored server {num_of_processes|auto}\n"
                        "remoted client {path_to_matrix} {num_of_servers|auto}\n");
                return 0;
        }

        if (strcmp(argv[1], "server") == 0)
                return server(argc, argv);
        if (strcmp(argv[1], "client") == 0)
                return client(argc, argv);

        printf("Invalid first argument. Must be \"server\" or \"client\"\n");
        return 0;
}
