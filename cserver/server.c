#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/event.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define STATUT_SIZE 50

typedef struct response_message {
  char message[BUFFER_SIZE];
  int message_size;
  int status;
  char status_text[STATUT_SIZE];
  int file_description;
  char content_type[256];
} ResponseMessage;

void get_content_type(const char *path, char content_type[256]) {
  char *ext = strrchr(path, '.');
  if (ext == NULL) {
    strcpy(content_type, "text/plain");
    return;
  }
  ext += 1;
  char type[50] = "text";
  char variant[50] = "plain";

  if (strcmp(ext, "html") == 0 || strcmp(ext, "css") == 0) {
    strcpy(variant, ext);
  } else if (strcmp(ext, "js") == 0) {
    strcpy(type, "application");
    strcpy(variant, "javascript");
  } else if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0 ||
             strcmp(ext, "png") == 0) {
    strcpy(type, "image");
    if (strcmp(ext, "jpg") == 0 || strcmp(ext, "jpeg") == 0) {
      strcpy(variant, "jpeg");
    } else {
      strcpy(variant, "png");
    }
  }
  int result = snprintf(content_type, 256, "%s/%s", type, variant);
}

int set_response(char *buffer, int buffer_size, int status,
                 const char status_text[], const char message[],
                 int message_size, char content_type[]) {

  const char response_template[] = "HTTP/1.1 %d %s\r\n"
                                   "Content-Type: %s\r\n"
                                   "Content-Length: %d\r\n"
                                   "\r\n"
                                   "%s";

  return snprintf(buffer, buffer_size, response_template, status, status_text,
                  content_type, message_size, message);
}

int write_response(ResponseMessage *message) {
  char response[BUFFER_SIZE];
  int count = set_response(response, BUFFER_SIZE, message->status,
                           message->status_text, message->message,
                           message->message_size, message->content_type);

  if (write(message->file_description, response, count) == -1) {
    perror("write");
    return EXIT_FAILURE;
  }

  return 0;
}

int write_header(ResponseMessage *message) {

  const char response_template[] = "HTTP/1.1 %d %s\r\n"
                                   "Content-Type: %s\r\n"
                                   "Content-Length: %d\r\n"
                                   "\r\n";
  char buffer[256];

  int size = snprintf(buffer, 256, response_template, message->status,
                      message->status_text, message->content_type,
                      message->message_size);
  if (size == -1) {
    perror("snprintf");
    message->status = 500;
    message->message_size = strlen(message->message);

    strcpy(message->status_text, "Internal Server Error");
    strcpy(message->message, "Internal Server Error");
    strcpy(message->content_type, "text/plain");
    write_response(message);
    return EXIT_FAILURE;
  }

  if (write(message->file_description, buffer, size) == -1) {
    perror("write");
    return EXIT_FAILURE;
  }
  return 0;
}

int handle_static_file(int client_fd, const char *path) {

  ResponseMessage message = {0};
  message.file_description = client_fd;

  int fd = open(path, O_RDONLY);
  if (fd == -1) {

    perror("open");
    message.status = 404;

    strcpy(message.status_text, "Not found");
    strcpy(message.message, "Not found");
    strcpy(message.content_type, "text/plain");
    message.message_size = strlen(message.message);
    write_response(&message);

    return EXIT_FAILURE;
  }
  char *ext = strrchr(path, '.');
  struct stat file_stat;
  if (fstat(fd, &file_stat) == -1) {
    perror("fstat");
    message.status = 500;

    strcpy(message.status_text, "Internal Server Error");
    strcpy(message.message, "Internal Server Error");
    strcpy(message.content_type, "text/plain");
    message.message_size = strlen(message.message);
    write_response(&message);
    return EXIT_FAILURE;
  }

  message.status = 200;
  strcpy(message.status_text, "Ok");
  message.message_size = file_stat.st_size;
  get_content_type(path, message.content_type);
  write_header(&message);

  char buff[BUFFER_SIZE];
  int read_size = 0;
  while ((read_size = read(fd, buff, BUFFER_SIZE)) > 0) {
    write(client_fd, buff, read_size);
  }
  close(fd);
  return 0;
}

int handle_client(int client_fd) {

  char buffer[BUFFER_SIZE];

  int read_count;
  if ((read_count = read(client_fd, buffer, sizeof(buffer) - 1)) == -1) {

    perror("unable to read the request");
    return EXIT_FAILURE;
  }
  buffer[read_count] = '\0';

  char method[8];
  char path[256];

  ResponseMessage message = {0};
  message.file_description = client_fd;

  if (sscanf(buffer, "%7s %255s", method, path) != 2) {
    char body[] = "Requete mal formatee";
    strcpy(message.message, body);
    message.message_size = strlen(body);
    strcpy(message.content_type, "text/plain");
    strcpy(message.status_text, "Bad request");
    message.status = 400;
    write_response(&message);
    return EXIT_FAILURE;
  }

  printf("method=%s path=%s\n", method, path);
  if (*path == '/' && strlen(path) == 1) {
    strcpy(path, "/index.html");
  } else {
    char *path_buff = path;
    while (*path_buff != '\0' && *(++path_buff) != '\0') {
      if (*(path_buff - 1) == '.' && *path_buff == '.') {
        char body[] = "You do not have permission to access this resource.";
        message.status = 403;
        strcpy(message.status_text, "Forbidden");
        strcpy(message.message, body);
        message.message_size = strlen(body);
        strcpy(message.content_type, "text/plain");

        write_response(&message);
        return EXIT_FAILURE;
      }
    }
  }

  char full_path[256];
  if (snprintf(full_path, 256, "./www%s", path) == -1) {
    perror("snprintf");
    message.status = 500;

    strcpy(message.status_text, "Internal Server Error");
    strcpy(message.message, "Internal Server Error");
    strcpy(message.content_type, "text/plain");
    message.message_size = strlen(message.message);

    return EXIT_FAILURE;
  }
  handle_static_file(client_fd, full_path);

  return 0;
}

void delete_event(int kq, int fd) {
  struct kevent del;
  EV_SET(&del, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
  kevent(kq, &del, 1, NULL, 0, NULL);
  close(fd);
}

int main(void) {
  int global_scoket = socket(AF_INET, SOCK_STREAM, 0);
  if (global_scoket == -1) {
    perror("unable to open a socket");
    return EXIT_FAILURE;
  }

  int opt = 1;
  if (setsockopt(global_scoket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) ==
      -1) {
    perror("setsockopt");
    close(global_scoket);
    return EXIT_FAILURE;
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(global_scoket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    close(global_scoket);
    perror("unable to bind the socket");
    return EXIT_FAILURE;
  }
  if (listen(global_scoket, 10) == -1) {
    close(global_scoket);
    perror("unable to listen to the server");
    return EXIT_FAILURE;
  }

  int kq = kqueue();
  if (kq == -1) {
    perror("kqueue");
    close(global_scoket);
    return EXIT_FAILURE;
  }

  struct kevent global_change;
  EV_SET(&global_change, global_scoket, EVFILT_READ, EV_ADD, 0, 0, NULL);
  struct kevent received_events[64];

  int n = kevent(kq, &global_change, 1, NULL, 0, NULL);
  if (n == -1) {
    perror("kevent");
    close(global_scoket);
    return EXIT_FAILURE;
  }

  while (1) {
    n = kevent(kq, NULL, 0, received_events, 64, NULL);
    if (n == -1) {
      perror("kevent");
      delete_event(kq, global_scoket);
      return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
      struct kevent current = received_events[i];
      if ((int)current.ident == global_scoket) {
        struct sockaddr_in accept_result;
        socklen_t address_len = sizeof(accept_result);
        int accept_socket;
        if ((accept_socket =
                 accept(global_scoket, (struct sockaddr *)&accept_result,
                        &address_len)) == -1) {
          perror("unable to accept connections");
          delete_event(kq, global_scoket);
          return EXIT_FAILURE;
        }
        struct kevent client_event;
        EV_SET(&client_event, accept_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
        if (kevent(kq, &client_event, 1, NULL, 0, NULL) == -1) {
          perror("kevent");
          delete_event(kq, global_scoket);
          return EXIT_FAILURE;
        }
      } else {
        handle_client((int)current.ident);
        delete_event(kq, (int)current.ident);
      }
    }
  }
  delete_event(kq, global_scoket);
  return 0;
}
