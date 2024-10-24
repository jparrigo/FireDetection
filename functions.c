#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"

struct arg_struct {
  int row;
  int col;
};

extern char floresta[TAMANHO][TAMANHO];
extern pthread_mutex_t floresta_mutex;
pthread_cond_t detectar_fogo = PTHREAD_COND_INITIALIZER;

void* verifica_sensor(void* args) {
  struct arg_struct *arguments = (struct arg_struct *)args;
  int col = arguments->col;
  int row = arguments->row;
  
  pthread_mutex_lock(&floresta_mutex);
  floresta[row][col] = 'T';
  pthread_mutex_unlock(&floresta_mutex);

  while(1) {
    pthread_mutex_lock(&floresta_mutex);
    if (floresta[row][col] == '@') {
      printf("Fogo encontrado");
    }
    pthread_mutex_unlock(&floresta_mutex);
    usleep(500000);
  }

  return NULL;
}

void* gerar_fogo(void* args) {
  while(1) {
    
    int col = rand() % TAMANHO;
    int row = rand() % TAMANHO;

    pthread_mutex_lock(&floresta_mutex);
    if (floresta[row][col] == '-') {
      floresta[row][col] = '@';
    }
    pthread_mutex_unlock(&floresta_mutex);
    sleep(3);
  }
}