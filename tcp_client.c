#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
  int sockfd;
  struct sockaddr_in servaddr;
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(3000);
  inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
  connect(sockfd, (struct sockaddr*)& servaddr, sizeof(servaddr)); 
  char buff[100]="Hello from Client";
  size_t sent=0;
  while (sent<strlen(buff)){
    ssize_t k=send(sockfd, buff+sent, strlen(buff)-sent, MSG_NOSIGNAL);
    sent+=k;
  }
  size_t recd=0;
  while (recd<strlen(buff)){
    ssize_t k=recv(sockfd, buff+recd, strlen(buff)-recd,0);
    recd+=k;
  }
  buff[recd]='\0';
  printf("server echoed - %s\n",buff);
  close(sockfd);
}
