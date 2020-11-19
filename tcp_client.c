/*
 * MIT License
 *
 * Copyright (c) 2018 Lewis Van Winkle
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "chap03.h"

#if defined(_WIN32)
#include <conio.h>
#endif

int main(int argc, char *argv[]) {

#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif

    if (argc < 3) {
        fprintf(stderr, "usage: tcp_client hostname port\n");
        return 1;
    }

    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo(argv[1], argv[2], &hints, &peer_address)) {
        fprintf(stderr, "getaddrinfo() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Remote address is: ");
    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
            address_buffer, sizeof(address_buffer),
            service_buffer, sizeof(service_buffer),
            NI_NUMERICHOST);
    printf("%s %s\n", address_buffer, service_buffer);


    printf("Creating socket...\n");
    SOCKET socket_peer;
    socket_peer = socket(peer_address->ai_family,
            peer_address->ai_socktype, peer_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_peer)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    printf("----%d----\n",socket_peer);

    printf("Connecting...\n");
    if (connect(socket_peer,
                peer_address->ai_addr, peer_address->ai_addrlen)) {
        fprintf(stderr, "connect() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(peer_address);

    printf("Connected.\n");
    printf("To send data, enter text followed by enter.\n");
    //red
    char color[100] = {'\0'};
    strcat(color,"\033[0;31m");
    while(1) {

        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer, &reads);
#if !defined(_WIN32)
        FD_SET(0, &reads);
#endif

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        if (select(socket_peer+1, &reads, 0, 0, &timeout) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        if (FD_ISSET(socket_peer, &reads)) {
            char read[4096];
            int bytes_received = recv(socket_peer, read, 4096, 0);
            if (bytes_received < 1) {
                printf("Connection closed by peer.\n");
                break;
            }
            int count=0;
            for(int i=0;i<bytes_received;i++){
                if(read[i] == '-')
                    count++;
            }
            if(count>10){
                int count = 0;
                printf("%s",color); 
                for(int k =0;k<bytes_received;k++){
                    if(read[k] == '*')
                        count++;
                    if(read[k] == 'X'  && count<32)
                        printf("\033[0;36m");
                    if(read[k] == 'O' && count<32)
                        printf("\033[0;32m");
                    printf("%c",read[k]);
                    if(count<32)
                        printf("%s",color); 
                    if(count == 32)
                        printf("\033[0m");
                }               
            }
            else if(strncmp(read,"chcolor",7) == 0){
                char name[10] = {'\0'};
                for(int i=8;i<bytes_received-1;i++){
                    name[i-8] = read[i];
                }
                if(strncmp(name,"yellow",6) == 0){
                    memset(color,'\0',100);
                    strcat(color,"\033[0;33m");
                }
                if(strncmp(name,"green",6) == 0){
                    memset(color,'\0',100);
                    strcat(color,"\033[0;32m");
                }
                if(strncmp(name,"red",6) == 0){
                    memset(color,'\0',100);
                    strcat(color,"\033[0;31m");
                }
                if(strncmp(name,"blue",6) == 0){
                    memset(color,'\0',100);
                    strcat(color,"\033[0;34m");
                }
                printf("%s",color); 
                printf("DONE!!!!!");
                printf("\033[0m");
                printf("\n");
            }
            else{
                printf("\033[0m"); 
                fwrite(read,bytes_received,1,stderr);                 
            }
            
        }
        if(FD_ISSET(0, &reads)) {
            char read[4096];
            memset(read,'\0',4096);
            if (!fgets(read, 4096, stdin)) break;
            int bytes_sent = send(socket_peer, read, strlen(read), 0);

        }
    } //end while(1)

    printf("Closing socket...\n");
    CLOSESOCKET(socket_peer);

#if defined(_WIN32)
    WSACleanup();
#endif

    printf("Finished.\n");
    return 0;
}

