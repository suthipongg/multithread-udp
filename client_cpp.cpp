#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iomanip>
#include <stdint.h>

#define PORT     8080
unsigned int microsecond = 1000000;

// Driver code
int main(int argc, char* argv[]) {
    std::string BUFF (argv[1]);
    int BUFF_SIZE = stoi(BUFF);
    std::string second (argv[2]);
    int sec {stoi(second)}; 

    uint8_t input[13] {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x30,0x31,0x30,0x31};
    size_t byte_array_len = sizeof(input);
    uint8_t* byte_array = reinterpret_cast<uint8_t*>(input);
    
    int sockfd;
    char buffer[BUFF_SIZE];
    struct sockaddr_in servaddr;
   
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
       
    int n;
    socklen_t len;

    while (1) {   
        sendto(sockfd, byte_array, byte_array_len,
                MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
                sizeof(servaddr));

        printf("client sent message : ");
        for (size_t i=0; i<byte_array_len; i++) {
            printf("%d ", *(byte_array+i));
        }
        std::cout << std::endl;
            
        n = recvfrom(sockfd, buffer, BUFF_SIZE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';

        std::cout<<"Server : \" "<<buffer<< " \"" << std::endl;
        std::cout<<"========================================"<<std::endl;
        std::cout<<std::endl;

        usleep(sec * microsecond);
    }

    close(sockfd);
    return 0;
}