#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_WORKERS 10
#define MAX_CONCURRENT 3

sem_t *pool;

void *worker(void *arg) {
  int id = *(int *)arg;
  printf("T%d: waiting\n", id);
  sem_wait(pool);

  printf("T%d: working\n", id);
  sleep(1);
  printf("T%d: done\n", id);

  sem_post(pool);
  return NULL;
}

int main(void) {
  sem_unlink("/my_pool"); // au cas où il traîne d'un run précédent
  pool = sem_open("/my_pool", O_CREAT, 0644, MAX_CONCURRENT);
  if (pool == SEM_FAILED) {
    perror("sem_open");
    exit(1);
  }

  pthread_t threads[N_WORKERS];
  int ids[N_WORKERS];

  for (int i = 0; i < N_WORKERS; i++) {
    ids[i] = i;
    pthread_create(&threads[i], NULL, worker, &ids[i]);
  }

  for (int i = 0; i < N_WORKERS; i++) {
    pthread_join(threads[i], NULL);
  }

  sem_close(pool);
  sem_unlink("/my_pool");
  return 0;
}
