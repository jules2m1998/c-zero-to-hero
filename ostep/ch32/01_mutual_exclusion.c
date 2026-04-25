#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>

void *increment(void *args);

#ifdef USE_ATOMIC
atomic_int counter = 0;

int main(void) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, increment, NULL);
  pthread_create(&t2, NULL, increment, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("counter = %d\n", atomic_load(&counter));
  return 0;
}

void *increment(void *args) {
  int i = 0;
  while (i < 1000000) {
    atomic_fetch_add(&counter, 1);
    i++;
  }
  return NULL;
}
#else
int counter = 0;

int main(void) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, increment, NULL);
  pthread_create(&t2, NULL, increment, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  printf("counter = %d\n", counter);
  return 0;
}
void *increment(void *args) {
  int i = 0;
  while (i < 1000000) {
    counter++;
    i++;
  }
  return NULL;
}

#endif /* ifdef USE_ATOMIC */
