#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>


#include "NetworkAnimation.hpp"

NetworkAnimation::NetworkAnimation(){
    sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in my_sock_addr;
    memset(&my_sock_addr, 0, sizeof(my_sock_addr));
    my_sock_addr.sin_family = AF_INET;
    my_sock_addr.sin_addr.s_addr = INADDR_ANY;
    my_sock_addr.sin_port = htons(2048);

    if (bind(sock, (struct sockaddr *) &my_sock_addr, sizeof(my_sock_addr))){
        perror("bind :");
        return -1;
    }

}
