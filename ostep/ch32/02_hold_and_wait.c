#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  int balance;
  pthread_mutex_t lock;
  int id;
} Account;

typedef struct {
  Account *from;
  Account *to;
  int amount;
} TransferArgs;
Account a = {.balance = 100, .id = 0, .lock = PTHREAD_MUTEX_INITIALIZER};
Account b = {.balance = 50, .id = 1, .lock = PTHREAD_MUTEX_INITIALIZER};

void *transfer(void *args);

int main(void) {
  pthread_t t1, t2;
  TransferArgs args1 = {.from = &a, .to = &b, .amount = 100};
  TransferArgs args2 = {.from = &b, .to = &a, .amount = 50};

  pthread_create(&t1, NULL, transfer, &args1);
  pthread_create(&t2, NULL, transfer, &args2);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
#ifdef USE_TRYLOCK

void *transfer(void *args) {
  TransferArgs *t_args = (TransferArgs *)args;

  while (1) {

    printf("T%d: lock from (account %d)\n", t_args->from->id, t_args->from->id);
    pthread_mutex_lock(&t_args->from->lock);

    if (pthread_mutex_trylock(&t_args->to->lock) == 0) {
      // on a les DEUX locks → on peut travailler

      printf("T%d: got both locks\n", t_args->from->id);
      break;
    }
    printf("T%d: trylock on %d failed, release %d\n", t_args->from->id,
           t_args->to->id, t_args->from->id);
    // on a from mais pas to → on lâche from et on retry
    pthread_mutex_unlock(&t_args->from->lock);

    // petit délai pour éviter le livelock
    usleep(10000); // 10ms
  }

  // section critique : on tient les deux
  t_args->to->balance += t_args->amount;
  t_args->from->balance -= t_args->amount;

  pthread_mutex_unlock(&t_args->to->lock);
  pthread_mutex_unlock(&t_args->from->lock);
  return NULL;
}
#else

void *transfer(void *args) {
  TransferArgs *t_args = (TransferArgs *)args;

  printf("T%d: lock from (account %d)\n", t_args->from->id, t_args->from->id);
  pthread_mutex_lock(&t_args->from->lock);
  sleep(1);
  printf("T%d: ask for to (account %d)\n", t_args->from->id, t_args->to->id);

  pthread_mutex_lock(&t_args->to->lock);
  printf("T%d: ask for to (account %d)\n", t_args->from->id, t_args->to->id);

  t_args->to->balance += t_args->amount;
  t_args->from->balance -= t_args->amount;

  pthread_mutex_unlock(&t_args->to->lock);

  pthread_mutex_unlock(&t_args->from->lock);

  return NULL;
}
#endif /* ifdef USE_TRYLOCK */
