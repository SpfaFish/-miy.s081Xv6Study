
// #include <string.h>

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char* cut(char *buf){
    static char s[64];
    memset(s, 0, sizeof s);
    int len = strlen(buf);
    int i;
    for(i = len - 1; i >= 0 && buf[i] != '/'; --i);
    ++i;
    for(int n = 0; i < len; ++i, ++n) s[n] = buf[i];
    return s;
}
void find(char *path, char *aim){
    int fd;
    struct dirent de;
    struct stat st;
    char *p;
    if((fd = open(path, O_RDONLY)) < 0){
        fprintf(2, "Find: cannot enter %s\n", path);
        close(fd);
        return;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "Find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch(st.type){
    case T_DEVICE:
    case T_FILE:
        if(strcmp(cut(path), aim) == 0){
            printf("%s %d %d %l\n", path, st.type, st.ino, st.size);
            return;
        }
        break;
    case T_DIR:
        if(strlen(path) + 1 + DIRSIZ + 1 > 512){
            printf("Find: path too long\n");
            break;
        }
        p = path + strlen(path);
        *p++ = '/';
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0) continue;
            if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(path, &st) < 0){
                printf("Find: cannot stat %s\n", path);
                continue;
            }
            switch(st.type){
            case T_DEVICE:
            case T_FILE:
                // printf("%s\n", cut(path));
                if(strcmp(cut(path), aim) == 0){
                    printf("%s %d %d %l\n", path, st.type, st.ino, st.size);
                    continue;
                }
                break;
            case T_DIR:
                find(path, aim);
                break;
            }
        }
        break;
    }

}
int main(int argc, char *argv[]){
    char path[512];
    memset(path, 0, sizeof path);
    path[0] = '.';
    // printf("%s\n", path);
    if(argc < 1){
        fprintf(2, "Too few argument\n");
    }else{
        for(int i = 1; i < argc; ++i){
            if(strlen(argv[i]) > 512){
                fprintf(2, "Too Long argument\n");
                exit(-1);
            }
            find(path, argv[i]);
        }
    }
    exit(0);
}