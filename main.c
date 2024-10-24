#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "functions.h"

#define	TAMANHO	30

struct arg_struct {
  int row;
  int col;
} args;

char floresta[TAMANHO][TAMANHO];
pthread_mutex_t floresta_mutex;

void iniciar_floresta() {
  for (int x = 0; x < TAMANHO; x++) {
    for (int y = 0; y < TAMANHO; y++) {
      floresta[x][y] = '-';
    }
  }
}


void print_matriz(int tick) {
  system("clear");
  printf("ATUALIZOU %d VEZ!\n",tick);
  for (int x = 0; x < TAMANHO; x++) {
    for (int y = 0; y < TAMANHO; y++) {
      printf("| %c ",floresta[x][y]);
    }
    printf("|\n");
  }
}

int main (void) {
  printf("Fire Detection\n");
  iniciar_floresta();
  pthread_mutex_init(&floresta_mutex, NULL);

  pthread_t sensores[TAMANHO][TAMANHO];
  pthread_t thread_gerador_fogo, thread_controlador;
  

  for (int x = 0; x < TAMANHO; x++) {
    for (int y = 0; y < TAMANHO; y++) {
      args.col = y;
      args.row = x;
      pthread_create(&sensores[x][y], NULL, verifica_sensor,(void *)&args);
    }
  }
  int time = 0;
  while(1) {
    time = time + 1;
    print_matriz(time);
    usleep(2000000);
  }

  return 0;
}