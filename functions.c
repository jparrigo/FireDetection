#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "functions.h"

extern char floresta[TAMANHO][TAMANHO];
extern pthread_mutex_t floresta_mutex;
pthread_cond_t detectar_fogo = PTHREAD_COND_INITIALIZER;
extern int numero_combates_fogo;

void* verifica_sensor(void* args) {
  int index = (intptr_t)args;
  int row = index / TAMANHO;
  int col = index % TAMANHO;
  
  pthread_mutex_lock(&floresta_mutex);
  floresta[row][col] = 'T';
  pthread_mutex_unlock(&floresta_mutex);

  while(1) {
    pthread_mutex_lock(&floresta_mutex);
    if (floresta[row][col] == '@') {
      propagar_fogo(row,col);
    }
    pthread_mutex_unlock(&floresta_mutex);
    sleep(1);
  }
}

void* gerar_fogo(void* args) {
  while(1) {
    
    int col = rand() % TAMANHO;
    int row = rand() % TAMANHO;

    pthread_mutex_lock(&floresta_mutex);
    if (floresta[row][col] == '-' || floresta[row][col] == 'T') {
      floresta[row][col] = '@';
    }
    pthread_mutex_unlock(&floresta_mutex);
    sleep(3);
  }
}

void propagar_fogo( int row, int col) {
  if (row > 0) floresta[row-1][col] = '@'; // Norte
  if (row < TAMANHO-1) floresta[row+1][col] = '@'; // Sul
  if (col > 0) floresta[row][col-1] = '@'; // Oeste
  if (col < TAMANHO-1) floresta[row][col+1] = '@'; // Leste
}

void combater_fogo() {
  for (int x = 0; x < TAMANHO; x++) {
    for (int y = 0; y < TAMANHO; y++) {
      if (floresta[x][y] == '@') {
        floresta[x][y] = '/';
        numero_combates_fogo = numero_combates_fogo + 1;
      }
    }
  }
}

void* controle_floresta(void* arg) {
    while (1) {
        pthread_mutex_lock(&floresta_mutex);
        for (int line = 0; line < TAMANHO; line++) {
          if (floresta[0][line] == '@' || floresta[29][line]) {
            combater_fogo();
          }
          if (floresta[line][0] == '@' || floresta[line][29]) {
            combater_fogo();
          }
        }
        // Ações da central (coleta de mensagens, combate ao fogo, etc.)
        pthread_mutex_unlock(&floresta_mutex);
        sleep(1);
    }
}