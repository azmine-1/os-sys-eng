#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int p){
  int prime; 
  if(read(p,&prime, sizeof(prime)) == 0){ 
    close(p); 
    exit(0);
  }
  printf("prime %d\n",prime); 
  
  int p1[2];
  pipe(p1);
  if(fork() == 0){
    close(p1[1]); 
    sieve(p1[0]); 
  } else {
    close(p1[0]); 
    int n; 
    while (read(p, &n, sizeof(n))) {
      if(n%prime != 0){
        write(p1[1], &n, sizeof(n)); 
      }
    }
    close(p);
    close(p1[1]); 
    wait(0); 
    exit(0);
  }

}

int main(int argc, char* argv[]) {
  int p1[2]; 
  pipe(p1); 
  

  if(fork() == 0){
    close(p1[1]); 
    sieve(p1[0]); 
  } else {
    close(p1[0]); 
    for(int i=2; i<=35; i++){
      write(p1[1],&i,sizeof(i));
    }
    close(p1[1]); 
    wait(0); 
    exit(0);
  }
}
