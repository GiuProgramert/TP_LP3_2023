#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_function(void *arg) {
  fprintf(stderr, "child thread pid is %d\n", (int)getpid());
  /* Spin forever. */
  while (1)
    ;
  return NULL;
}

int main() {
  pthread_t thread;
  fprintf(stderr, "main thread pid is %d\n", (int)getpid());
  pthread_create(&thread, NULL, &thread_function, NULL);
  /* Spin forever. */
  while (1)
    ;
  return 0;
}
