#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"

int main(int argc, char const *argv[])
{
        int sk = 0;
        cond = socket(PF_INET, SOCK_STREAM, 0);
        if (cond == -1)
                goto fail;
        
        
fail:
        return 0;
}