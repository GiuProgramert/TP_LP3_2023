#include <pthread.h>
#include <stdio.h>

void *thread_function(void *thread_arg) {
  int number = *((int *)thread_arg);
  long long factorial = 1;

  // Calculate the factorial of the given number.
  for (int i = 1; i <= number; ++i) {
    factorial *= i;
  }

  printf("Factorial de %d es %lld\n", number, factorial);

  // No need to return anything in this example.
  return NULL;
}

int main() {
  pthread_attr_t attr;
  pthread_t thread;

  int fac_to_calc = 10;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&thread, &attr, &thread_function, &fac_to_calc);
  pthread_attr_destroy(&attr);

  /* Do work here... */
  /* No need to join the second thread. */
  thread_function(&fac_to_calc);

  return 0;
}