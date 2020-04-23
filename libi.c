#include <dlfcn.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#define ARGAGG(...) __VA_ARGS__

#define WRAPPER(func_name, ret_type, args,              \
    argname, argtype, preprocess)                       \
    static ret_type (*old_##func_name)(argtype) = NULL; \
    ret_type func_name(args) {                          \
        if(old_##func_name == NULL){                    \
            void *handle = dlopen("libc.so.6"           \
                , RTLD_LAZY);                           \
                                                        \
            if(handle != NULL){                         \
                old_##func_name = dlsym(handle,         \
                    #func_name);                        \
            } else {                                    \
                perror("Open libc.so.6 fail");          \
            }                                           \
        } else {}                                       \
        preprocess                                      \
        return old_##func_name(argname);                \
    };

WRAPPER(opendir, DIR*, 
    ARGAGG(const char *name), 
    ARGAGG(name), 
    ARGAGG(const char*), 
    printf("hello worlds\n");
    );

//untest yet
WRAPPER(chmod, int, 
    ARGAGG(const char *pathname, mode_t mode), 
    ARGAGG(pathname, mode), 
    ARGAGG(const char*, mode_t),
    printf("hello this is chmod\n");
    );

WRAPPER(readdir, struct dirent*, 
    ARGAGG(DIR *dirp),
    ARGAGG(dirp), 
    ARGAGG(DIR*),
    printf("this is readdir\n");
    );

WRAPPER(chdir, int, 
    ARGAGG(const char *path),
    ARGAGG(path),
    ARGAGG(const char*),
    printf("this is chdir\n");
    );
WRAPPER(chown, int,
    ARGAGG(const char *pathname, uid_t owner, gid_t group),
    ARGAGG(pathname, owner, group),
    ARGAGG(const char*, uid_t, gid_t),
    printf("This is chown\n");
    );
WRAPPER(creat, int,
    ARGAGG(const char *pathname, mode_t mode),
    ARGAGG(pathname, mode),
    ARGAGG(const char*, mode_t),
    printf("This is creat\n");
    );
WRAPPER(fopen, FILE*,
    ARGAGG(const char *pathname, const char *mode),
    ARGAGG(pathname, mode),
    ARGAGG(const char*, const char*),
    printf("This is fopen\n");
    );
WRAPPER(link, int,
    ARGAGG(const char *oldpath, const char *newpath),
    ARGAGG(oldpath, newpath),
    ARGAGG(const char*, const char*),
    printf("This is link\n");
    );

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