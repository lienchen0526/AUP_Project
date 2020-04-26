#include <dlfcn.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
//#include <sys/stat.h>

#define ARGAGG(...) __VA_ARGS__

#define WRAPPER(func_name, ret_type, args,                      \
    argname, argtype, preprocess)                               \
    static ret_type (*old_##func_name)(argtype) = NULL;         \
    ret_type func_name(args) {                                  \
        if(old_##func_name == NULL){                            \
            void *handle = dlopen("libc.so.6"                   \
                , RTLD_LAZY);                                   \
                                                                \
            if(handle != NULL){                                 \
                *(void**) &(old_##func_name) = dlsym(handle,    \
                    #func_name);                                \
            } else {                                            \
                perror("Open libc.so.6 fail");                  \
            }                                                   \
        } else {}                                               \
        preprocess                                              \
        return old_##func_name(argname);                        \
    };

bool permission(const char *target_path){
    size_t path_len = 0;
    char mutable_target_path[256] = {0};
    char cwd[PATH_MAX];
    char target_resolved_path[PATH_MAX];
    if(strcpy(mutable_target_path, target_path) == NULL){
        fprintf(stderr,"strcpy fail with %s\n", target_path);
    };
    while(mutable_target_path[path_len] != 0){
        path_len += 1;
    }

    while(realpath(mutable_target_path, 
        target_resolved_path) == NULL){
        while(path_len > 0 && mutable_target_path[path_len] != '/'){
            mutable_target_path[path_len] = 0;
            path_len --;
        }
        if(path_len != 0){
            mutable_target_path[path_len] = 0;
            path_len --;
        } else {}
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        if(strncmp(target_resolved_path, cwd, strlen(cwd)) == 0){
            return true;
        } else {
            if(getenv("PRIV") == NULL){
                return false;
            } else {
                return true;
            }
        }
    } else {
        perror("getcwd() error");
        return true;
    }
}

void print_deny(const char *function_name,
    const char* pathname){
        fprintf(stderr, "[sandbox] %s: access to %s is not allowed\n",
            function_name, pathname);
}
extern "C"{
WRAPPER(opendir, DIR*, 
    ARGAGG(const char *name), 
    ARGAGG(name), 
    ARGAGG(const char*), 
    if(!permission(name)){
        print_deny("opendir", name);
        return NULL;
    } else {};
    );

WRAPPER(chmod, int, 
    ARGAGG(const char *pathname, mode_t mode), 
    ARGAGG(pathname, mode), 
    ARGAGG(const char*, mode_t),
    if(!permission(pathname)){
        print_deny("chmod", pathname);
        return -1;
    } else {};
    );


WRAPPER(chdir, int, 
    ARGAGG(const char *path),
    ARGAGG(path),
    ARGAGG(const char*),
    if(!permission(path)){
        print_deny("chdir", path);
        return -1;
    } else {};
    );
WRAPPER(chown, int,
    ARGAGG(const char *pathname, uid_t owner, gid_t group),
    ARGAGG(pathname, owner, group),
    ARGAGG(const char*, uid_t, gid_t),
    if(!permission(pathname)){
        print_deny("chown", pathname);
        return -1;
    } else {};
    );

WRAPPER(open, int,
    ARGAGG(const char *pathname, int flags),
    ARGAGG(pathname, flags),
    ARGAGG(const char*, int),
    if(!permission(pathname)){
        print_deny("open", pathname);
        return -1;
    } else {};
    );

WRAPPER(creat, int,
    ARGAGG(const char *pathname, mode_t mode),
    ARGAGG(pathname, mode),
    ARGAGG(const char*, mode_t),
    if(!permission(pathname)){
        print_deny("creat", pathname);
        return -1;
    } else {};
    );
WRAPPER(openat, int,
    ARGAGG(int dirfd, const char *pathname, int flags),
    ARGAGG(dirfd, pathname, flags),
    ARGAGG(int, const char*, int),
    if(!permission(pathname)){
        print_deny("openat", pathname);
        return -1;
    } else {};
    );

WRAPPER(__xstat, int,
    ARGAGG(const char *pathname, struct stat *statbuf),
    ARGAGG(pathname, statbuf),
    ARGAGG(const char*, struct stat*),
    if(!permission(pathname)){
        print_deny("stat", pathname);
        return -1;
    } else {};
    );
WRAPPER(fopen, FILE*,
    ARGAGG(const char *pathname, const char *mode),
    ARGAGG(pathname, mode),
    ARGAGG(const char*, const char*),
    if(!permission(pathname)){
        print_deny("creat", pathname);
        return NULL;
    } else {};
    );
WRAPPER(link, int,
    ARGAGG(const char *oldpath, const char *newpath),
    ARGAGG(oldpath, newpath),
    ARGAGG(const char*, const char*),
    if(!permission(oldpath)){
        print_deny("link", oldpath);
        return -1;
    } else {};
    if(!permission(newpath)){
        print_deny("link", newpath);
        return -1;
    } else {};
    );
WRAPPER(mkdir, int,
    ARGAGG(const char *pathname, mode_t mode),
    ARGAGG(pathname, mode),
    ARGAGG(const char*, mode_t),
    if(!permission(pathname)){
        print_deny("mkdir", pathname);
        return -1;
    } else {};
    );
WRAPPER(readlink, ssize_t,
    ARGAGG(const char *pathname, char *buf, size_t bufsiz),
    ARGAGG(pathname, buf, bufsiz),
    ARGAGG(const char*, char*, size_t),
    if(!permission(pathname)){
        print_deny("readlink", pathname);
        return -1;
    } else {};
    );
WRAPPER(remove, int,
    ARGAGG(const char *pathname),
    ARGAGG(pathname),
    ARGAGG(const char*),
    if(!permission(pathname)){
        print_deny("remove", pathname);
        return -1;
    } else {};
    );
WRAPPER(rename, int,
    ARGAGG(const char *oldpath, const char *newpath),
    ARGAGG(oldpath, newpath),
    ARGAGG(const char*, const char*),
    if(!permission(oldpath)){
        print_deny("rename", oldpath);
        return -1;
    } else {};
    if(!permission(newpath)){
        print_deny("rename", newpath);
        return -1;
    } else {};
    );
WRAPPER(rmdir, int,
    ARGAGG(const char *pathname),
    ARGAGG(pathname),
    ARGAGG(const char*),
    if(!permission(pathname)){
        print_deny("rmdir", pathname);
        return -1;
    } else {};
    );


WRAPPER(symlink, int,
    ARGAGG(const char *target, const char *linkpath),
    ARGAGG(target, linkpath),
    ARGAGG(const char*, const char*),
    if(!permission(target)){
        print_deny("symlink", target);
        return -1;
    } else {};
    if(!permission(linkpath)){
        print_deny("symlink", linkpath);
        return -1;
    } else {};
    );
WRAPPER(unlink, int,
    ARGAGG(const char *pathname),
    ARGAGG(pathname),
    ARGAGG(const char*),
    if(!permission(pathname)){
        print_deny("unlink", pathname);
        return -1;
    } else {};
    );

WRAPPER(execl, int,
    ARGAGG(const char *path, const char *arg, ...),
    ARGAGG(path, arg),
    ARGAGG(const char *, const char *),
    printf("[sandbox] execl(%s): not allowed\n", path);
    return -1;
    );

WRAPPER(execve, int,
    ARGAGG(const char *filename, char *const argv[],
                  char *const envp[]),
    ARGAGG(filename, *argv, *envp),
    ARGAGG(const char *, char *const, char *const),
    printf("[sandbox] execve(%s): not allowed\n", filename);
    return -1;
    );

WRAPPER(execle, int,
    ARGAGG(const char *path, const char *arg, ...),
    ARGAGG(path, arg),
    ARGAGG(const char*, const char*),
    printf("[sandbox] execle(%s): not allowed\n", path);
    return -1;
    );

WRAPPER(execlp, int,
    ARGAGG(const char *file, const char *arg, ...),
    ARGAGG(file, arg),
    ARGAGG(const char*, const char*),
    printf("[sandbox] execlp(%s): not allowed\n", file);
    return -1;
    );

WRAPPER(execv, int,
    ARGAGG(const char *path, char *const argv[]),
    ARGAGG(path, *argv),
    ARGAGG(const char*, char *const),
    printf("[sandbox] execv(%s): not allowed\n", path);
    return -1;
    );
WRAPPER(execvp, int,
    ARGAGG(const char *file, char *const argv[]),
    ARGAGG(file, *argv),
    ARGAGG(const char*, char *const),
    printf("[sandbox] execvp(%s): not allowed\n", file);
    return -1;
    );

WRAPPER(system, int,
    ARGAGG(const char *command),
    ARGAGG(command),
    ARGAGG(const char*),
    printf("[sandbox] system(%s): not allowed\n", command);
    return -1;
    );
}