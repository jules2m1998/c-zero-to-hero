#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 100

void print_file(int fd) {
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read = 0;

  printf("content :\n");
  while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[bytes_read] = '\0';
    printf("%s", buffer);
  }
  printf("\n");
}

int main(void) {
  int fd = open("input.txt", O_RDWR);
  if (fd < 0) {
    perror("failed to open the file");
    return EXIT_FAILURE;
  }
  print_file(fd);

  char content[] = "\nfor write\n";
  ssize_t buffer_written = write(fd, content, strlen(content));
  if (buffer_written < 0) {
    perror("unable to write in the file");
    return EXIT_FAILURE;
  }

  lseek(fd, 0, SEEK_SET);
  print_file(fd);
  close(fd);

  return 0;
}
