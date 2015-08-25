#include <stdio.h>
#include <errno.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <unistd.h>

//#include <linux/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/************************************************
 * test ip_transparent
 *https://www.kernel.org/doc/Documentation/networking/tproxy.txt
 */

int main(int argc, char** argv)
{
    int ret = 0;
    int fd;
    int freebind = 1;
    int reuse = 1;
    struct sockaddr_in sockin;
    int cfd;
    struct sockaddr csockaddr;
    socklen_t clen;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("socket error!\n");
        return -errno;
    }
    
    ret = setsockopt(fd, SOL_IP, IP_TRANSPARENT, &freebind, sizeof(freebind));
    if (ret < 0)
    {
        perror("sockopt error!");
        ret = -errno;
        goto lab_close;
    }
    
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret < 0)
    {
        perror("sockopt reuse error!");
        ret = -errno;
        goto lab_close;
    }

    sockin.sin_family = PF_INET;
    sockin.sin_addr.s_addr = inet_addr("1.1.1.2");
    sockin.sin_port = htons(5632);

    ret = bind(fd, (struct sockaddr*)&sockin, sizeof(sockin));
    if (ret < 0)
    {
        perror("bind error!");
        ret = -errno;
        goto lab_close;
    }

    ret = listen(fd, 20);
    if (ret < 0)
    {
        perror("listen error!");
        ret = -errno;
        goto lab_close;
    }
    
    clen = sizeof(struct sockaddr);
    cfd = accept(fd, &csockaddr, &clen);
    if ( cfd < 0 )
    {
        perror("accept error!");
        ret = -errno;
        goto lab_close;
    }

    printf("accept ok!");

lab_close:
    close(fd);
    return ret;
}
