#include "iv_remote.h"

int getmyip(struct in_addr* to_save)
{
    int fd;
    struct ifreq ifr;
     
    char iface[] = "eth0";
     
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd == -1)
        return -1;
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
 
    *to_save = ( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr;
    return 0;
}


int main(int argc, char const *argv[])
{
        struct in_addr my = {};
        int ret = getmyip(&my);

        printf("ret = %d, %s\n", ret, inet_ntoa(my));
        return 0;
}
