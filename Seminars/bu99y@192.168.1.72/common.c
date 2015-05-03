#include "stdio.h"
#include "iv_remote.h"

char const* errors_msgs[] = {
        "",
        "Server error:\n"
        "Too big number: argument must be \"auto\" or in [1..#MAXPROC]\n",
        "Server error:\n"
        "Too small number: argument must be \"auto\" or in [1..#MAXPROC]\n",
        "Server error:\n"
        "Invalid argument: argument must be \"auto\" or in [1..#MAXPROC]\n",
        "Server error:\n"
        "Failed to set up handshaker",
        "Server error:\n"
        "Failed to set socket",
        "Server error:\n"
        "Failed to get socket",
        "Server error:\n"
        "Failed to bind",
        "Server error:\n"
        "Failed to establish handshake thread",
        "Server error:\n"
        "recvfrom() failed",


        "Client error:\n"
        "Failed to get socket",
        "Client error:\n"
        "Failed to set socket",
        "Client error:\n"
        "Failed to send package",
        "Client error:\n"
        "Memory allocation failed\n",
        "Client error:\n"
        "recvfrom() failed",
        "Client error:\n"
        "Memory allocation failed"

};

// int is_error(int errnum)
// {
//         if (FIRST_ERROR <= errnum && errnum <= LAST_ERROR){
//                 return 1;
//         }
//         return 0;
// }

void __print_error(int line, int errnum) 
{
       static char buf[1024];
       if (FIRST_ERROR <= errnum && errnum<= LAST_ERROR){
                sprintf(buf, 
                        "%d: %s\n", 
                        line, 
                        errors_msgs[errnum - FIRST_ERROR]);
                perror(buf);
        } 
}