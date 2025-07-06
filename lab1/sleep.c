#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if (argc < 2){

        exit(-1);    
    }
    int int_argv = atoi(argv[1]);
    sleep(int_argv);
    exit(0);

}