#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// #include "user/ulib.c"

int main(int argc, char *argv[]){
    if(argc != 2){
        write(1, "Error!\n", 6);
        exit(-1);
    }else{
        int time = atoi(argv[1]);
        // write(1, "init\n", 5);
        // write(1, argv[1], strlen(argv[1]));
        if(time <= 0){
            write(1, "Error!\n", 6);
            exit(-1);
        }
        sleep(time);
    }
    exit(0);
}