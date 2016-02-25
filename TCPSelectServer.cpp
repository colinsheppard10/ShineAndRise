#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <header.h>

using std::cout;
using std::endl;
using std::string;

void getTime(char* buffer){
    time_t curtime;
    struct tm* loctime;
    char localBuffer[99];
    
    //get the current time
    curtime = time(NULL);
    
    //convert curtime to localtime
    loctime = localtime(&curtime);
    
    //fill the localBuffer
    asctime_r(loctime, localBuffer);
    
    //copy localBuffer to passed in buffer
    memmove(buffer, localBuffer, 24);
    
}
int setUpServer(){
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *addrlooper;
    int status;
    int sockfd;
    
    memset(&hints,0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    
    // setting up servinfo struct
    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0){
        printf("there was an error\n");
    }else{
        printf("got addrinfo status: %d\n",status);
    }
    
    // finding socket
    for (addrlooper = servinfo; addrlooper != NULL; addrlooper = addrlooper->ai_next){
        sockfd = socket(addrlooper->ai_family, addrlooper->ai_socktype, addrlooper->ai_protocol);
        if (sockfd == -1)
            continue;
        else break;
    }
    printf("socket found, sockfd:%d\n", sockfd);
    
    // binding to a socket
    status = bind(sockfd, addrlooper->ai_addr, addrlooper->ai_addrlen);
    if (status == -1)
        printf("failed finding binding\n");
    else
        printf("binding completed\n");
    
    // making listen call
    int listenval = listen(sockfd, 5);
    if (listenval == -1)
        printf("listening error\n");
    else
        printf("listening\n");
    return sockfd;
};
int acceptClient(int mainSocket){
    
    struct sockaddr_storage addr_storage;
    memset(&addr_storage,0, sizeof(struct sockaddr));
    socklen_t addrlen = sizeof( struct sockaddr_storage);
    
    int newfd = accept(mainSocket,(struct sockaddr *)&addr_storage, &addrlen);
    if (newfd == -1)
        printf("accepting error");
    
    return newfd;
};
void android(char* input){
    cout << "found android" << endl;
    cout << input << endl;
    
    char buffer[60] ={0};
    strcpy(buffer, "INSERT INTO subjects (menu_name) VALUE('");
    char *secondHalf = "');";
    
    strcat(buffer, input);
    // buffer[strlen(buffer)-1] = 0;
    strcat(buffer, secondHalf);
    
    cout << "from finished: "<< buffer << endl;
    access_database(buffer);
    
}
void esp(){
    char buffer[24];
    getTime(buffer);
    
    cout << "found esp from TCP select" << endl;
    memmove(buffer+4, buffer + 11, 10);
    memset(buffer + 9, '\0', 15);
    char queryBuffer[53] = {0};
    strcpy(queryBuffer, "SELECT * FROM subjects WHERE menu_name = '");
    char *secondHalf = "';";
    strcat(queryBuffer, buffer);
    strcat(queryBuffer, secondHalf);
    cout << queryBuffer << endl;
    access_database(queryBuffer);
    
}

int main(){
    
    fd_set tempSet;
    fd_set master;
    int listener;
    char timeBuffer[30];
    char inputBuffer[99] = {0};
    
    listener = setUpServer();
    
    FD_ZERO(&tempSet);
    FD_ZERO(&master);
    FD_SET(listener,&master);
    
    int numberfd = listener;
    for(;;){
        tempSet = master;
        select(numberfd+1, &tempSet, NULL, NULL, NULL);
        
        int i;
        for(i=0;i<= numberfd;i++){
            
            if (FD_ISSET(i, &tempSet)){
                if (i == listener){
                    int newfd;
                    newfd = acceptClient(listener);
                    cout << "new client on fd: "<< newfd << endl;
                    
                    recv(newfd, &inputBuffer, 10, 0);
                    
                    if(inputBuffer[0] == '1'){
                        android(inputBuffer);
                    }
                    if (inputBuffer[0] == '0'){
                        esp();
                    }
                    
                    FD_SET(newfd, &master);
                    if (newfd > numberfd)
                        numberfd = newfd;
                    
                    break;
                }else{
                    int nbytes = 0;
                    if ((nbytes = recv(i, inputBuffer, sizeof(inputBuffer), 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    }else{
                        int z;
                        for(z = 0; z <= numberfd; z++){
                            if (z != listener && z != i){
                                send(z, inputBuffer, nbytes, 0);
                            }
                        }
                    }
                }
            }
        }
    }
}
