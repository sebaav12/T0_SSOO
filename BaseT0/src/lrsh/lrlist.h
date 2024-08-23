#ifndef LRLIST_H
#define LRLIST_H

#include <time.h>
#include <sys/types.h>

// struct para almacenar la info de los procesos
typedef struct ProcessInfo {
    pid_t pid;
    char name[256];
    time_t start_time;
    int exit_code;
    struct ProcessInfo *next;
} ProcessInfo;

// variable global de informacion (extern para eso)
extern ProcessInfo *process_list;

// funciones de lrlist
void add_process(pid_t pid, char *name);
void update_exit_code(pid_t pid, int exit_code);
void lrlist(void);

#endif
