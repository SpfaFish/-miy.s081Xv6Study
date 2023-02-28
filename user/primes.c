#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define NULL 0
#define sizeof(int) 4

int ssqrt(int x){//myself's math func
    int l = 0, r = x;
    while(l < r){
        int mid = (l + r) >> 1;
        if(mid * mid <= x) l = mid + 1;
        else r = mid;
    }
    return l - 1;
}
#define true 1
#define false 0
int isPrime(int x){
    int len = ssqrt(x);
    // printf("len: %d, X: %d", len, x);
    for(int i = 2; i <= len; ++i){
        if(x % i == 0) return false;
    }
    return true;
}
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

void printInt(int x){//used for debug, could replaced by printf
    char buf[64];
    turn(x, buf);
    write(1, buf, sizeof buf);
    write(1, "\n", 1);
}
int main(){
    int num[64];
    char buf[64];
    for(int i = 2; i <= 35; ++i){
        if(isPrime(i)){
            // printf("%d\n", i);
            turn(i, buf);
            int p[2];
            pipe(p);
            if(fork() == 0){
                read(p[0], num, sizeof(int));
                close(p[0]);
                turn(num[0], buf);
                write(1, "Prime: ", 7);
                write(1, buf, strlen(buf));
                write(1, "\n", 1);
                exit(0);
            }else{
                write(p[1], &i, sizeof(int));
                close(p[1]);
                wait(0);
            }
        }
    }
   
    exit(0);
}