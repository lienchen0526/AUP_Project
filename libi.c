#include <dlfcn.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define ARGPARSE(...) __VA_ARGS__

#define WRAPPER(func_name, ret_type, args,              \
    argname, preprocess)                                \
    ret_type func_name(args) {                          \
        if(old_##func_name == NULL){                    \
            void *handle = dlopen("libc.so.6"           \
                , RTLD_LAZY);                           \
                                                        \
            if(handle != NULL){                         \
                old_##func_name = dlsym(handle,         \
                    #func_name);                   \
            } else {                                    \
                perror("Open libc.so.6 fail");          \
            }                                           \
        } else {}                                       \
        preprocess                                      \
        return old_##func_name(argname);                   \
    };

static bool initflag = false;

static DIR *(*old_opendir)(const char*) = NULL;

WRAPPER(opendir, DIR*, const char *name, 
    name, printf("hello world\n"););

/*
DIR *opendir(const char *name){
    if(old_opendir == NULL){
        void *handle = dlopen("libc.so.6", RTLD_LAZY);
        if(handle != NULL){
            old_opendir = dlsym(handle, "opendir");
        } else {
            perror("Open libc.so.6 fail");
        }
    } else {}
    printf("inject success\n");
    return old_opendir(name);
}
*/