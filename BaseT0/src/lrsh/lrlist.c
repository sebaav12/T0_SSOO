#include "lrlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

ProcessInfo *process_list = NULL;

// agregar un proceso a la lista
void add_process(pid_t pid, char *name) {
    ProcessInfo *new_process = malloc(sizeof(ProcessInfo));
    new_process->pid = pid;
    strcpy(new_process->name, name);
    new_process->start_time = time(NULL);
    new_process->exit_code = -1;
    new_process->next = process_list;
    process_list = new_process;
}

// actualizar el exit code
void update_exit_code(pid_t pid, int exit_code) {
    ProcessInfo *current = process_list;
    while (current != NULL) {
        if (current->pid == pid) {
            current->exit_code = exit_code;
            break;
        }
        current = current->next;
    }
}

// print de lrlist final
void lrlist() {
    ProcessInfo *current = process_list;
    printf("PID\tNombre\t\tTiempo\t\tExit Code\n");
    while (current != NULL) {
        time_t elapsed_time = time(NULL) - current->start_time;
        printf("%d\t%s\t\t%ld segundos\t%d\n", current->pid, current->name, elapsed_time, current->exit_code);
        current = current->next;
    }
}
