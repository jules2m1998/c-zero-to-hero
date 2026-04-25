#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 2
#define CONSUMER_COUNT 3
#define EMPTY_SEM "/pc_empty"
#define FULL_SEM "/pc_full"

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t *empty;
sem_t *full;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *arg);
void *producer(void *arg);

int main(void) {
  sem_unlink(EMPTY_SEM);
  sem_unlink(FULL_SEM);

  empty = sem_open(EMPTY_SEM, O_CREAT, 0644, BUFFER_SIZE);
  full = sem_open(FULL_SEM, O_CREAT, 0644, 0);

  pthread_t producer_threads[PRODUCER_COUNT];
  int p_ids[PRODUCER_COUNT];
  for (int i = 0; i < PRODUCER_COUNT; i++) {
    p_ids[i] = i;
    pthread_create(&producer_threads[i], NULL, producer, (void *)&p_ids[i]);
  }

  pthread_t consumer_threads[CONSUMER_COUNT];
  int c_ids[CONSUMER_COUNT];
  for (int i = 0; i < CONSUMER_COUNT; i++) {
    c_ids[i] = i;
    pthread_create(&consumer_threads[i], NULL, consumer, (void *)&c_ids[i]);
  }

  for (int i = 0; i < PRODUCER_COUNT; i++) {
    pthread_join(producer_threads[i], NULL);
  }

  for (int i = 0; i < CONSUMER_COUNT; i++) {
    sem_wait(empty);
    pthread_mutex_lock(&lock);
    buffer[in] = -1;
    in = (in + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&lock);
    sem_post(full);
  }

  for (int i = 0; i < CONSUMER_COUNT; i++) {
    pthread_join(consumer_threads[i], NULL);
  }

  sem_close(empty);
  sem_close(full);

  sem_unlink(EMPTY_SEM);
  sem_unlink(FULL_SEM);

  return 0;
}

void *consumer(void *arg) {
  int id = *((int *)arg);
  while (1) {
    sem_wait(full);
    pthread_mutex_lock(&lock);
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&lock);
    sem_post(empty);

    if (item == -1) {
      printf("C%d: poison pill, exit\n", id);
      return NULL;
    }
    printf("C%d: consumed %d\n", id, item);
  }
}
void *producer(void *arg) {
  int id = *((int *)arg);
  for (int i = 0; i < 10; i++) {
    int item = rand() % 1000;

    sem_wait(empty);
    pthread_mutex_lock(&lock);
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    pthread_mutex_unlock(&lock);
    sem_post(full);

    printf("P%d: produced %d\n", id, item);
  }
  return NULL;
}
