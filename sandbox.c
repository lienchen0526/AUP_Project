#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

__attribute__((constructor)) void preload(){
    char full_so[256] = {0};
    if(realpath("./sandbox.so", full_so) == NULL){
        perror("realpath fail");
    }
    setenv("LD_PRELOAD", full_so, true); 
};

void invokehelp(){
    printf("usage: ./sandbox [-p sopath] [-d basedir] [--] cmd [cmd args ...]\n \
        -p: set the path to sandbox.so, default = ./sandbox.so\n \
        -d: the base directory that is allowed to access, default = .\n \
        --: seperate the arguments for sandbox and for the executed command\n");
}

size_t flatten_argv(int argc, char *argv[], 
    size_t start_point, char *dst_cmd){
    size_t lens = 0;
    size_t temp_indexer = 0;
    char *tail = dst_cmd;
    for(int i = start_point; i < argc; i++){
        while(argv[i][temp_indexer] != 0){
            dst_cmd[lens] = argv[i][temp_indexer];
            temp_indexer ++;
            lens ++;
        }
        dst_cmd[lens] = ' ';
        temp_indexer = 0;
        lens ++;
    }
    return lens;
}

unsigned char parse_args(int argc, char *argv[]){
    unsigned char arg_flag = 0;
    for(int i = 1; i < argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'p'){
                //sopath
                i++;
                arg_flag = arg_flag + (i * 10);
            } else if(argv[i][1] == 'd'){
                //basedir
                i++;
                arg_flag = arg_flag + i;
            } else if(argv[i][1] == 'h'){
                //invokehelp
                invokehelp();
                exit(0);
            } else {
                fprintf(stderr, "%s invalid option -- '%s'", 
                    argv[0], argv[i] + 1);
                invokehelp();
                exit(0);
            }
        }
    }
    return arg_flag;
}

int main(int argc, char *argv[]){
    
    bool complex = false;
    size_t arg_start = -1;
    unsigned char arg_flag = 0;
    char longcmd[256] = {0};
    pid_t pid;
    int pstatus = 0;

    //Looking for if -- exist
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--") == 0){
            complex = true;
            arg_start = i + 1;
        } else {};
    }
    if(complex){
        flatten_argv(argc, argv, arg_start, longcmd);
        argc -= (argc - arg_start + 1);
    } else {}
    arg_flag = parse_args(argc, argv);
    pid = fork();
    while(pid < 0){
        sleep(10);
        pid = fork();
    };
    if(pid == 0){
        //iamchild
        char full_so[256] = {0};
        char full_pwd[256] = {0};
        if((arg_flag / 10) % 10 != 0){
            if(realpath(argv[(arg_flag / 10) % 10], full_so) == NULL){
                perror("realpath() fail in sandbox on so");
            }
            printf("%s\n", full_so);
            setenv("LD_PRELOAD", full_so, true);
        }
        if(arg_flag % 10 != 0){
            if(realpath(argv[arg_flag % 10], full_pwd) == NULL){
                perror("realpath() fail in sandbox on pwd");
            }
            if(setenv("PWD", full_pwd, true) < 0){
                perror("setenv PWD error");
            }
            if(chdir(full_pwd) < 0){
                perror("chdir fail");
            }
        }
        //printf("current pwd: %s\n", getenv("PWD"));
        execvp(argv[arg_start], argv + arg_start);
        exit(0);
    } else{
        //iamparent
        wait(&pstatus);
    }
    return 0;
}