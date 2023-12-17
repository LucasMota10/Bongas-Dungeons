#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int tp_item; 


typedef struct {
  bool desvio;
}desvio;

//dados estruturado que representa o descritor
typedef struct tp_prox{ 

  struct tp_prox *nivel_desvio;

  desvio existe; 
  tp_item info;  //0-> combate 1->descanso
  
  struct tp_prox *prox;   
} tp_level; 

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

    novo_level->info = level_n;
    novo_level->prox = NULL;


  if(primeirolevel(*level)){
    novo_level->existe.desvio = true;
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
    
    level_item = atu->info;
    atu = atu->prox;
  }
  return level_item;
}


void imprime_caminho(tp_level *level){

  tp_level *atu;
  atu = level;


  while(atu != NULL){
    
    switch (atu->info)
    {
    case 0:
      printf("Combate - ", atu->info);
      break;
    
    default:
      printf("Descanso - ", atu->info);
      break;
    }
    
    atu = atu->prox;
    
  }

  if(level->existe.desvio){
    printf(" Combate/Descanso\n\n");
  }
  else printf(" Combate\n\n");

}

#endif