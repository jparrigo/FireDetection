#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h>

// Definir o tamanho da matriz da floresta
#define TAMANHO 30

// Protótipos das funções
void* verifica_sensor(void* args);         // Função para os nós sensores
void* gerar_fogo(void* args);      // Função para a thread geradora de incêndios
void* controle_floresta(void* arg);     // Função para a central de controle
void propagar_fogo( int row, int col); // Função para propagar o fogo

// Variáveis globais
extern char floresta[TAMANHO][TAMANHO];       // Matriz que representa a floresta
extern pthread_mutex_t floresta_mutex;  // Mutex para garantir a exclusão mútua ao acessar a floresta
extern pthread_cond_t detectar_fogo;  // Variável de condição para detectar incêndios
extern int numero_combates_fogo;

#endif
