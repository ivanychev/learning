#include "airport_header.h"


int socket_snd_rcv_timeout(int sk, int rcv, int snd)
{
    struct timeval rcv_timeout = {
                .tv_sec  = rcv,
                .tv_usec = 0
    };
    struct timeval snd_timeout = {
                .tv_sec  = snd,
                .tv_usec = 0
    };

    if (rcv >= 0 && setsockopt(sk, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout,
                                                    sizeof(rcv_timeout))== -1){
        // print_error(CT_SETSOCK_FAIL);
        return -1;    
    }
    if (snd >= 0 && setsockopt(sk, SOL_SOCKET, SO_SNDTIMEO, &snd_timeout,
                                                    sizeof(snd_timeout))== -1){
        // print_error(CT_SETSOCK_FAIL);
        return -1;   
    }

    return 0;
}

int set_default_timeouts(int sk) {
    return socket_snd_rcv_timeout(sk, RCV_TMOUT_SEC, SND_TMOUT_SEC);
}

int get_socket() 
{
    int sk = 0, is_reuse = 1;

    sk = socket(PF_INET, SOCK_STREAM, 0);
    if (sk == -1) {
        // print_error(CT_GETSOCK_FAIL);
        return -1;
    }

    if (setsockopt(sk, 
                   SOL_SOCKET, 
                   SO_REUSEADDR, 
                   &is_reuse, sizeof(is_reuse)) == -1) {
        // print_error(CT_SETSOCK_FAIL);
        goto fail;
    }

    if (set_default_timeouts(sk) != 0) {
        // print_error(CT_SETSOCK_FAIL);
        goto fail;        
    }

    return sk;
fail:
    close(sk);
    return -1;
}
        
void calc_time(Case* buf, uint32_t* day, uint32_t* hour, uint32_t* min)
{
        if (buf->day > *day) {
                *day  = buf->day;
                *hour = buf->hour;
                *min  = buf->min;
                return; 
        }
        if (buf->hour > *hour ||((buf->hour == *hour)&&(buf->min > *min))) {
                *hour = buf->hour;
                *min  = buf->min;
                return; 
        }
}

void add_mins(uint32_t num, uint32_t* day, uint32_t* hour, uint32_t* min)
{
        uint32_t extra_day = 0;
        uint32_t extra_hour = 0;
        if ((*min + num) >= 60)
                extra_hour = 1;
        *min = (*min + num) % 60;

        if (*hour + extra_hour >= 24)
                extra_day = 1;
        *hour = (*hour + extra_hour) % 24;
        *day += extra_day;
}

int main(int argc, char const *argv[])
{
        int sk_acc = 0, ret = 0;
        struct sockaddr_in rcv_addr;
        char ip[100];
        uint32_t responce = 0;
        Case buf;
        uint32_t day = 0;
        uint32_t hour = 0;
        uint32_t min = 0;

        printf("Type ip address of server\n");
        scanf("%s", ip);

        rcv_addr.sin_family       = AF_INET;
        rcv_addr.sin_port         = htons(PORT);
        ret = inet_pton(AF_INET, ip, &(rcv_addr.sin_addr));
        if (ret != 1) {
                perror("Invalid format of IP adress\n");
                return 0;
        }

        sk_acc = get_socket();
        if (sk_acc == -1) {
                perror("Failed to create accepting socket\n");
                return 0;
        }

        ret = connect(sk_acc ,(struct sockaddr*)&rcv_addr, sizeof(rcv_addr));
        if (ret == -1) {
                perror("Failed to connect\n");
                return 0;
        }

        while (1) {
                ret = recv(sk_acc, &buf, sizeof(buf), 0);
                if (ret == -1) {
                        perror("Failed to get task\n");
                        close(sk_acc);
                        printf("Failed to get task\n");
                        return 0;
                }
                if (buf.index == -1) {
                        printf("Finish packet received\n");
                        break;
                }
                printf("Task %"PRId32": %s plane on day %"PRIu32", time %02"PRIu32":%02"PRIu32"\n",
                                buf.index, 
                                (buf.type == LANDING)?"landing":"taking off",
                                buf.day, 
                                buf.hour, 
                                buf.min);
                calc_time(&buf, &day, &hour, &min);
                printf("Now is day %d, time %02d:%02d\n", day, hour, min);
                add_mins(3, &day, &hour, &min);
                sleep(1);
                printf("Task is completed\n");
                printf("Now is day %d, time %02d:%02d\n", day, hour, min);
                ret = send(sk_acc, &responce, sizeof(responce), 0);
        }

        return 0;
}
