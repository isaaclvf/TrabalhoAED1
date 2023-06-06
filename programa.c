#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <csv.h>
#include "lista.h"
#define Max_LEN 152

typedef struct filme
{
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

int main(void)
{

  FILE *file = fopen("filmes.csv", "r");
  char buffer[1024];
  Filme a24[Max_LEN];

  int i = 0;
  fgets(buffer, sizeof(buffer), file);

  while (fgets(buffer, sizeof(buffer), file) != NULL)
  {
    // dados dos filmes

    char *id_str, *title, *director, *writers, *producer, *starring, *language, *country, *running_time_str, *budget_str, *box_office_str, *release_dates, *imdb_str, *metascore_str, *rotten_tomates_str;

    id_str = strtok(buffer, ",");
    title = strtok(NULL, ",");
    director = strtok(NULL, ",");
    writers = strtok(NULL, ",");
    producer = strtok(NULL, ",");
    starring = strtok(NULL, ",");
    country = strtok(NULL, ",");
    language = strtok(NULL, ",");
    running_time_str = strtok(NULL, ",");
    budget_str = strtok(NULL, ",");
    box_office_str = strtok(NULL, ",");
    release_dates = strtok(NULL, ",");
    imdb_str = strtok(NULL, ",");
    metascore_str = strtok(NULL, ",");
    rotten_tomates_str = strtok(NULL, ",");

    int id = atoi(id_str);
    int running_time = atoi(running_time_str);

    float budget = atof(budget_str);
    float box_office = atof(box_office_str);
    float imdb = atof(imdb_str);
    float metascore = atof(metascore_str);
    float rotten_tomates = atof(rotten_tomates_str);

    // alocando memoria

    a24[i].title = malloc(sizeof(char) * (strlen(title) + 1));
    a24[i].director = malloc(sizeof(char) * (strlen(director) + 1));
    a24[i].writers = malloc(sizeof(char) * (strlen(writers) + 1));
    a24[i].producer = malloc(sizeof(char) * (strlen(producer) + 1));
    a24[i].starring = malloc(sizeof(char) * (strlen(starring) + 1));
    a24[i].language = malloc(sizeof(char) * (strlen(language) + 1));
    a24[i].country = malloc(sizeof(char) * (strlen(country) + 1));
    a24[i].release_dates = malloc(sizeof(char) * (strlen(release_dates) + 1));

    // armazenando os dados no vetor

    strcpy(a24[i].title, title);
    strcpy(a24[i].director, director);
    strcpy(a24[i].writers, writers);
    strcpy(a24[i].producer, producer);
    strcpy(a24[i].starring, starring);
    strcpy(a24[i].language, language);
    strcpy(a24[i].country, country);
    strcpy(a24[i].release_dates, release_dates);
    a24[i].id = id;
    a24[i].running_time = running_time;
    a24[i].box_office = box_office;
    a24[i].budget = budget;
    a24[i].imdb = imdb;
    a24[i].metascore = metascore;
    a24[i].rotten_tomates = rotten_tomates;

    /* inserir auqui a função de print */

    // getchar();
    i++;
  }
  fclose(file);

  printf("%f\n", a24[1].imdb);
  return 0;
}