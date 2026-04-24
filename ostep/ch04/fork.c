#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  pid_t id = fork();
  if (id < 0) {
    perror("fork");
    return EXIT_FAILURE;
  }
  if (id == 0) {
    execv("/bin/ls", (char *[]){"/bin/ls", "-la", NULL});
    perror("execv");
    exit(EXIT_FAILURE);
  }
  int status;
  int child_pid = waitpid(id, &status, 0);
  if (child_pid == -1) {
    perror("waitpid");
    return EXIT_FAILURE;
  }
  printf("parent: pid %d\n", getpid());
  return 0;
}
