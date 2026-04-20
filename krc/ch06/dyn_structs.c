

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student {
  double gpa;
  char name[30];
  int age;
};

int main(void) {
  struct student *student =
      (struct student *)malloc(3 * sizeof(struct student));

  if (student == NULL) {
    fprintf(stderr, "malloc failed\n");
    return 1;
  }

  student->age = 10;
  student->gpa = 100;
  strncpy(student->name, "Jules Junior", sizeof(student->name));

  (student + 1)->age = 10;
  (student + 1)->gpa = 3.4;
  strncpy((student + 1)->name, "Student 2", sizeof((student + 1)->name));

  (student + 2)->age = 10;
  (student + 2)->gpa = 50.5;
  strncpy((student + 2)->name, "Student 3", sizeof((student + 2)->name));

  for (int i = 0; i < 3; i++) {
    struct student *current = (student + i);
    printf("name : %s, age : %d, gpa : %f\n", current->name, current->age,
           current->gpa);
  }

  printf("sizeof(struct student) = %ld\n", sizeof(struct student));
  printf("sizeof(char[32]) + sizeof(int) + sizeof(double) = %ld\n",
         sizeof(char[32]) + sizeof(int) + sizeof(double));
  free(student);
  student = NULL;

  return 0;
}
