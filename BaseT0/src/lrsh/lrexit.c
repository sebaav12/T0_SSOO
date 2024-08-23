#include "lrexit.h"
#include "lrlist.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>  // exit()
#include <stdio.h>

// funcion para enviar una señal a los procesos
void send_signal_to_all(int signal) {
    ProcessInfo *current = process_list;
    while (current != NULL) {
        kill(current->pid, signal);
        current = current->next;
    }
}

// Función para terminar la ejecución de la shell (lrexit)
void lrexit() {
    send_signal_to_all(SIGINT);
    sleep(10);  // esperar a que los procesos terminen, timer 10 s

    // iterar y matar procesos con SIGKILL
    ProcessInfo *current = process_list;
    while (current != NULL) {
        int status;
        pid_t result = waitpid(current->pid, &status, WNOHANG);
        if (result == 0) {  // El proceso sigue activo
            kill(current->pid, SIGKILL);
        }
        current = current->next;
    }
    // salir de la shell
    exit(0);
}
