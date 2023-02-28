#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define NULL 0
void turn(int a, char *s){
    int len = 0;
    int x = a;
    do{
        ++len;
    }while(x /= 10);
    s[len] = NULL;
    for(int i = len - 1; i >= 0; --i){
        s[i] = a % 10 + '0';
        a /= 10;
    }
}
int main(int argc, char *argv[]){
    int p[2];
    char buf[64];
    char num[64];
    pipe(p);
    if(fork() == 0){
        read(p[0], buf, sizeof buf);
        int id = getpid();
        turn(id, num);
        write(1, num, strlen(num));
        write(1, ": ", 2);
        write(1, "receved ", 8);
        write(1, buf, strlen(buf));
        write(1, "\n", 1);
        exit(0);
    }else{
        int id = getpid();
        turn(id, num);
        write(1, num, strlen(num));
        write(1, ": ", 2);
        write(1, "receved ping\n", 13);
        write(p[1], "pong", 4);
        wait(0);
        close(p[0]);
        close(p[1]);
        exit(0);
    }
}