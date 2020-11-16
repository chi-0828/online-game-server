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
#include <ctype.h>

int main() {

#if defined(_WIN32)
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d)) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }
#endif


    printf("Configuring local address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *bind_address;
    getaddrinfo(0, "8080", &hints, &bind_address);


    printf("Creating socket...\n");
    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family,
            bind_address->ai_socktype, bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }


    printf("Binding socket to local address...\n");
    if (bind(socket_listen,
                bind_address->ai_addr, bind_address->ai_addrlen)) {
        fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }
    freeaddrinfo(bind_address);


    printf("Listening...\n");
    if (listen(socket_listen, 10) < 0) {
        fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
        return 1;
    }

    fd_set master;
    FD_ZERO(&master);
    FD_SET(socket_listen, &master);
    SOCKET max_socket = socket_listen;

    printf("Waiting for connections...\n");
    typedef struct member M;
    struct member{
        char name[200];
        int id ;
        int login;
        int user2_id;
    };
    M mem[10];
    int member_count =0;
    while(1) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
            return 1;
        }

        SOCKET i;
        for(i = 1; i <= max_socket; ++i) {
            if (FD_ISSET(i, &reads)) {
                if (i == socket_listen) {
                    struct sockaddr_storage client_address;
                    socklen_t client_len = sizeof(client_address);
                    SOCKET socket_client = accept(socket_listen,
                            (struct sockaddr*) &client_address,
                            &client_len);
                    if (!ISVALIDSOCKET(socket_client)) {
                        fprintf(stderr, "accept() failed. (%d)\n",
                                GETSOCKETERRNO());
                        return 1;
                    }

                    FD_SET(socket_client, &master);
                    if (socket_client > max_socket)
                        max_socket = socket_client;

                    char address_buffer[100];
                    getnameinfo((struct sockaddr*)&client_address,
                            client_len,
                            address_buffer, sizeof(address_buffer), 0, 0,
                            NI_NUMERICHOST);
                    printf("New connection from %s  %d\n", address_buffer,socket_client);
                    // add new user
                    char mes[100];
                    memset(mes,'\0',100);
                    sprintf(mes,"%d",socket_client);
                    strcat(mes," welcome!!!!\n");
                    strcat(mes,"please enter user name: \n");
                    send(socket_client, mes, strlen(mes), 0);
                    mem[member_count].id = socket_client;
                    mem[member_count].login = -1;
                    mem[member_count].user2_id = -2;
                    member_count ++;

                } else {
                    char read[1024];
                    int bytes_received = recv(i, read, 1024, 0);
                    int k;
                    for(k =0;k<member_count;k++){
                        if(mem[k].id == i){
                            break;
                        }
                    }
                    //login
                    if(mem[k].login == -1){
                        //strcat(mem[k].name , read);
                        strncat(mem[k].name , read,bytes_received);
                        printf("%s\n",mem[k].name );
                        mem[k].login = 1;
                    }
                    // play game
                    else {
                        if (bytes_received < 1) {
                            FD_CLR(i, &master);
                            CLOSESOCKET(i);
                            continue;
                        }
                        for(k =0;k<member_count;k++){
                            if(mem[k].id == i){
                                break;
                            }
                        }
                        if(mem[k].user2_id == -1){
                            char temp_name[100]={'\0'};
                            strncat(temp_name , read,bytes_received-1);
                            for(k =0;k<member_count;k++){
                                if(strncmp(mem[k].name,temp_name,bytes_received-1) == 0){
                                    break;
                                }
                            }   
                            if(k == member_count){
                                send(i,"no this player\n",strlen("no this player\n"),0);
                                continue;
                            }
                            //request game
                            char message[100]={'\0'}; 
                            strcat(message,mem[i].name);
                            strcat(message," want to play with you!\nPlease enter \"Yes\" if you agree(others mean NO)\n");
                            send(mem[k].id,message,strlen(message),0);
                            mem[i].user2_id = mem[k].id;      
                            mem[k].user2_id = mem[i].id;                     
                        }
                        else if(strncmp(read,"show!\n",bytes_received) == 0){
                            send(i,"Players:\n",strlen("Players:\n"),0);
                            for(int l=0;l<member_count;l++){
                                fprintf(stderr,"%s",mem[l].name);
                                send(i,mem[l].name,strlen(mem[l].name),0);
                            }
                        }
                        else if(strncmp(read,"play!\n",bytes_received) == 0){
                            send(i,"Please enter user name who you want to play with:\n",strlen("Please enter user name who you want to play with:\n"),0);
                            for(k =0;k<member_count;k++){
                                if(mem[k].id == i){
                                    break;
                                }
                            }
                            mem[k].user2_id = -1;
                        }
                    }
                }
            } //if FD_ISSET
        } //for i to max_socket
    } //while(1)



    printf("Closing listening socket...\n");
    CLOSESOCKET(socket_listen);

#if defined(_WIN32)
    WSACleanup();
#endif


    printf("Finished.\n");

    return 0;
}
