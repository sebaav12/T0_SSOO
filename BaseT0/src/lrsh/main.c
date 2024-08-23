#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "../input_manager/manager.h"
#include "is_prime.h"
#include "lrlist.h"
#include "lrexit.h"

#define TRUE 1

void print_prompt() {
    printf("shell> ");
    fflush(stdout); // Asegura que el prompt se muestra inmediatamente
}

int main(int argc, char const *argv[]) {
    int status;

    while (TRUE) { 
        print_prompt();  
        char** input = read_user_input(); 

        if (input[0] == NULL) {  
            free_user_input(input);
            continue;
        }

        else if (strcmp(input[0], "exit") == 0 || strcmp(input[0], "lrexit") == 0) {  
            free_user_input(input);
            lrexit();
        }

        // Manejo de lrlist antes de la creación de procesos hijos
        if (strcmp(input[0], "lrlist") == 0) {
            lrlist();
            free_user_input(input);
            continue; // Volver al prompt sin crear un proceso hijo
        }

        if (strcmp(input[0], "lrexec") == 0) {
            if (input[1] == NULL) {
                printf("Error: Debes proporcionar el nombre del ejecutable.\n");
                free_user_input(input);
                continue;
            }

            // Crear un proceso hijo para lrexec
            pid_t pid = fork();

            if (pid == 0) {  // Proceso hijo
                if (execvp(input[1], &input[1]) == -1) {
                    perror("Error al ejecutar el programa");
                }
                exit(EXIT_FAILURE);  // En caso de error en execvp
            } else if (pid > 0) {  // Proceso padre (la shell)
                // Agregar el proceso a la lista
                add_process(pid, input[1]);
                waitpid(pid, &status, 0);  // Esperar a que el proceso hijo termine
                update_exit_code(pid, WEXITSTATUS(status));
            } else {
                perror("Error al crear el proceso");
            }
        } else {
            // Crear un proceso hijo para otros comandos
            pid_t pid = fork();

            if (pid == 0) {  // Proceso hijo
                // Hello World
                if (strcmp(input[0], "hello") == 0) {
                    printf("Hello World!\n");

                // Suma
                } else if (strcmp(input[0], "sum") == 0) {
                    if (input[1] != NULL && input[2] != NULL) {
                        double num1 = atof(input[1]);
                        double num2 = atof(input[2]);
                        printf("Resultado: %.2f\n", num1 + num2);
                    } else {
                        printf("Error: Debes proporcionar dos números para sumar.\n");
                    }

                // es primo
                } else if (strcmp(input[0], "is_prime") == 0) {
                    if (input[1] != NULL) {
                        int num = atoi(input[1]);  
                        if (is_prime(num)) {
                            printf("%d es un número primo.\n", num);
                        } else {
                            printf("%d no es un número primo.\n", num);
                        }
                    } else {
                        printf("Error: Debes proporcionar un número entero.\n");
                    }
                } else {
                    printf("Comando no reconocido: %s\n", input[0]);
                }
                free_user_input(input);
                exit(0);  
            } else if (pid > 0) {  // Proceso padre (la shell)
                waitpid(pid, &status, 0);  
                // No se agrega a la lista porque no fue ejecutado por lrexec
            }
        }

        free_user_input(input); 
    }

    return 0;
}
