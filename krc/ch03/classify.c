#include <stdio.h>

int main(void) {
  int c;
  int vowel_count = 0;
  int consonants_count = 0;
  int other_count = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      vowel_count++;
      break;
    default:
      if (c >= 'a' && c <= 'z') {
        consonants_count++;
      } else {
        other_count++;
      }
    }
  }
  printf("vowels: %d\n", vowel_count);
  printf("consonants: %d\n", consonants_count);
  printf("other: %d\n", other_count);
  return 0;
}
