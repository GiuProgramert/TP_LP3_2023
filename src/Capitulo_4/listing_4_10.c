#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct job {
  /* Link field for linked list. */
  struct job *next;
  /* Other fields describing work to be done... */
  int number;
};

void is_prime(int number) {
  for (int i = 2; i < number; i++) {
    if (number % i == 0) {
      printf("No es primo %d\n", number);
      return;
    }
  }
  printf("No es primo %d\n", number);
}

void process_job(struct job *job) { is_prime(job->number); }

struct job *job_queue;
void *thread_function(void *arg) {
  while (job_queue != NULL) {
    struct job *next_job = job_queue;
    job_queue = job_queue->next;
    process_job(next_job);
    free(next_job);
  }
  return NULL;
}

int main() {
  pthread_t thread1_id;
  pthread_t thread2_id;

  srandom(time(NULL));

  for (int i = 0; i < 10; i++) {
    int random_num = (random() % 1000) + 1;

    struct job *new_job;
    new_job = malloc(sizeof(struct job));
    new_job->number = random_num;
    new_job->next = job_queue;
    job_queue = new_job;
  }

  pthread_create(&thread1_id, NULL, &thread_function, NULL);
  pthread_create(&thread2_id, NULL, &thread_function, NULL);

  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);

  return 0;
}