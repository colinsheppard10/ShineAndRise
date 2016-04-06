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
//#include <header.h>

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

char getDigit(char* input){
    if((input[0] == 'M') && (input[1] == 'o') && (input[2] == 'n'))
        return '1';
    if((input[0] == 'T') && (input[1] == 'u') && (input[2] == 'e'))
        return '2';
    if((input[0] == 'W') && (input[1] == 'e') && (input[2] == 'd'))
        return '3';
    if((input[0] == 'T') && (input[1] == 'h') && (input[2] == 'u'))
        return '4';
    if((input[0] == 'F') && (input[1] == 'r') && (input[2] == 'i'))
        return '5';
    if((input[0] == 'S') && (input[1] == 'a') && (input[2] == 't'))
        return '6';
    if((input[0] == 'S') && (input[1] == 'u') && (input[2] == 'n'))
        return '7';
    else
        return '0';
}

void android(char* input){
    
    cout << "found android" << endl;
    cout << input << endl;
    char buffer[62] ={0};
    char dbBuffer[10] = {0};
    char digit;
    
    if (input[1] == '2'){
        char *secondHalfO = "',1);";
        getTime(input);
        digit = getDigit(input);
        memset(input, digit, 1);
        memmove(input + 1, input + 11, 2);
        memmove(input + 3, input + 14, 2);
        memmove(input + 5, input + 17, 2);
        
        strcpy(buffer, "INSERT INTO subjects (menu_name, visible) VALUE('");
        
        memmove(buffer+49, input, 7);
        memmove(buffer+56, secondHalfO, 5);
    }
    else if (input[1] == '3'){
        char *secondHalfO = "',2);";
        getTime(input);
        digit = getDigit(input);
        memset(input, digit, 1);
        memmove(input + 1, input + 11, 2);
        memmove(input + 3, input + 14, 2);
        memmove(input + 5, input + 17, 2);
        
        strcpy(buffer, "INSERT INTO subjects (menu_name, visible) VALUE('");
        
        memmove(buffer+49, input, 7);
        memmove(buffer+56, secondHalfO, 5);
        
        
    }
    else {
        strcpy(buffer, "INSERT INTO subjects (menu_name, visible) VALUE('");
        char *secondHalf = "',0);";
        
        input++;
        
        digit = getDigit(input);
        cout << digit << endl;
        
        strcat(buffer, &digit);
        memmove(&buffer[50], input+4, 2);
        memmove(buffer+52, input + 7, 2);
        memmove(buffer+54, "00", 2);
        strcat(buffer, secondHalf);
        
        
    }
    
    cout << "from android finished: "<< buffer << endl;
    //    access_database(buffer,dbBuffer);
    
}

char getMonthDigit(char* time){
    
    if (time[4] == 'A')
        return '4';
    return '5';
}
void esp(char* dbBuffer){
    cout << "found esp from TCP select" << endl;
    
    char buffer[24] = {0};
    char digit;
    char queryBuffer[150] = {0};
    char responseTime[20] = {0};
    getTime(buffer);
    
    memmove(responseTime, buffer + 11, 2);
    memmove(responseTime + 2, buffer + 14, 2);
    memmove(responseTime + 4, buffer + 17, 2);
    memmove(responseTime + 6, buffer + 8, 2);
    if (responseTime[6] == ' '){
        responseTime[6] = '0';
    }
    memset(responseTime + 8, '0', 1);
    memset(responseTime + 9, getMonthDigit(buffer), 1);
    memmove(responseTime + 10, buffer + 20, 4);
    cout << responseTime << endl;
    
    
    digit = getDigit(buffer);
    memset(buffer, digit, 1);
    memmove(buffer + 1, buffer + 11, 2);
    memmove(buffer + 3, buffer + 14, 2);
    memmove(buffer + 5, buffer + 17, 2);
    memmove(buffer + 7, "\0", 1);
    
    strcpy(queryBuffer, "SELECT * FROM subjects WHERE menu_name = (SELECT MIN(menu_name) from subjects where menu_name > (");
    char *secondHalf = " - 3));";
    
    strcat(queryBuffer, buffer);
    strcat(queryBuffer, secondHalf);
    cout <<"prepared query from esp(): " << queryBuffer << endl;
    //   access_database(queryBuffer, dbBuffer);
    memmove(dbBuffer, "020201", 6);
    strcat(responseTime, dbBuffer);
    memmove(dbBuffer, responseTime, 20);
    memmove(dbBuffer +20, "\0", 1);
    cout <<"dbBuffer from esp(): " << dbBuffer << endl << endl;
    
}

int main(){
    
    fd_set tempSet;
    fd_set master;
    int listener;
    char timeBuffer[30];
    char inputBuffer[99] = {0};
    char espBuffer[21] = {0};
    
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
                        esp(espBuffer);
                        // this is where I am sending the string to the ESP
                        send(newfd, espBuffer, 21, 0);
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
                    }
                }
            }
        }
    }
}




