#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "lista.h"

typedef struct filme {
  int id;
  char *title;
  char *director;
  char *writers;
  char *producer;
  char *starring;
  char *country;
  char *language;
  int running_time;
  float budget;
  float box_office;
  char *release_dates;
  float imdb;
  float metascore;
  float rotten_tomates;

} Filme;

int main(void) {
  printf("oiii\n");
  return 0;
}