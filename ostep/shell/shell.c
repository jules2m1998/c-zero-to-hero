#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_SPLIT " \t\n"
#define MAX_ARGS 64

void handle_pipes(char *left[MAX_ARGS], char *right[MAX_ARGS], int fds[2],
                  pid_t *pids) {
  pids[0] = fork();
  if (pids[0] == 0) {
    // Enfant 1
    dup2(fds[1], STDOUT_FILENO);
    close(fds[0]);
    close(fds[1]);

    execvp(left[0], left);
    perror("execvp");
    exit(EXIT_FAILURE);
  }

  pids[1] = fork();
  if (pids[1] == 0) {
    // Enfant 2
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    close(fds[1]);

    execvp(right[0], right);
    perror("execvp");
    exit(EXIT_FAILURE);
  }
}

void handle_simple(char *args[MAX_ARGS], int has_in, char *infile, int has_out,
                   char *outfile, pid_t *pids) {
  pids[0] = fork();

  if (pids[0] == 0) {
    if (has_out) {
      int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (fd == -1) {
        perror(outfile);
        exit(EXIT_FAILURE);
      }
      dup2(fd, STDOUT_FILENO);
      close(fd);
    }
    if (has_in) {
      int fd = open(infile, O_RDONLY);
      if (fd == -1) {
        perror(infile);
        exit(EXIT_FAILURE);
      }
      dup2(fd, STDIN_FILENO);
      close(fd);
    }

    execvp(args[0], args);
    perror("execvp");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  char *line = NULL;
  size_t linecapp;
  int bg_process_count = 0;
  while (1) {
    pid_t reaped;
    while ((reaped = waitpid(-1, NULL, WNOHANG)) > 0) {
      printf("[done] %d\n", reaped);
      bg_process_count--;
    }
    printf("$ ");
    fflush(stdout);

    ssize_t result = getline(&line, &linecapp, stdin);
    if (result == -1) {
      if (feof(stdin)) {
        printf("\n");
        break;
      }
      perror("getline");
      exit(1);
    }

    if (result == 0) {
      continue;
    }

    char *left[MAX_ARGS] = {NULL};
    char *right[MAX_ARGS] = {NULL};

    int has_pipe = 0;

    char *token = strtok(line, STR_SPLIT);
    int i = 0;
    char *outfile = NULL;
    char *infile = NULL;

    int has_out = 0;
    int has_in = 0;
    int is_bg = 0;

    while (token != NULL && i < MAX_ARGS - 1) {
      if (strcmp(token, ">") == 0) {
        has_out = 1;
      } else if (strcmp(token, "<") == 0) {
        has_in = 1;
      } else if (strcmp(token, "|") == 0) {
        has_pipe = 1;
        i = 0;
      } else if (has_out && outfile == NULL) {
        outfile = token;
      } else if (has_in && infile == NULL) {
        infile = token;
      } else if (!has_pipe) {
        left[i++] = token;
      } else {
        right[i++] = token;
      }

      token = strtok(NULL, STR_SPLIT);
    }

    if (has_pipe && *right == NULL) {
      fprintf(stderr, "syntax error: missing token after |\n");
      continue;
    }
    if (has_pipe && *left == NULL) {
      fprintf(stderr, "syntax error: missing token before |\n");
      continue;
    }
    if (has_out && outfile == NULL) {
      fprintf(stderr, "syntax error: missing file after >\n");
      continue;
    }

    if (has_in && infile == NULL) {
      fprintf(stderr, "syntax error: missing file after <\n");
      continue;
    }

    if (i == 0) {
      continue;
    }

    char **last_args = has_pipe ? right : left;

    if (i > 0 && strcmp(last_args[i - 1], "&") == 0) {
      if (i == 1 && !has_pipe) {
        fprintf(stderr, "shell : invalid token &\n");
        continue;
      }
      last_args[--i] = NULL;
      is_bg = 1;
    }

    if (strcmp(left[0], "exit") == 0) {
      exit(0);
    }

    if (strcmp(left[0], "cd") == 0) {
      const char *target = left[1];
      if (target == NULL) {
        target = getenv("HOME");
        if (target == NULL) {
          fprintf(stderr, "cd: HOME not set\n");
          continue;
        }
      }
      if (chdir(target) != 0) {
        perror("cd");
      }
      continue;
    }

    if (strcmp(left[0], "pwd") == 0) {
      char cwd[1024];
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
      } else {
        perror("pwd");
      }
      continue;
    }

    pid_t pids[2] = {-1, -1};

    int fds[2] = {-1, -1};

    if (has_pipe) {
      int pipe_result = pipe(fds);
      if (pipe_result == -1) {
        perror("pipe");
        continue;
      }
      handle_pipes(left, right, fds, pids);
      for (int i = 0; i < 2; i++) {
        close(fds[i]);
      }
    } else {
      handle_simple(left, has_in, infile, has_out, outfile, pids);
    }

    if (!is_bg) {
      for (int y = 0; y < 2 && pids[y] != -1; y++) {
        waitpid(pids[y], NULL, 0);
      }
    } else {
      for (int j = 0; j < 2 && pids[j] != -1; j++) {
        bg_process_count++;
      }
      printf("[%d] %d\n", bg_process_count, pids[0]);
    }
  }
  free(line);

  return 0;
}
