#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "functions.h"

#define	TAMANHO	30

char floresta[TAMANHO][TAMANHO];
int numero_combates_fogo = 0;
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
  printf("COMBATEU %d AREAS COM FOGO!\n",numero_combates_fogo);
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
  print_matriz(0);
  sleep(2);
  pthread_mutex_init(&floresta_mutex, NULL);

  pthread_t sensores[TAMANHO][TAMANHO];
  pthread_t thread_gerador_fogo, thread_controlador;
  
  for (int x = 0; x < TAMANHO; x++) {
    for (int y = 0; y < TAMANHO; y++) {
      pthread_create(&sensores[x][y], NULL, verifica_sensor,(void *)(intptr_t)(x * TAMANHO + y));
    }
  }

  pthread_create(&thread_gerador_fogo, NULL, gerar_fogo, NULL);

  pthread_create(&thread_controlador, NULL, controle_floresta, NULL);

  int time = 0;
  while(1) {
    time = time + 1;
    print_matriz(time);
    sleep(1);
  }

  return 0;
}