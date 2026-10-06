#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

void echo(int fd){
  char buff[100];
  for (;;){
    ssize_t n=recv(fd,buff,strlen(buff),0);
    ssize_t tbs=0;
    while (tbs<n){
      ssize_t k=send(fd,buff+tbs,strlen(buff)-tbs,0);
      tbs+=k;
    }
  }
}

int main(){
  int sockfd;
  struct sockaddr_in servaddr={0};
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
  servaddr.sin_port=htons(3000);
  bind(sockfd,(struct sockaddr*)& servaddr, sizeof(servaddr));
  listen(sockfd,5);
  for (;;){
    int confd=accept(sockfd,NULL,NULL);
    echo(confd);
    close(confd);
  }
}

