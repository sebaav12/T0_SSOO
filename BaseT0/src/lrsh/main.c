
// #include <stdio.h>
// #include <stdlib.h>
// #include "../input_manager/manager.h"

// int main(int argc, char const *argv[])
// {
//   char** input = read_user_input();
//   printf("%s\n", input[0]);
//   free_user_input(input);
// }

// syscal usadas: fork(), wait(), exit()

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../input_manager/manager.h"
#include "is_prime.h"

#define TRUE 1

int main(int argc, char const *argv[]) {
    int status;

    while (TRUE) { 
        // Mostrar el prompt

        printf("shell> ");  
        char** input = read_user_input(); 

        if (input[0] == NULL) {  
            free_user_input(input);
            continue;
        }

        else if (strcmp(input[0], "exit") == 0) {  
            free_user_input(input);
            break;
        }

        pid_t pid = fork();  

        // Este caso esta pensado para casos en que el proceso hijo no se puedo crear
        if (pid == 0) {  

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
                    // Convertir el input a un entero
                    int num = atoi(input[1]);  
                    if (is_prime(num)) {
                        printf("%d es un número primo.\n", num);
                    } else {
                        printf("%d no es un número primo.\n", num);
                    }
                } else {
                    printf("Error: Debes proporcionar un número entero.\n");
                }

            // Lrexec    

            } else if (strcmp(input[0], "lrexec") == 0){

                // entiendo que al hacer esto no se deberia congelar la shell, onda este otro fork
                
                pid_t pid = fork();
                if (pid == 0) {  
                    if (execvp(input[1], &input[1]) == -1) {
                        perror("Error al ejecutar el programa");
                    }
                    exit(EXIT_FAILURE);  
                } else if (pid > 0) {  // Proceso padre
                    // esto esta para esperar a que el hijo termine, pero no se si es necesario
                    // quizas estoy congelando la sehll
                    wait(NULL);  
                } else {
                    perror("Error al crear el proceso");
                }
                
            } else {
                printf("Comando no reconocido: %s\n", input[0]);
            }
            free_user_input(input);
            // Terminar el proceso hijo
            exit(0);  
            
        } else if (pid > 0) {  // Proceso padre (la shell)
            // Esperar a que el proceso hijo termine
            wait(&status);  
        }

        // Liberar la memoria de la entrada del usuario
        free_user_input(input); 
    }

    return 0;
}


