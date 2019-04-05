#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <time.h>
void func(void*arg);
void error_handling(char *message);

struct address{
  char * host;
  int port;
  char * msg;
};
  
int main(int argc, char *argv[], char *envp[]){
  int i,err;
  void *tret;

  if( argc < 5){
    printf("usage:bin host port thread_num msg-to-server, for example:your-bin 127.0.0.1 8888 4 your-message\n\r");
    return -1;
  }
  
  struct address addr;
  addr.host = argv[1];
  addr.port = atoi(argv[2]);
  addr.msg = argv[4];
  int thread_num = atoi(argv[3]);  
  pthread_t thread[thread_num];

  for(i = 0; i < thread_num; i++){
    printf("i:%d\n\r",i);
    err = pthread_create(&thread[i], NULL, (void *)&func, (void *)&addr);
    if (err != 0)
      printf("can't create thread %d: %s\n",i, strerror(err));
  }

  for(i = 0; i < thread_num; i++){
    err = pthread_join(thread[i], &tret);  
    if (err != 0)  
      printf("can't join with thread %d: %s\n",i, strerror(err));  
  }
  return 0;
}

void func(void *arg){
  struct address * addr = (struct address*) arg;
  int sock;
  struct sockaddr_in serv_addr;
  char message[300];
  int err,str_len;
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [128];
  printf("host:%s, port:%d, msg:%s\n\r",addr->host,addr->port,addr->msg);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  // pthread_key_t key;
  // pthread_setspecific(key,(void *)sock);   
  if (sock == -1){
    printf("err:%s",strerror(errno));
    error_handling("create sock() error");
  }
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(addr->host);
  serv_addr.sin_port = htons(addr->port);
  err = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  if ( err != 0){
    // error_handling("connect() error!");
    printf("connect err %s\n",strerror(errno));
    exit(1);
  }
  while(1){
    sleep(1);
    //    int sock = pthread_getspecific(key);
    str_len = send(sock, addr->msg, 300, 0);
    if (str_len == -1){
      time (&rawtime);
      timeinfo = localtime (&rawtime);
      strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S ",timeinfo);
      printf("%s", buffer);
      
      printf("client %ld,write err:%s\n",pthread_self(),strerror(errno));
      // error_handling("read() error!");
      //perror(NULL);

      //          printf("err:%s",strerror(errno));
      //        error_handling("write() error!");
      break;
    }

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1){
      time (&rawtime);
      timeinfo = localtime (&rawtime);
      strftime (buffer,sizeof(buffer),"%Y/%m/%d %H:%M:%S ",timeinfo);
      printf("%s", buffer);
      
      printf("client %ld,read err:%s\n",pthread_self(),strerror(errno));
      // error_handling("read() error!");
      //perror(NULL);
      break;
    }
    // message[str_len]=0x0;
    // printf(" client %ld, Message from server: %s\n",pthread_self(), message);
  }
}


void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
