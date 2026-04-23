#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

typedef enum {
  TOKEN_STAR,     /* * */
  TOKEN_LPAREN,   /* ( */
  TOKEN_RPAREN,   /* ) */
  TOKEN_LBRACKET, /* [ */
  TOKEN_RBRACKET, /* ] */
  TOKEN_INT,      /* int, char... */
  TOKEN_IDENT,    /* nom de variable */
  TOKEN_NUMBER,   /* 3, 5... */
} TokenType;

typedef struct {
  TokenType type;
  char value[BUFFER_SIZE];
} Token;

int tokenize(const char *input, Token *tokens, int max_tokens);
int find_token_ident(Token *tokens,
                     int max_count); // return the token with type TOKEN_IDENT
                                     // and return -1 if there is none
void explain(Token *tokens, int count, char *output, int output_size);

static int accumulate_token(const char *input, char *output, int max_count) {
  int i = 0;
  while (i < max_count && *input != '\0') {
    switch (*input) {
    case '*':
    case '(':
    case ')':
    case '[':
    case ']':
    case ' ':
      return i;
    }
    output[i] = *input;
    i++;
    input++;
  }
  return i;
}
void print_explanation(const char input[]) {

  Token tokens[64];
  int count = tokenize(input, tokens, 64);
  // for (int i = 0; i < count; i++) {
  //   printf("type=%d value='%s'\n", tokens[i].type, tokens[i].value);
  // }
  char output[256];
  explain(tokens, count, output, 256);
  printf("%s\n", output);
}
int main(void) {
  char input[256];
  if (fgets(input, sizeof(input), stdin) == NULL) {
    printf("invalid input !\n");
    exit(EXIT_FAILURE);
  }
  input[strcspn(input, "\n")] = '\0';
  print_explanation(input);
  return 0;
}

int tokenize(const char *input, Token *tokens, int max_tokens) {
  int i = 0;
  char acc[BUFFER_SIZE];
  while (*input != '\0' && i < max_tokens) {
    Token current = {0};
    int count_token = 0;

    switch (*input) {
    case '*':
      current.type = TOKEN_STAR;
      strcpy(current.value, "*");
      break;
    case '(':
      current.type = TOKEN_LPAREN;
      strcpy(current.value, "(");
      break;
    case ')':
      current.type = TOKEN_RPAREN;
      strcpy(current.value, ")");
      break;
    case '[':
      current.type = TOKEN_LBRACKET;
      strcpy(current.value, "[");
      break;
    case ']':
      current.type = TOKEN_RBRACKET;
      strcpy(current.value, "]");
      break;
    case ' ':
      input++;
      continue;
    default:
      count_token = accumulate_token(input, acc, max_tokens - i);
      if (count_token > 0) {
        acc[count_token] = '\0';
        strcpy(current.value, acc);

        if (strcmp(acc, "int") == 0 || strcmp(acc, "char") == 0 ||
            strcmp(acc, "double") == 0 || strcmp(acc, "unsigned") == 0 ||
            strcmp(acc, "long") == 0 || strcmp(acc, "short") == 0 ||
            strcmp(acc, "void") == 0) {
          current.type = TOKEN_INT;
        } else if (acc[0] >= 'a' && acc[0] <= 'z') {
          current.type = TOKEN_IDENT;
        } else {
          current.type = TOKEN_NUMBER;
        }
      }
      tokens[i++] = current;
      input += count_token;
      continue;
    }
    if (*current.value == 0) {
      printf("something wrong happened!");
      exit(1);
    }
    tokens[i++] = current;
    input++;
  }
  return i;
}

int find_token_ident(Token *tokens, int max_count) {
  int result = 0;
  while (result < max_count) {
    if (tokens->type == TOKEN_IDENT) {
      return result;
    }
    tokens++;
    result++;
  }
  return -1;
}

void consume_until(Token *tokens, int *right, char *output, int output_size,
                   TokenType type) {
  while (tokens[*right].type != type) {
    strlcat(output, tokens[*right].value, output_size);
    *right += 1;
  }
}
void explain(Token *tokens, int count, char *output, int output_size) {

  int begin = -1;
  if ((begin = find_token_ident(tokens, count)) == -1) {
    printf("theren't any identifier on this instruction!");
    return;
  }
  snprintf(output, output_size, "%s is", tokens[begin].value);
  int right = begin + 1;
  int left = begin - 1;

  int direction = 0;
  int iterations = 0;
  char msg[256];
  char size[50];

  while (iterations < count - 1) {
    if (direction == 0 && right < count) { // go right
      switch (tokens[right].type) {
      case TOKEN_LBRACKET:
        size[0] = '\0';

        right++;
        consume_until(tokens, &right, size, 50, TOKEN_RBRACKET);
        snprintf(msg, 256, " array %s of", size);
        strlcat(output, msg, output_size);
        right++;
        direction = -1;
        break;
      case TOKEN_RPAREN:
        right++;
        direction = -1;
        break;
      case TOKEN_LPAREN:
        right++;
        size[0] = '\0';
        consume_until(tokens, &right, size, 50, TOKEN_RPAREN);
        snprintf(msg, 256, " function (%s) returning", size);
        strlcat(output, msg, output_size);
        right++;
        direction = -1;
        break;
      default:
        return;
        break;
      }
    } else if (direction == -1 && left >= 0) { // go left
      switch (tokens[left].type) {
      case TOKEN_INT:
        strlcat(output, " ", output_size);
        strlcat(output, tokens[left].value, output_size);
        left--;
        direction = 0;
        break;
      case TOKEN_STAR:
        strlcat(output, " pointer to", output_size);
        left--;
        direction = 0;
        break;
      case TOKEN_LPAREN:
        left--;
        direction = 0;
        break;
      default:
        return;
      }
    } else if (right >= count && left < 0) {
      break;
    } else {
      direction = direction == 0 ? -1 : 0;
      continue;
    }
    iterations++;
  }
}
