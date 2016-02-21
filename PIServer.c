#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

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

void recieve (int clientfd, char* recivedData){
    int recv_count;
    recv_count = recv(clientfd, recivedData, 99, 0);

    printf("the recv_count in recieve: %d\n", recv_count);
};

char client1buffer[99];

// fills the passed in buffer with the current date and time
void getTime(char* buffer){
	time_t curtime;
	struct tm* loctime;
	char localBuffer[99];

	//get the current time
	curtime = time(NULL);
	
	//convert curtime to localtime
	loctime = localtime(&curtime);

	//fill the localbuffer
	asctime_r(loctime, &localBuffer);

	//copy localBuffer to passed in buffer
	memmove(buffer, &localBuffer, 23);
}


int main(){

	char buffer[] = "show tables";
	access_database(buffer);

	char timeBuffer[30];
	getTime(timeBuffer);
	printf("this is the time: %s\n", timeBuffer);
    
    int mainSocket = setUpServer();
    int client1fd = acceptClient(mainSocket);

    int server = 1;
    int i;

    while (server){
        recieve(client1fd, client1buffer);

	for (i= 0; i<20; i++){
		printf("%c", client1buffer[i]);
	}
        send(client1fd, client1buffer,99, 0);
	server = 0;
    }
}
