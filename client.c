#include "game.h"
#include <signal.h>
int check(int peer , char *play_ground){
    //sleep(1);
    //15 17 19
    //37 39 41
    //59 61 63
    if(play_ground[14]==play_ground[16]&&play_ground[14]==play_ground[18]&&play_ground[14]!=' ')
        return -1;
    if(play_ground[36]==play_ground[38]&&play_ground[38]==play_ground[40]&&play_ground[40]!=' ')
        return -1;
    if(play_ground[58]==play_ground[60]&&play_ground[62]==play_ground[60]&&play_ground[60]!=' ')
        return -1;
    if(play_ground[14]==play_ground[36]&&play_ground[14]==play_ground[58]&&play_ground[14]!=' ')
        return -1;
    if(play_ground[38]==play_ground[16]&&play_ground[16]==play_ground[60]&&play_ground[16]!=' ')
        return -1;
    if(play_ground[18]==play_ground[40]&&play_ground[18]==play_ground[62]&&play_ground[18]!=' ')
        return -1;
    if(play_ground[14]==play_ground[38]&&play_ground[38]==play_ground[62]&&play_ground[14]!=' ')
        return -1;
    if(play_ground[18]==play_ground[38]&&play_ground[38]==play_ground[58]&&play_ground[18]!=' ')
        return -1;
    if(play_ground[14]!= ' '&&play_ground[16] != ' '&&play_ground[18] != ' '&&play_ground[36] != ' '&& play_ground[38] != ' '&&play_ground[40] != ' '&& play_ground[58] != ' ' && play_ground[60] != ' '&&play_ground[62]!=' ')
        return -1;
    if((play_ground[16]==play_ground[18]&&play_ground[14]==' '&&play_ground[16]!=' ' )|| (play_ground[36]==play_ground[58]&&play_ground[14]==' '&&play_ground[36]!=' ') || (play_ground[38]==play_ground[62]&&play_ground[14]==' '&&play_ground[38]!=' ')){
        int a = send(peer,"1 1\n",strlen("1 1\n"),0);
        fprintf(stderr,"1 1\n");
        return 1;
    }
    if((play_ground[14]==play_ground[16]&&play_ground[18]==' '&&play_ground[14]!=' ' )|| (play_ground[38]==play_ground[58]&&play_ground[18]==' '&&play_ground[38]!=' ') || (play_ground[40]==play_ground[62]&&play_ground[18]==' '&&play_ground[40]!=' ')){
        int a = send(peer,"1 3\n",strlen("1 3\n"),0);
        fprintf(stderr,"1 3\n");
        return 1;
    }
    if((play_ground[14]==play_ground[18]&&play_ground[16]==' '&&play_ground[14]!=' ' )|| (play_ground[38]==play_ground[60]&&play_ground[16]==' '&&play_ground[38]!=' ')){
        int a = send(peer,"1 2\n",strlen("1 2\n"),0);
        fprintf(stderr,"1 2\n");
        return 1;
    }
    if((play_ground[14]==play_ground[36]&&play_ground[58]==' '&&play_ground[14]!=' ' )|| (play_ground[60]==play_ground[62]&&play_ground[58]==' '&&play_ground[60]!=' ') || (play_ground[18]==play_ground[38]&&play_ground[58]==' '&&play_ground[18]!=' ')){
        int a = send(peer,"3 1\n",strlen("3 1\n"),0);
        fprintf(stderr,"3 1\n");
        return 1;
    }
    if((play_ground[18]==play_ground[40]&&play_ground[62]==' '&&play_ground[18]!=' ' )|| (play_ground[58]==play_ground[60]&&play_ground[62]==' '&&play_ground[58]!=' ') || (play_ground[14]==play_ground[38]&&play_ground[62]==' '&&play_ground[14]!=' ')){
        int a = send(peer,"3 3\n",strlen("3 3\n"),0);
        fprintf(stderr,"3 3\n");
        return 1;
    }
    if((play_ground[58]==play_ground[62]&&play_ground[60]==' '&&play_ground[58]!=' ' )|| (play_ground[16]==play_ground[38]&&play_ground[60]==' '&&play_ground[16]!=' ')){
        int a = send(peer,"3 2\n",strlen("3 2\n"),0);
        fprintf(stderr,"3 2\n");
        return 1;
    }
    if((play_ground[14]==play_ground[58]&&play_ground[36]==' '&&play_ground[14]!=' ' )|| (play_ground[38]==play_ground[40]&&play_ground[36]==' '&&play_ground[38]!=' ')){
        int a = send(peer,"2 1\n",strlen("2 1\n"),0);
        fprintf(stderr,"2 1\n");
        return 1;
    }
    if((play_ground[18]==play_ground[62]&&play_ground[40]==' '&&play_ground[18]!=' ' )|| (play_ground[36]==play_ground[38]&&play_ground[40]==' '&&play_ground[36]!=' ')){
        int a = send(peer,"2 3\n",strlen("2 3\n"),0);
        fprintf(stderr,"2 3\n");
        return 1;
    }
    if((play_ground[14]==play_ground[32]&&play_ground[38]==' '&&play_ground[14]!=' ' )|| (play_ground[60]==play_ground[16]&&play_ground[38]==' '&&play_ground[16]!=' ') 
            || (play_ground[18]==play_ground[58]&&play_ground[38]==' '&&play_ground[18]!=' ') || (play_ground[40]==play_ground[36]&&play_ground[38]==' '&&play_ground[40]!=' ')){
        int a = send(peer,"2 2\n",strlen("2 2\n"),0);
        fprintf(stderr,"2 2\n");
        return 1;
    }
    //15 17 19
    //37 39 41
    //59 61 63
    if(play_ground[14]==' '){
        int a = send(peer,"1 1\n",strlen("1 1\n"),0);
        fprintf(stderr,"1 1\n");
        return 1;
    }
    if(play_ground[16]==' '){
        int a = send(peer,"1 2\n",strlen("1 2\n"),0);
        fprintf(stderr,"1 2\n");
        return 1;
    }
    if(play_ground[18]==' '){
        int a = send(peer,"1 3\n",strlen("1 3\n"),0);
        fprintf(stderr,"1 3\n");
        return 1;
    }
    if(play_ground[36]==' '){
        int a = send(peer,"2 1\n",strlen("2 1\n"),0);
        fprintf(stderr,"2 1\n");
        return 1;
    }
    if(play_ground[38]==' '){
        int a = send(peer,"2 2\n",strlen("2 2\n"),0);
        fprintf(stderr,"2 2\n");
        return 1;
    }
    if(play_ground[40]==' '){
        int a = send(peer,"2 3\n",strlen("2 3\n"),0);
        fprintf(stderr,"2 3\n");
        return 1;
    }
    if(play_ground[58]==' '){
        int a = send(peer,"3 1\n",strlen("3 1\n"),0);
        fprintf(stderr,"3 1\n");
        return 1;
    }
    if(play_ground[60]==' '){
        int a = send(peer,"3 2\n",strlen("3 2\n"),0);
        fprintf(stderr,"3 2\n");
        return 1;
    }
    if(play_ground[62]==' '){
        int a = send(peer,"3 3\n",strlen("3 3\n"),0);
        fprintf(stderr,"3 3\n");
        return 1;
    }
    return -1;
}
void my_wait(size_t secs)
{
	usleep(50000);

}
int stop;
void print_progress(size_t count, size_t max)
{
	const char prefix[] = "Progress: [";
	const char suffix[] = " ]";
	const size_t prefix_length = sizeof(prefix) - 1;
	const size_t suffix_length = sizeof(suffix) - 1;
	char *buffer = calloc(max*5 + prefix_length + suffix_length + 1, 1); // +1 for \0
	size_t i = 0;
    char array[5];
    strcpy(array, u8"\u25A0");
	strcpy(buffer, prefix);
	for (; i < max; ++i){
        if(i<count)
            strcat(buffer,array);
        else
		    strcat(buffer," ");
	}

	strcat(buffer,suffix);
	printf("\b\b\b\b");
	fflush(stdout);
    printf("%c[2K\r%s %ld%c\r", 27, buffer,count*10/2,'%');
	free(buffer);
}
void ctr_c_handler(){
    printf("\nDo you want to exit?(Y/N)");
    char ans;
    scanf("%c",&ans);
    if(ans == 'Y')
        stop = 1;
}
int main(int argc, char *argv[]) {
    stop = 0;
    struct sigaction action;  
    //signal(SIGINT,ctr_c_handler);
    action.sa_handler = ctr_c_handler;    
    sigemptyset(&action.sa_mask);    
    action.sa_flags = 0;    
    /* 设置SA_RESTART属性 */    
    action.sa_flags |= SA_RESTART;    
    sigaction(SIGINT, &action, NULL);
    printf("Configuring remote address...\n");
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    struct addrinfo *peer_address;
    if (getaddrinfo("0", "8080", &hints, &peer_address)) {
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
    int AUTO = 0;
    while(1) {
        if(stop == 1){
            send(socket_peer,"88\n",strlen("88/n"),0);
            break;
        }
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
            if(errno != 4){
                fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
                return 1;
            }
            else{
                continue;
            }
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
                int i=0;
                int a =1;
                char ground[200] = {'\0'};
                printf("%s",color); 
                for(int k =0;k<bytes_received;k++){
                    if(read[k] == '*')
                        count++;
                    if(count == 0)
                        printf("\033[0m");
                    if(count<32 && count>0)
                        printf("%s",color); 
                    if(read[k] == 'X'  && count<32)
                        printf("\033[0;36m");
                    if(read[k] == 'O' && count<32)
                        printf("\033[0;32m");
                    printf("%c",read[k]);
                    if(count<32 && count>0)
                        printf("%s",color); 
                    if(count == 32)
                        printf("\033[0m");
                    if(count<32 && count>0)
                        ground[i++] = read[k];
                }           
                if(AUTO)    
                    a = check(socket_peer,ground);
                if(a < 0)
                    AUTO = 0;
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
            else if(strncmp(read,"AUTO",4) == 0){
                AUTO = 1;
                printf("\033[0m"); 
                fwrite(read,bytes_received,1,stderr);  
            }
            else if(strncmp(read,"enter \"play!\" to have fun with others\nIf you want to see last game history, enter \"history\"\n",strlen("enter \"play!\" to have fun with others\nIf you want to see last game history, enter \"history\"\n")) == 0){
                AUTO = 0;
                printf("\033[0m"); 
                fwrite(read,bytes_received,1,stderr);  
            }
            else if(strncmp(read,"see you next time\n",strlen("see you next time\n")) == 0){
                size_t num_secs = 1, max_secs = 20;
                printf("%s\n", "");
                print_progress(0, max_secs);
                for (; num_secs <= max_secs; ++num_secs) {
                    my_wait(1);
                    print_progress(num_secs, max_secs);
                }
                printf("%s\n", "");
                printf("%s\n", "done");
            }
            else if(strncmp(read,"\e[1;1H\e[2J",strlen("\e[1;1H\e[2J")) == 0){
                printf("\033[0m"); 
                fwrite(read,bytes_received,1,stderr);      
                printf("3\n");
                sleep(1);
                printf("2\n");
                sleep(1);
                printf("1\n");
                break;
            }
            else if(strncmp(read,"login success\n",strlen("login success\n")) == 0){
                size_t num_secs = 1, max_secs = 20;
                printf("%s\n", "");
                print_progress(0, max_secs);
                for (; num_secs <= max_secs; ++num_secs) {
                    my_wait(1);
                    print_progress(num_secs, max_secs);
                }
                printf("%s\n", "");
                printf("%s\n", "done");
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

    printf("Finished.\n");
    return 0;
}

