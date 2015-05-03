#include "string.h"
#include <stdio.h>


int server(int argc, char const *argv[]);
int client(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
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