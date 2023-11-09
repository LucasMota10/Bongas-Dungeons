#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>

typedef int tp_item;

typedef struct tp_prox{

  tp_item level_n, tipo; //Tipo-> Descanso ou Luta (0= combate, 1=descanso). Level_n-> Em qual nível o player se encontra;
  struct tp_prox *prox;

}tp_level;

tp_level * inicializa_level(){
    return NULL;
}

int primeirolevel(tp_level *level){

  if(level == NULL) return 1;
  else return 0;

}

tp_level *aloca_level(){
    tp_level *novo_level;
    novo_level = (tp_level*) malloc(sizeof(tp_level));
  
}

int novolevel(tp_level **level, tp_item level_n, tp_item tipo){
  tp_level *novo_level, *atu;
	
	novo_level = aloca_level();
	if(novo_level == NULL) return 0;

    novo_level->level_n = level_n;
    novo_level->tipo = tipo;
    novo_level->prox = NULL;

  if(primeirolevel(*level)){
    *level = novo_level;
  }
  else{
    atu = *level;
    while(atu->prox != NULL){
      atu = atu->prox;
    }
    atu->prox = novo_level;
  }
  return 1;
}

int level_atual(tp_level *level){
  
  tp_level *atu;
  tp_item level_item;

  atu = level;
  
  while(atu != NULL){
    level_item = atu->level_n;
    atu = atu->prox;
  }
  return level_item;
}

#endif