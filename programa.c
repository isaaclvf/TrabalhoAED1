#include <csv.h>
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

/**
 * Funções para ordenação
 *
 * IMPORTANTE:
 * As funções de comparação devem retornar números inteiros seguindo essas
 * regras (para ordenar em ordem crescente):
 * - negativo se o primeiro elemento for menor,
 * - zero se forem iguais,
 * - positivo se o primeiro elemento for maior.
 */

int comparaImdb(Filme *a, Filme *b) {
  if (a->imdb > b->imdb) {
    return -1;
  }

  if (a->imdb < b->imdb) {
    return 1;
  }
  return 0;
}

int comparaMetascore(Filme *a, Filme *b) {
  if (a->metascore > b->metascore) {
    return -1;
  }

  if (a->metascore < b->metascore) {
    return 1;
  }
  return 0;
}

int comparaRotten(Filme *a, Filme *b) {
  if (a->rotten_tomates > b->rotten_tomates) {
    return -1;
  }

  if (a->rotten_tomates < b->rotten_tomates) {
    return 1;
  }
  return 0;
}

int comparaTitulo(Filme *a, Filme *b) { return strcmp(a->title, b->title); }

int comparaDiretor(Filme *a, Filme *b) {
  return strcmp(a->director, b->director);
}

int comparaDataLancamento(Filme *a, Filme *b) {
  // Filmes mais antigos no início
  int ano1, mes1, dia1;
  sscanf(a->release_dates, "%d-%d-%d", &ano1, &mes1, &dia1);

  int ano2, mes2, dia2;
  sscanf(b->release_dates, "%d-%d-%d", &ano2, &mes2, &dia2);

  // Compara anos
  if (ano1 > ano2) {
    return 1;
  } else if (ano1 < ano2) {
    return -1;
  }

  // Se for do mesmo ano, compara meses
  if (mes1 > mes2) {
    return 1;
  } else if (mes1 < mes2) {
    return -1;
  }

  // Se for do mesmo mês, compara dias
  if (dia1 > dia2) {
    return 1;
  } else if (dia1 < dia2) {
    return -1;
  }

  // Datas iguais
  return 0;
}

/**
 * Funções auxiliares
 */
Filme *criaFilme(int id, char *title, char *director, char *writers,
                 char *producer, char *starring, char *country, char *language,
                 int running_time, float budget, float box_office,
                 char *release_dates, float imdb, float metascore,
                 float rotten_tomates) {
  Filme *f = malloc(sizeof(Filme));

  f->title = malloc(sizeof(char) * (strlen(title) + 1));
  f->director = malloc(sizeof(char) * (strlen(director) + 1));
  f->writers = malloc(sizeof(char) * (strlen(writers) + 1));
  f->producer = malloc(sizeof(char) * (strlen(producer) + 1));
  f->starring = malloc(sizeof(char) * (strlen(starring) + 1));
  f->language = malloc(sizeof(char) * (strlen(language) + 1));
  f->country = malloc(sizeof(char) * (strlen(country) + 1));
  f->release_dates = malloc(sizeof(char) * (strlen(release_dates) + 1));

  strcpy(f->title, title);
  strcpy(f->director, director);
  strcpy(f->writers, writers);
  strcpy(f->producer, producer);
  strcpy(f->starring, starring);
  strcpy(f->language, language);
  strcpy(f->country, country);
  strcpy(f->release_dates, release_dates);
  f->id = id;
  f->running_time = running_time;
  f->box_office = box_office;
  f->budget = budget;
  f->imdb = imdb;
  f->metascore = metascore;
  f->rotten_tomates = rotten_tomates;

  return f;
}

Lista *leFilmesCsv(char *path) {
  FILE *file = fopen(path, "r");
  char buffer[1024];
  Lista *lista_filmes = criaLista();

  int i = 0;
  fgets(buffer, sizeof(buffer), file);

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    // dados dos filmes
    char *id_str, *title, *director, *writers, *producer, *starring, *language,
        *country, *running_time_str, *budget_str, *box_office_str,
        *release_dates, *imdb_str, *metascore_str, *rotten_tomates_str;

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

    Filme *f = criaFilme(id, title, director, writers, producer, starring,
                         country, language, running_time, budget, box_office,
                         release_dates, imdb, metascore, rotten_tomates);

    inserirFim(lista_filmes, f);

    i++;
  }

  fclose(file);

  return lista_filmes;
}

int main(void) {
  Lista *lista_filmes = leFilmesCsv("filmes.csv");

  // Ordena em ordem alfabetica antes de imprimir
  quicksort(lista_filmes->inicio, lista_filmes->fim, comparaTitulo);

  for (No *i = lista_filmes->inicio; i->prox != NULL; i = i->prox) {
    Filme *f = (Filme *)i->dados;
    printf("%s %.2f\n", f->title, f->imdb);
  }

  return 0;
}