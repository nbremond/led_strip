#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>


#include "NetworkAnimation.hpp"

NetworkAnimation::NetworkAnimation() :
    Animation(true,0,mainThread)
{
}

void NetworkAnimation::mainThread(Animation* parentAnim){
    assert(parentAnim != NULL);
    NetworkAnimation& a = *(NetworkAnimation*)parentAnim;
    a.sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in my_sock_addr;
    memset(&my_sock_addr, 0, sizeof(my_sock_addr));
    my_sock_addr.sin_family = AF_INET;
    my_sock_addr.sin_addr.s_addr = INADDR_ANY;
    my_sock_addr.sin_port = htons(2048);

    for (int i = 0; i < 10; i++){
    if (bind(a.sock, (struct sockaddr *) &my_sock_addr, sizeof(my_sock_addr))){
        perror("bind :");
    }else
        break;
        std::cout<<("error during bind, trying again");
        sleep(i*5);
    }
    if (listen(a.sock,10)){
        perror("listen :");
    }
    int client_fd = -1;
    struct sockaddr_in client_addr;
    socklen_t client_addr_size;
    int pos = 0;
    while (!a.stopThread){
        if (client_fd == -1) {
            client_addr_size = sizeof(client_addr);
            client_fd = accept(a.sock, (struct sockaddr *) &client_addr, &client_addr_size);
            if (client_fd == -1){
                perror("accept:");
                continue;
            }
            std::cout<<"NetworkAnimation : client connected : "
                <<(client_addr.sin_addr.s_addr & 0xFF)<<"."
                <<((client_addr.sin_addr.s_addr>>8) & 0xFF)<<"."
                <<((client_addr.sin_addr.s_addr>>16) & 0xFF)<<"."
                <<((client_addr.sin_addr.s_addr>>24) & 0xFF)
                <<std::endl;
        } else {
            char r,g,b;
            ssize_t rr;
            rr =read(client_fd,&r,1);
            if (rr == 1 && (r == '\n' || r == '\r')){
                pos = 0;
                continue;
            }
            rr = read(client_fd,&g,1);
            if (rr==1 &&(g == '\n' || r == '\r')){
                pos = 0;
                continue;
            }
            rr = read(client_fd,&b,1);
            if (rr == 1 &&(b == '\n' || r == '\r')){
                pos = 0;
                continue;
            }
            if (rr<=0){
                close(client_fd);
                client_fd =-1;
                std::cout<<"NetworkAnimation : client disconected"<<std::endl;
                continue;
            }
            Color c(r-48,g-48,b-48);
            LedStrip* leds = a.leds;
            if (leds != NULL){
                if (pos >= leds->getLength()){
                    write(client_fd,"over\n",5);
                }else{
                    leds->setColor(pos,c);
                    pos++;
                }
            }
        }

    }

}

void NetworkAnimation::doAnimationStep(){
}
