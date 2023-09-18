#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initialize_flag() {
  pthread_mutex_init(&thread_flag_mutex, NULL);
  thread_flag = 0;
}

/* Sets the value of the thread flag to FLAG_VALUE. */
void set_thread_flag(int flag_value) {
  /* Protect the flag with a mutex lock. */
  pthread_mutex_lock(&thread_flag_mutex);
  thread_flag = flag_value;
  pthread_mutex_unlock(&thread_flag_mutex);
}

void do_work() {
  int ran_num = (rand() % 1000) + 1;
  printf("Número generado %d\n", ran_num);

  if (ran_num / 2 == 0) {
    set_thread_flag(0);
  }
}

/* Calls do_work repeatedly while the thread flag is set; otherwise
 spins. */
void *thread_function(void *thread_arg) {
  while (1) {
    int flag_is_set;
    /* Protect the flag with a mutex lock. */
    pthread_mutex_lock(&thread_flag_mutex);
    flag_is_set = thread_flag;
    pthread_mutex_unlock(&thread_flag_mutex);
    if (flag_is_set)
      do_work();
    /* Else don't do anything. Just loop again. */
  }
  return NULL;
}

int main() {

  pthread_t thread_id;

  srand(time(NULL));
  initialize_flag();

  set_thread_flag(1);
  pthread_create(&thread_id, NULL, &thread_function, NULL);

  while (thread_flag) {
    sleep(2);
  }

  return 0;
}
