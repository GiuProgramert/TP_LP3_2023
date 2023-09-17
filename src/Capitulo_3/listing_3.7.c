#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

sig_atomic_t child_exit_status;

void clean_up_child_process (int signal_number)
{
    /* Clean up the child process. */
    int status;
    wait (&status);
    /* Store its exit status in a global variable. */
    child_exit_status = status;
}

int main ()
{
    pid_t child_pid;
    /* Handle SIGCHLD by calling clean_up_child_process. */
    struct sigaction sigchld_action;
    memset (&sigchld_action, 0, sizeof (sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;
    sigaction (SIGCHLD, &sigchld_action, NULL);

    child_pid = fork ();
    if (child_pid != 0) {
      printf("Soy el proceso padre. A constitucion se espera hasta 7 segundos para que "
           "el proceso hijo (probablemente) termina\n");
    }
    else {
      printf("Soy el processo hijo. Probablemente voy a terminar ahora.\n");
      exit(1);
    }
    
    sleep(7);

    printf("Mi proceso hijo termino con codigo exit %d\n", WEXITSTATUS(child_exit_status));
    return 0;
}