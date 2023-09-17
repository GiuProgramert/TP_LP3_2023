#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

sig_atomic_t sigusr1_count = 0;

void handler (int signal_number)
{
    ++sigusr1_count;
}
int main ()
{
    time_t tiempo1;
    time_t tiempo2;
    struct sigaction sa;
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &handler;
    sigaction (SIGUSR1, &sa, NULL);
    
    /* Do some lengthy stuff here. */
    printf("Ahora tiene 20 segundos para ejecutar \"kill -s 10 %d\" en otra terminal para aumentar el contador\n", (int) getpid ());
    
    tiempo1 = time(&tiempo1);   // Tomar el tiempo actual en segundos

    // Esperar 20 segundos (se usa time en vez de sleep ya que sleep se cancela despues de la primera llamada kill)
    while(1) {
        tiempo2 = time(&tiempo2);   // Tomar el tiempo actual en segundos
        if(tiempo1 + 20 < tiempo2) {    // si pasaron 10 segundos salir del ciclo
            break;
        }
    }
    
    printf ("SIGUSR1 was raised %d times\n", sigusr1_count);
    return 0;
}