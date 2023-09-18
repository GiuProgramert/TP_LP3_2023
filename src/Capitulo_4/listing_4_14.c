#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int thread_flag;
pthread_cond_t thread_flag_cv;
pthread_mutex_t thread_flag_mutex;

void initialize_flag() {
  pthread_mutex_init(&thread_flag_mutex, NULL);
  pthread_cond_init(&thread_flag_cv, NULL);
  thread_flag = 0;
}

void set_thread_flag(int flag_value) {
  pthread_mutex_lock(&thread_flag_mutex);
  thread_flag = flag_value;
  pthread_cond_signal(&thread_flag_cv);
  pthread_mutex_unlock(&thread_flag_mutex);
}

void do_work() {
  int ran_num = (rand() % 1000) + 1;
  printf("Número generado %d\n", ran_num);

  if (ran_num / 2 == 0) {
    set_thread_flag(0);
  }
}

void *thread_function(void *thread_arg) {
  while (1) {
    pthread_mutex_lock(&thread_flag_mutex);
    while (!thread_flag)
      pthread_cond_wait(&thread_flag_cv, &thread_flag_mutex);
    pthread_mutex_unlock(&thread_flag_mutex);
    do_work();
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
