#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char **argv){
    // for(int i = 0; i <= argc; ++i) printf("%s\n", argv[i]);
    // char **buf = (char**) malloc(64 * sizeof(char**));
    // for(int i = 0; i < argc; ++i){
    //     buf[i] = (char*) malloc(64 * sizeof(char*));
    //     int len = strlen(argv[i]);
    //     for(int j = 0; j < len; ++j){
    //         buf[i][j] = argv[i][j];
    //     }
    //     buf[i][len] = 0;
    // }
    // printf("---------\n");
    if(fork() == 0){
        exec("asdfasdf", argv + 1);
        printf("erro asdfas ar");
        exit(0);
    }else{
        wait(0);
    }
    // exec(buf[1], buf + 1);
    // printf("erro asdfas ar");
    // exit(0);
    // printf("echo Error\n");
    exit(-1);
}