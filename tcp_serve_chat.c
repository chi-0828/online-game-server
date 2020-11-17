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
int check(char *play_ground){
    //15 17 19
    //37 39 41
    //59 61 63
    if(play_ground[14]==play_ground[16]&&play_ground[14]==play_ground[18]&&play_ground[14]!=' ')
        return 1;
    if(play_ground[36]==play_ground[38]&&play_ground[38]==play_ground[40]&&play_ground[40]!=' ')
        return 2;
    if(play_ground[58]==play_ground[60]&&play_ground[62]==play_ground[60]&&play_ground[60]!=' ')
        return 3;
    if(play_ground[14]==play_ground[36]&&play_ground[14]==play_ground[58]&&play_ground[14]!=' ')
        return 4;
    if(play_ground[38]==play_ground[16]&&play_ground[16]==play_ground[60]&&play_ground[16]!=' ')
        return 5;
    if(play_ground[18]==play_ground[40]&&play_ground[18]==play_ground[62]&&play_ground[18]!=' ')
        return 6;
    if(play_ground[14]==play_ground[38]&&play_ground[38]==play_ground[62]&&play_ground[14]!=' ')
        return 7;
    if(play_ground[18]==play_ground[38]&&play_ground[38]==play_ground[58]&&play_ground[18]!=' ')
        return 8;
    return -1;
}
int game(int c,int r,char A ,char *play_ground){
    int col_count =0;
    int row_count =0;
    r--;c--;
    for(int i=0;i<strlen(play_ground);i++){
        if((play_ground[i] == 'O'||play_ground[i] == 'X'||play_ground[i] == ' ')&&(play_ground[i+1]=='|'||play_ground[i-1]=='|')){
            if(col_count == c&& row_count == r){
                play_ground[i] = A;
                break;
            }
            else{
                if((col_count+1)%3 == 0 &&col_count!=0){
                    row_count++;
                    col_count = 0;
                    continue;
                }
                col_count++;
            }
        }
    }
    int state = check(play_ground);
    fprintf(stderr,"%d\n",state);
    if(state!= -1){
        return 1;
    }
    return 0;
}
int main() {
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
        int request;
        int court;
        char A;
    };
    M mem[10];
    int member_count =0;
    //15 17 19
    //37 39 41
    //59 61 63
    char play_borad[100] = {'*','*','*','*','*','*','*','*','*','*','\n',
                        '*','1',' ',' ','|',' ','|',' ',' ','*','\n',
                        '*',' ','-','-','-','-','-','-','-','*','\n',
                        '*','2',' ',' ','|',' ','|',' ',' ','*','\n',
                        '*',' ','-','-','-','-','-','-','-','*','\n',
                        '*','3',' ',' ','|',' ','|',' ',' ','*','\n',
                        '*',' ',' ','1',' ','2',' ','3',' ','*','\n',
                        '*','*','*','*','*','*','*','*','*','*','\n','\0'};
    char play_ground[10][100]={'\0'};
    int play_grpund_turn[10] ;
    int court_cout = 0;
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
                    mem[member_count].request = -1;
                    mem[member_count].court = -1;
                    memset(mem[member_count].name,'\0',200);
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
                        // in game
                        if(mem[k].user2_id >= 0){
                            if(play_grpund_turn[mem[k].court] != mem[k].id){
                                send(i,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                                send(i,"Please wait, not your turn\n",strlen("Please wait, not your turn\n"),0);
                                continue;
                            }
                            int c,r;
                            sscanf(read,"%d%d",&r,&c);
                            if(r>3 || r<0 || c>3 || c<0){
                                send(i,"Please enter correct location\n",strlen("Please enter correct location\n"),0);
                                continue;
                            }
                            int state = game(c,r,mem[k].A,play_ground[mem[k].court]);
                            send(i,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                            send(mem[k].user2_id,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                            if(state != 0){
                                send(i,"NICE! YOU WIN!\n",strlen("NICE! YOU WIN!\n"),0);
                                send(mem[k].user2_id,"GAME OVER , YOU LOOSE!\n",strlen("GAME OVER , YOU LOOSE!\n"),0);
                                continue;
                            }
                            play_grpund_turn[mem[k].court] = mem[k].user2_id;
                            send(mem[k].user2_id,"Your turn\n",strlen("Your turn\n"),0);
                            continue;
                        }
                        else if(mem[k].user2_id == -1){
                            char temp_name[100]={'\0'};
                            strncat(temp_name , read,bytes_received-1);
                            int l;
                            int fail = 0;
                            for( l=0;l<member_count;l++){
                                if(strncmp(mem[l].name,temp_name,bytes_received-1) == 0){
                                    if(mem[l].user2_id>0)
                                        fail = 1;
                                    break;
                                }
                            }   
                            if(fail){
                                send(i,"this player is already in game\n",strlen("this player is already in game\n"),0);
                                continue;
                            }
                            if(l == member_count){
                                send(i,"no this player\n",strlen("no this player\n"),0);
                                continue;
                            }
                            //request game
                            char message[100]={'\0'}; 
                            strncat(message,mem[l].name,strlen(mem[l].name)-1);
                            strcat(message," want to play with you!\nPlease enter \"Yes\" if you agree(others mean NO)\n");
                            send(mem[l].id,message,strlen(message),0);
                            send(mem[k].id,"wait...\n",strlen("wait...\n"),0);
                            mem[l].user2_id = -3; // recevive request
                            mem[k].user2_id = -4; // send request
                            mem[l].request = mem[k].id; // record request id
                            continue;                    
                        }
                        else if(mem[k].user2_id == -4){
                            send(mem[k].id,"wait...\n",strlen("wait...\n"),0);
                            continue;
                        }
                        else if(mem[k].user2_id == -3){
                            char temp_name[100]={'\0'};
                            strncat(temp_name , read,bytes_received-1);
                            //if agree request
                            if(strncmp(temp_name,"Yes",bytes_received-1) == 0){
                                char message[100]={'\0'}; 
                                strncat(message,mem[k].name,strlen(mem[k].name)-1);
                                strcat(message," agree\n");
                                send(mem[k].request,message,strlen(message),0);
                                int l;
                                mem[k].user2_id = mem[k].request; 
                                for(l=0;l,member_count;l++){
                                    if(mem[l].id == mem[k].request)
                                        break;
                                }
                                mem[l].user2_id = mem[k].id;
                                mem[k].A = 'X';
                                send(mem[k].id,play_borad,strlen(play_borad),0);
                                send(mem[k].id,"You are \"X\"\n",strlen("You are \"X\"\n"),0);
                                
                                mem[l].A = 'O';
                                send(mem[l].id,play_borad,strlen(play_borad),0);
                                send(mem[l].id,"You are \"O\"\nYour turn\n",strlen("You are \"O\"\nYour turn\n"),0);
                                
                                mem[k].court = court_cout;
                                mem[l].court = court_cout;
                                strcat(play_ground[court_cout],play_borad);
                                play_grpund_turn[court_cout] = mem[l].id;
                                court_cout++;
                            }
                            //reject
                            else{
                                char message[100]={'\0'}; 
                                strncat(message,mem[k].name,strlen(mem[k].name)-1);
                                strcat(message," reject your request\n");
                                send(mem[k].request,message,strlen(message),0);
                                
                                int l;
                                for(l=0;l,member_count;l++){
                                    if(mem[l].id == mem[k].request)
                                        break;
                                }
                                mem[l].user2_id = -2;
                                mem[k].request = -1;
                            }

                            continue;
                        }
                        else if(strncmp(read,"show!\n",bytes_received) == 0){
                            send(i,"Players:\n",strlen("Players:\n"),0);
                            for(int l=0;l<member_count;l++){
                                fprintf(stderr,"%s",mem[l].name);
                                send(i,mem[l].name,strlen(mem[l].name),0);
                            }
                            continue;
                        }
                        else if(strncmp(read,"play!\n",bytes_received) == 0){
                            send(i,"Please enter user name who you want to play with:\n",strlen("Please enter user name who you want to play with:\n"),0);
                            for(k =0;k<member_count;k++){
                                if(mem[k].id == i){
                                    break;
                                }
                            }
                            mem[k].user2_id = -1;
                            continue;
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
