#include "game.h"
#include <ctype.h>
#include <signal.h>
int stop ;
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
    if(play_ground[14]!= ' '&&play_ground[16] != ' '&&play_ground[18] != ' '&&play_ground[36] != ' '&& play_ground[38] != ' '&&play_ground[40] != ' '&& play_ground[58] != ' ' && play_ground[60] != ' '&&play_ground[62]!=' ')
        return 9;
    return -1;
}
int game(int c,int r,char A ,char *play_ground){
    int col_count =0;
    int row_count =0;
    r--;c--;
    for(int i=0;i<strlen(play_ground);i++){
        if((play_ground[i] == 'O'||play_ground[i] == 'X'||play_ground[i] == ' ')&&(play_ground[i+1]=='|'||play_ground[i-1]=='|')){
            if(col_count == c&& row_count == r){
                // this position already had O or X
                if(play_ground[i] != ' ') return -1;
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
void ctr_c_handler(){
    printf("\nDo you want to close server?(Y/N)");
    char ans;
    scanf("%c",&ans);
    if(ans == 'Y')
        stop = 1;
}
int main() {
    stop =0;
    struct sigaction action;  
    //signal(SIGINT,ctr_c_handler);
    action.sa_handler = ctr_c_handler;    
    sigemptyset(&action.sa_mask);    
    action.sa_flags = 0;    
    /* 设置SA_RESTART属性 */    
    action.sa_flags |= SA_RESTART;    
    sigaction(SIGINT, &action, NULL);

    typedef struct User U;
    struct User{
        char *name;
        char *pass;
        int state ;
    };
    U user[10];
    int user_count = 4;
    user[0].name = "gary";
    user[1].name = "mark";
    user[2].name = "jj";
    user[3].name = "jack";
    user[0].pass = "111";
    user[1].pass = "111";
    user[2].pass = "111";
    user[3].pass = "111";
    user[0].state = 0;
    user[1].state = 0;
    user[2].state = 0;
    user[3].state = 0;
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
        int win;
        int loose;
        char his[1000];
        char passward[100];
        int audience;
        int watch;
    };
    M mem[20];
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
    char play_ground[20][100]={'\0'};
    int play_grpund_turn[20] ;
    int court_cout = 0;
    while(1) {
        int no_gaming = 1;
        if(stop){
            for(int a=0;a<member_count;a++){
                if(mem[a].user2_id>0){
                    send(mem[a].id,"\e[1;1H\e[2Jsory! server will close after 3s\n",strlen("\e[1;1H\e[2Jsory! server will close after 3s\n"),0);
                    continue;
                }
                send(mem[a].id,"\e[1;1H\e[2J",strlen("\e[1;1H\e[2J"),0);
            }
            for(int b=0;b<3;b++){
                sleep(1);
            }
            break;
        }
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            if(errno != 4){
                fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
                return 1;
            }
            else{
                continue;
            }
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
                    mem[member_count].audience = -1;
                    mem[member_count].watch = -1;
                    mem[member_count].win = 0;
                    mem[member_count].loose = 0;
                    memset(mem[member_count].name,'\0',200);
                    memset(mem[member_count].his,'\0',1000);
                    memset(mem[member_count].passward,'\0',100);
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
                    if(strncmp(read,"signup",6) == 0){
                        //strcat(mem[k].name , read);
                        int l=8;
                        char name[100] = {'\0'};
                        char pass[100] = {'\0'};
                        for(;l<bytes_received-1;l++){
                            if(read[l] == '|')
                                break;
                            name[l-8] = read[l];
                        }
                        l++;
                        int a=0;
                        for(;l<bytes_received-1;l++){
                            pass[a] = read[l];
                            a++;
                        }
                        
                        user[user_count].name = malloc(100);
                        memset(user[user_count].name ,'\0',100);
                        strcat(user[user_count].name,name);
                        user[user_count].pass = malloc(100);
                        memset(user[user_count].pass ,'\0',100);
                        strcat(user[user_count].pass,pass);
                        user_count++;
                        send(mem[k].id,"Done! enter username to sign in\n",strlen("Done! enter username to sign in\n"),0);
                        continue;
                        
                    }
                    //login
                    if(mem[k].login == -1){
                        //strcat(mem[k].name , read);
                        int find =0;
                        for(int j=0;j<user_count;j++){
                            if(strncmp(read,user[j].name,strlen(user[j].name))==0 ){
                                if(strcmp(read,"\n") == 0){
                                    break;
                                }
                                if(user[j].state == 1){
                                    find = -1;
                                    break;
                                }
                                strcat(mem[k].passward ,user[j].pass);
                                user[j].state = 1;
                                find =1;
                                break;
                            }
                        }
                        
                        if(find == 1){
                            strncat(mem[k].name ,read,bytes_received);
                            printf("%s\n",mem[k].name );
                            mem[k].login = 1;
                            send(mem[k].id,"password:\n",strlen("password:\n"),0);
                            continue;
                        }
                        else if(find == -1){
                            send(mem[k].id,"you already login at other device\n",strlen("you already login at other device\n"),0);
                            continue;
                        }
                        else{
                            send(mem[k].id,"no user name\ncreate account please enter \"signup -<username>|<password>\"\n",strlen("no user name\ncreate account please enter \"signup -<username>|<password>\"\n"),0);
                            continue;
                        }
                    }
                    //create account
                    else if(mem[k].login == 1){
                        //strcat(mem[k].name , read);
                        if(strncmp(mem[k].passward,read,strlen(mem[k].passward))==0){
                            if(strcmp(read,"\n") == 0){
                                send(mem[k].id,"wrong password\n",strlen("wrong password\n"),0);
                                 continue;
                            }
                            mem[k].login = 2;
                            send(mem[k].id,"login success\n",strlen("login success\n"),0);
                            usleep(1);
                            char *mes = "\"chcolor -<color>\" : change output color\n       option : blue yellow red green\n\"play!\" : invite one player join a game\n\"show -user\" : show all players who are online\n\"show -game\" : show all players who are playing game\n\"watch -<user>\" : Watch the battle\n\"exit!\" : logout\n\"history\" : get info of last game\n";
                            send(i,mes,strlen(mes),0);
                            continue;
                        }
                        else{
                            send(mem[k].id,"wrong password\n",strlen("wrong password\n"),0);
                            continue;
                        }
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
                        if(strncmp(read,"chcolor",7) == 0){
                            char name[10] = {'\0'};
                            for(int i=9;i<bytes_received-1;i++){
                                name[i-9] = read[i];
                            }
                            char mes[100] = {'\0'};
                            sprintf(mes,"chcolor %s\n",name);
                            send(i,mes,strlen(mes),0);
                            continue;
                        }
                        else if(strncmp(read,"exit!",5) == 0){
                            send(mem[k].id,"see you next time\n",strlen("see you next time\n"),0);
                            //if in game
                            if(mem[k].user2_id > 0){
                                if(mem[k].audience > 0){
                                    send(mem[k].audience,"the player exited\n",strlen("the player exited\n"),0);
                                    for(int l=0;l<member_count;l++){
                                        if(mem[l].id == mem[k].audience){
                                            mem[l].watch = -1;
                                            break;
                                        }
                                    }
                                }
                                send(mem[k].user2_id,"opponent exited\nchoose another player\n",strlen("opponent exited\nchoose another player\n"),0);
                                for(int l=0;l<member_count;l++){
                                    if(mem[l].id == mem[k].user2_id){
                                        if(mem[l].audience > 0){
                                            send(mem[l].audience,"the player exited\n",strlen("the player exited\n"),0);
                                            for(int o=0;o<member_count;o++){
                                                if(mem[o].id == mem[l].audience){
                                                    mem[o].watch = -1;
                                                    break;
                                                }
                                            }
                                        }
                                        mem[l].user2_id = -1;
                                        mem[l].request = -1;
                                        mem[l].court = -1;
                                        break;
                                    }
                                }
                            }
                            //reset
                            char mes[100] = {'\0'};
                            usleep(1);
                            strcat(mes,"please enter user name: \n");
                            send(i, mes, strlen(mes), 0);
                            mem[k].login = -1;
                            mem[k].user2_id = -2;
                            mem[k].request = -1;
                            mem[k].court = -1;
                            mem[k].audience = -1;
                            mem[k].watch = -1;
                            for(int l=0;l<user_count;l++){
                                if(strncmp(mem[k].name,user[l].name,strlen(user[l].name)) == 0){
                                    user[l].state = 0;
                                    break;
                                }
                            }
                            memset(mem[k].name,'\0',200);
                            memset(mem[k].his,'\0',1000);
                            memset(mem[k].passward,'\0',100);
                            continue;
                        }
                        // in game
                        if(mem[k].user2_id >= 0){
                            //again
                            if(mem[k].request == -2){
                                mem[k].request = -3;
                                //agree
                                if(strncmp(read,"Y\n",bytes_received) == 0){
                                    int l;
                                    for(l=0;l,member_count;l++){
                                        if(mem[l].id == mem[k].user2_id)
                                            break;
                                    }
                                    if(mem[l].request == -2){
                                        send(mem[k].id,"wait for your opponent\n",strlen("wait for your opponent\n"),0);
                                        continue;
                                    }
                                    send(mem[k].id,play_borad,strlen(play_borad),0);
                                    usleep(1);
                                    send(mem[l].id,play_borad,strlen(play_borad),0);
                                    memset(mem[l].his,'\0',1000);
                                    memset(mem[k].his,'\0',1000);
                                    memset(play_ground[mem[k].court],'\0',100);
                                    strcat(play_ground[mem[k].court],play_borad);
                                    play_grpund_turn[mem[k].court] = mem[k].id;
                                    send(mem[k].id,"Your turn\n",strlen("Your turn\n"),0);
                                    continue;
                                }
                                //reject
                                else {
                                    int l;
                                    for(l=0;l,member_count;l++){
                                        if(mem[l].id == mem[k].user2_id)
                                            break;
                                    }
                                    usleep(1);
                                    send(mem[k].id,"enter \"play!\" to have fun with others\nIf you want to see last game history, enter \"history\"\n",strlen("enter \"play!\" to have fun with others\nIf you want to see last game history, enter \"history\"\n"),0);
                                    usleep(1);
                                    send(mem[k].user2_id,"enter \"play!\" to have fun with others\nIf you want to see last game history, enter \"history\"\n",strlen("enter \"play!\" to have fun with others\nIf you want to see last game history, enter \"history\"\n"),0);
                                    mem[k].user2_id = -2;
                                    mem[k].request = -1;
                                    mem[k].court = -1;
                                    mem[l].user2_id = -2;
                                    mem[l].request = -1;
                                    mem[l].court = -1;
                                    continue;
                                }
                            }
                            if(play_grpund_turn[mem[k].court] != mem[k].id){
                                //send(i,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                                usleep(1);
                                send(i,"Please wait, not your turn\n",strlen("Please wait, not your turn\n"),0);
                                continue;
                            }
                            int c = -1,r =-1;
                            sscanf(read,"%d%d",&r,&c);
                            if(r>3 || r<0 || c>3 || c<0){
                                usleep(1);
                                send(i,"Please enter correct location\n",strlen("Please enter correct location\n"),0);
                                continue;
                            }
                            int state = game(c,r,mem[k].A,play_ground[mem[k].court]);
                            int l;
                            for(l=0;l,member_count;l++){
                                if(mem[l].id == mem[k].user2_id)
                                    break;
                            }
                            strcat(mem[k].his,"\nYOU : \n");
                            strcat(mem[k].his,play_ground[mem[k].court]);
                            strcat(mem[l].his,"\nOPPONENT : \n");
                            strcat(mem[l].his,play_ground[mem[k].court]);
                            send(i,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                            send(mem[k].user2_id,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                            if(mem[k].audience>0){
                                send(mem[k].audience,mem[k].name,strlen(mem[k].name),0);
                                usleep(1);
                                send(mem[k].audience,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                            }
                            else if(mem[l].audience>0){
                                send(mem[l].audience,mem[k].name,strlen(mem[k].name),0);
                                usleep(1);
                                send(mem[l].audience,play_ground[mem[k].court],strlen(play_ground[mem[k].court]),0);
                            }
                            if(state > 0&&stop == 1){
                                send(i,"NICE! YOU WIN!\n",strlen("NICE! YOU WIN!\n"),0);
                                usleep(1);
                                send(mem[k].user2_id,"GAME OVER , YOU LOOSE!\n",strlen("GAME OVER , YOU LOOSE!\n"),0);
                                continue;
                            }
                            if(state > 0){
                                if(state == 9){
                                    send(i,"Again?(Y/N)\n",strlen("Again?(Y/N)\n"),0);
                                    usleep(1);
                                    send(mem[k].user2_id,"Again?(Y/N)\n",strlen("Again?(Y/N)\n"),0);
                                    mem[k].request = -2;
                                    int l;
                                    for(l=0;l,member_count;l++){
                                        if(mem[l].id == mem[k].user2_id)
                                            break;
                                    }
                                    mem[l].request = -2;
                                    continue;
                                }
                                else{
                                    send(i,"NICE! YOU WIN!\nAgain?(Y/N)\n",strlen("NICE! YOU WIN!\nAgain?(Y/N)\n"),0);
                                    mem[k].win++;
                                    usleep(1);
                                    send(mem[k].user2_id,"GAME OVER , YOU LOOSE!\nAgain?(Y/N)\n",strlen("GAME OVER , YOU LOOSE!\nAgain?(Y/N)\n"),0);
                                    mem[l].loose++;
                                    mem[k].request = -2;
                                    int l;
                                    for(l=0;l,member_count;l++){
                                        if(mem[l].id == mem[k].user2_id)
                                            break;
                                    }
                                    mem[l].request = -2;
                                    continue;
                                }
                            }
                            else if(state < 0){
                                send(i,"Please choose another position\n",strlen("Please choose another position\n"),0);
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
                                if(strncmp(mem[l].name,temp_name,strlen(temp_name)) == 0){
                                    if(mem[l].user2_id>0)
                                        fail = 1;
                                    if(mem[l].id == mem[k].id)
                                        fail = 2;
                                    break;
                                }
                            }   
                            if(fail == 1){
                                send(i,"this player is already in game\n",strlen("this player is already in game\n"),0);
                                continue;
                            }
                            if(fail == 2){
                                send(i,"You can't play with yourself\n",strlen("You can't play with yourself"),0);
                                continue;
                            }
                            if(l == member_count){
                                send(i,"no this player\n",strlen("no this player\n"),0);
                                continue;
                            }
                            //request game
                            char message[100]={'\0'}; 
                            strncat(message,mem[k].name,strlen(mem[k].name)-1);
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
                                usleep(1);
                                send(mem[l].id,play_borad,strlen(play_borad),0);
                                send(mem[l].id,"You are \"O\"\nYour turn\n",strlen("You are \"O\"\nYour turn\n"),0);

                                memset(mem[l].his,'\0',1000);
                                memset(mem[k].his,'\0',1000);
                                
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
                                for(l=0;l<member_count;l++){
                                    if(mem[l].id == mem[k].request)
                                        break;
                                }
                                mem[l].user2_id = -2;
                                mem[k].request = -1;
                            }

                            continue;
                        }
                        else if(mem[k].watch > 0){
                            if(strncmp(read,"out\n",bytes_received) == 0){
                                for(int l=0;l<member_count;l++){
                                    if(mem[l].id == mem[k].watch){
                                        mem[l].audience = -1;
                                        break;
                                    }
                                }
                                mem[k].watch = -1;
                                send(i,"exit watching\n",strlen("exit watching\n"),0);
                                continue;
                            }
                            send(i,"you can enter \"out\" to stop watching\n",strlen("you can enter \"out\" to stop watching\n"),0);
                            continue;
                        }
                        else if(strncmp(read,"show -user\n",bytes_received) == 0){
                            send(i,"Players:\n",strlen("Players:\n"),0);
                            for(int l=0;l<member_count;l++){
                                fprintf(stderr,"%s",mem[l].name);
                                send(i,mem[l].name,strlen(mem[l].name),0);
                            }
                            continue;
                        }
                        else if(strncmp(read,"show -game\n",bytes_received) == 0){
                            send(i,"Players:\n",strlen("Players:\n"),0);
                            char mes[100] = {'\0'};
                            for(int l=0;l<member_count;l++){
                                if(mem[l].user2_id>0){
                                    int j=0;
                                    for(j=0;j<member_count;j++){
                                        if(mem[j].id == mem[l].user2_id){
                                            char name1[10] = {'\0'};
                                            char name2[10] = {'\0'};
                                            strncat(name1,mem[l].name,strlen(mem[l].name)-1);
                                            strncat(name2,mem[j].name,strlen(mem[j].name)-1);
                                            sprintf(mes,"%s vs %s\n",name1,name2);
                                            break;
                                        }
                                    }
                                    send(i,mes,strlen(mes),0);
                                    memset(mes,'\0',100);
                                }
                            }
                            continue;
                        }
                        else if(strncmp(read,"rank\n",bytes_received) == 0){
                            char rank_name[member_count][100] ;
                            memset(rank_name,'\0',member_count*100);
                            double rank_score[member_count] ;
                            for(int l=0;l<member_count;l++){
                                if(l == k)
                                    strncat(rank_name[l],"\033[0;31m",strlen("\033[0;31m"));
                                strncat(rank_name[l],mem[l].name,strlen(mem[l].name)-1);
                                if(l == k)
                                    strncat(rank_name[l],"\033[0m",strlen("\033[0m"));
                                rank_score[l] =((double)mem[l].win/((double)mem[l].win+(double)mem[l].loose));
                                printf("%f\n",rank_score[l]);
                            }
                            for(int l=0;l<member_count;l++){
                                for(int j=l+1;j<member_count;j++){
                                    if(rank_score[l] < rank_score[j]){
                                        double temp = rank_score[l];
                                        rank_score[l] = rank_score[j];
                                        rank_score[j] = temp;
                                        char temp_name[100] = {'\0'};
                                        strcat(temp_name,rank_name[l]);
                                        memset(rank_name[l],'\0',100);
                                        strcat(rank_name[l],rank_name[j]);
                                        memset(rank_name[j],'\0',100);
                                        strcat(rank_name[j],temp_name);
                                    }
                                }
                            }
                            // send ranking
                            for(int l=0;l<member_count;l++){
                                char mes[100] = {'\0'};
                                sprintf(mes,"rank:%d  name:%s --- Win rate: %f\n",l+1,rank_name[l],rank_score[l]);
                                send(i,mes,strlen(mes),0);
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
                        else if(strncmp(read,"history\n",bytes_received) == 0){
                            FILE *his;
                            char buffer[200];
                            
                            char name[100] = {'\0'};
                            strcat(name,"./record/history_");
                            strncat(name,mem[k].name,strlen(mem[k].name)-1);
                            strcat(name,".txt");
                            his = fopen(name,"w");
                            setvbuf(his, buffer, _IONBF, 0);
                            if(!his){
                                send(i,"Download error\n",strlen("Download error\n"),0);
                                printf("%s",name);
                                continue;
                            }
                            int s = fwrite(mem[k].his,1,strlen(mem[k].his),his);
                            fwrite(mem[k].his,1,strlen(mem[k].his),stderr);
                            printf("%d\n",s);
                            if(s>0)
                                send(i,"Record file is loacted at ./record/\n",strlen("Record file is loacted at ./record/\n"),0);
                            else
                                send(i,"Download error\n",strlen("Download error\n"),0);
                            continue;
                        }
                        else if(strncmp(read,"watch",5) == 0){
                            send(i,"you can enter \"out\" to stop watching\n",strlen("you can enter \"out\" to stop watching\n"),0);
                            char name[10] = {'\0'};
                            for(int i=7;i<bytes_received-1;i++){
                                name[i-7] = read[i];
                            }
                            printf("%s\n",name);
                            int l;
                            for(l=0;l<member_count;l++){
                                if(strncmp(name,mem[l].name,strlen(name)) == 0)
                                    break;
                            }
                            mem[l].audience = mem[k].id;
                            mem[k].watch = mem[l].id;
                            continue;
                        }
                        else{
                            char *mes = "\"chcolor -<color>\" : change output color\n       option : blue yellow red green\n\"play!\" : invite one player join a game\n\"show -user\" : show all players who are online\n\"show -game\" : show all players who are playing game\n\"watch -<user>\" : Watch the battle\n\"exit!\" : logout\n\"history\" : get info of last game\n";
                            send(i,mes,strlen(mes),0);
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
