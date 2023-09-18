#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
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
pthread_mutex_t job_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t job_queue_count;

void initialize_job_queue() {
  job_queue = NULL;
  sem_init(&job_queue_count, 0, 0);
}

void *thread_function(void *arg) {
  while (1) {
    struct job *next_job;
    sem_wait(&job_queue_count);

    pthread_mutex_lock(&job_queue_mutex);
    next_job = job_queue;
    job_queue = job_queue->next;
    pthread_mutex_unlock(&job_queue_mutex);
    process_job(next_job);
    free(next_job);
  }
  return NULL;
}

void enqueue_job(struct job *new_job) {
  pthread_mutex_lock(&job_queue_mutex);
  new_job->next = job_queue;
  job_queue = new_job;
  sem_post(&job_queue_count);
  pthread_mutex_unlock(&job_queue_mutex);
}

void *gen_numbers(void *arg) {
  while (1) {
    int random_add = (random() % 100) + 1;
    for (int i = 0; i < random_add; i++) {
      int random_num = (random() % 1000) + 1;

      struct job *new_job;
      new_job = malloc(sizeof(struct job));
      new_job->number = random_num;
      enqueue_job(new_job);
    }
    sleep(5);
  }
}

int main(void) {

  pthread_t thread1_id;
  pthread_t thread2_id;
  pthread_t thread3_id;
  pthread_t thread_gen;

  int thread1_num = 1;
  int thread2_num = 2;
  int thread3_num = 3;

  srandom(time(NULL));

  job_queue = NULL;
  sem_init(&job_queue_count, 0, 0);

  pthread_create(&thread_gen, NULL, &gen_numbers, NULL);
  pthread_create(&thread1_id, NULL, &thread_function, &thread1_num);
  pthread_create(&thread2_id, NULL, &thread_function, &thread2_num);
  pthread_create(&thread3_id, NULL, &thread_function, &thread3_num);

  pthread_join(thread_gen, NULL);
  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);
  pthread_join(thread3_id, NULL);

  return 0;
}
