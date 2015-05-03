#define __USE_MISC

#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "unistd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUFSIZE  1024
#define MAXQUEUE 5
#define PORT     4202



int client(const char*);

int server();


int main(int argc, char const *argv[])
{
        if (argc == 2)
                return client(argv[1]);
        else if (argc == 1)
                return server();
        printf("Wrong number of parameters\n");
        return 0;
}


int client(const char* path)
{
        int fd = 0, sk = 0, cond = 0, got = 0;
        char buf[BUFSIZE] = {};
        struct sockaddr_in server_addr = {
                .sin_family = AF_INET
        };

        server_addr.sin_port = htons(PORT);

        inet_pton(AF_INET, "192.168.1.72", &server_addr.sin_addr);

        fd = open(path, O_RDONLY);
        sk = socket(PF_INET, SOCK_STREAM, 0);
        if (cond == -1)
                goto fail;

        cond = connect(sk, 
                        (struct sockaddr*)&server_addr, 
                        sizeof(struct sockaddr_in));

        if (cond== -1)
                goto fail;

        while ((got = read(fd, buf, BUFSIZE)) > 0) {
                cond = send(sk, buf, got, 0);
                if (cond != got)
                        goto fail;
        }

        if (got == -1)
                goto fail;
close:
        close(fd);
        close(sk);

        return 0;
fail:
        perror("");
        goto close;
}


int server()
{
        int sk = 0, cond = 0, client = 0;
        unsigned size = 0;
        long got = 0;
        char buf[BUFSIZE] = {};
        struct sockaddr_in addr = {
                .sin_family = AF_INET,
        };

        addr.sin_addr.s_addr    = htonl(INADDR_ANY);
        addr.sin_port           = htons(PORT);
        struct sockaddr_in clt_addr = {};

        sk = socket(PF_INET, SOCK_STREAM, 0);
        if (sk == -1)
                goto fail;
        cond = bind(sk, (struct sockaddr*)&addr, sizeof(addr));
        if (cond == -1)
                goto fail;
        cond = listen(sk, MAXQUEUE);
        if (sk == -1)
                goto fail;

        size = sizeof(struct sockaddr_in);
        client = accept(sk, (struct sockaddr*)&clt_addr, &size); // is it OK?
        if (client == -1)
                goto fail;

        while ((got = recv(client, buf, BUFSIZE, 0)) > 0) 
                write(STDOUT_FILENO, buf, got);

        if (got == -1)
                goto fail;       
close:

        close(client);
        close(sk);
        return 0;
fail:
        perror("");
        goto close;
}