#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int running = 1;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int random_number = 0;
int has_item = 0;
void *producer(void *arg);
void *consumer(void *arg);

int main(void) {
  pthread_t t1, t2, t3;
  pthread_create(&t1, NULL, producer, NULL);
  pthread_create(&t2, NULL, consumer, NULL);
  pthread_create(&t3, NULL, consumer, NULL);

  sleep(5);
  running = 0;

  pthread_join(t1, NULL);

  pthread_cond_broadcast(&cond);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);

  return 0;
}

void *producer(void *arg) {
  while (running) {
    pthread_mutex_lock(&lock);
    srand(time(NULL));

    random_number = rand();
    has_item = 1;

    printf("produced : %d\n", random_number);
    pthread_mutex_unlock(&lock);

    pthread_cond_signal(&cond);
    sleep(1);
  }
  return NULL;
}

static int queue_empty() { return has_item == 0 && running == 1; }

void *consumer(void *arg) {
  while (running) {
    pthread_mutex_lock(&lock);
    while (queue_empty()) {
      pthread_cond_wait(&cond, &lock);
    }
    if (running == 0) {
      pthread_mutex_unlock(&lock);
      return NULL;
    }

    uint64_t tid;
    pthread_threadid_np(NULL, &tid);
    printf("consumed from %llu is %d\n", tid, random_number);
    random_number = 0;
    has_item = 0;
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}
