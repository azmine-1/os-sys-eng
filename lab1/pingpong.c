#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
  int p1[2]; 
  int p2[2]; 
  char buf[10];
  pipe(p1);
  pipe(p2);
  int pid = fork(); 

  if (pid == 0){
    close(p1[1]);
    close(p2[0]); 
    read(p1[0],buf,1);
    if(buf[0] == 'i'){
      printf("%d: received ping\n",getpid());
    }
    write(p2[1],"o",1);
    close(p1[0]);
    close(p2[1]);
  }
  if(pid > 0){
    close(p1[0]);
    close(p2[1]);
    write(p1[1],"i",1);
    read(p2[0],buf,1);
    if(buf[0] == 'o'){
      printf("%d: received pong\n",getpid());
    }
    close(p1[1]);
    close(p2[0]);
  }
  exit(0);
}
