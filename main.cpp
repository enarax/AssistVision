#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "vision.h"


const char* robotaddr = "10.28.23.2";
const unsigned short robotport = 12869;

bool r1, r2, r3;


int main(void)
{
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    int rc;
   
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(robotaddr);
    addr.sin_port  = htons(robotport);

    rc = sendto(s, "hello", 5, 0, (struct sockaddr *) &addr, sizeof(addr));

    close(s);

    return rc;
}
