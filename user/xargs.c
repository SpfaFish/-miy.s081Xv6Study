// #include <stdlib.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"


int main(int argc, char *argv[]){
    // printf("%d\n", argc);
    // for(int i = 0; i < argc; ++i){
    //     printf("%s\n", argv[i]);
    // }
    if(argc < 2){
        printf("Wrong arguments\n");
        exit(-1);
    }
    int n = 32;
    if(strcmp(argv[1], "-n") == 0){
        n = atoi(argv[2]);
    }
    if(n <= 0 || n > MAXARG){
        printf("Wrong arguments\n");
        exit(-1);
    }
    char buf[512], commandBuf[512];
    // printf("%d\n", n + (argc - (n == 32 ? 1 : 3)) + 1);
    // printf("%d\n", n);
    int len = 0;
    char *p = buf;
    while(read(0, p++, 1) > 0){
        ++len;
    }
    if(len <= 0){
        printf("Wrong input\n");
        exit(-1);
    }else if(len == sizeof buf){
        printf("Too many input!\n");
        exit(-1);
    }
    // int top = n + (argc - (n == 32 ? 1 : 3)) + 1;
    // top = 32;
    char *commandLine[32];
    int st = 0;
    for(int i = (n == 32 ? 0 : 3); i < argc; ++i) commandLine[st++] = argv[i];
    // for(int i = st; i < top; ++i) commandBuf[i] = (char*) malloc(64 * sizeof(char));
    // memset(commandBuf[st], 0, 64 * sizeof(char));
    commandLine[st] = p = commandBuf;
    int cnt = st;
    // printf("%d next\n", len);
    // printf("%s|||\n", buf);
    // printf("st: %d\n", st);
    for(int i = 0; i < len; ++i){
        // printf("%d %d %c\n", i, cnt, buf[i]);
        if(buf[i] == '\\' || (buf[i] == '\\' && i < len - 1 && buf[i + 1] == 'n')
            || buf[i] == ' ' || (buf[i] == 'n' && i && buf[i - 1] == '\\') || buf[i] == '"' || buf[i] == '\'' || i == len - 1){
            // printf("in this\n");
            if(p != commandLine[cnt]){
                *p = 0;
                // memset(commandBuf[++cnt], 0x00, 64 * sizeof(char));
                // p = commandBuf[cnt];
                // ++p;
                commandLine[++cnt] = ++p;
            }
        }else{
            // printf("in that\n");
            *p++ = buf[i];
        }
        if(cnt == st + n || i == len - 1){
            if(cnt - 1 > 32){
                printf("too many arguments\n");
                exit(-1);
            }
            if(cnt == 1) continue;
            // printf("command\n");
            *p = 0;
            // for(int j = 0; j <= cnt; ++j){//output
                // printf("%s\n", commandLine[j]);
            // }
            printf("%s: ", commandLine[0]);
            if(fork() == 0){
                // printf("in fork\n");
                // for(int j = 0; j <= cnt; ++j){//output
                //     printf("%d %s\n", strlen(commandLine[j]), commandLine[j]);
                // }
                int rt = exec(commandLine[0], commandLine);
                printf("%d exec Error\n", rt);
                exit(-1);
                // exit(0);
            }else{
                wait(0);
            }
            // memset(commandBuf[cnt = st], 0, 64 * sizeof(char));
            commandLine[cnt = st] = p;
        }
    }
    // exec(argv[0], argv);
    exit(0);
}