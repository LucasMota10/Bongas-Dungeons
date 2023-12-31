#ifndef MONSTRO_H
#define MONSTRO_H

#include "caminho.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

#define MAXF 10

typedef struct {
  char name[30];
  int vida;
  int escudo, tipo; //tipo 0 = mob normal; 1 = boss || Escudo maximo = 30

} tp_monstro;

typedef struct {
  int tipo, valor; //tipo-> 0 = ataque, 1 = defesa, 2 = especial
}acoes_monstro; 

typedef struct { //fila das ações do monstro
  acoes_monstro acoes[MAXF];
  int ini , fim;

}tp_fila;


void inicializa_fila(tp_fila *f){
f->ini = f->fim = MAXF - 1;
}

int fila_vazia(tp_fila *f){
if(f->ini == f->fim) return 1;
return 0;
}

int proximo(int pos){
if(pos == MAXF - 1) return 0;
return ++pos;
}

int fila_cheia(tp_fila *f){
    if(proximo(f->fim) == f->ini) return 1;
    return 0;
}

int insere_fila(tp_fila *f, acoes_monstro e){
    if(fila_cheia(f)) return 0;
    f->fim = proximo(f->fim);
    f->acoes[f->fim] = e;

    return 1;
}

int remove_fila(tp_fila *f, acoes_monstro *e){
    if(fila_vazia(f)) return 0;
    f->ini = proximo(f->ini);
    *e = f->acoes[f->ini];

return 1;
}

void imprime_acoes_monstro(tp_fila f){
    acoes_monstro e;
    printf("============================================\n");
    while(!fila_vazia(&f)){
        remove_fila(&f, &e);
         switch (e.tipo)
        {
        case 0:
            printf("Valor do Ataque: %d\n", e.valor);
            break;
        case 1:
            printf("Valor da Defesa: %d\n", e.valor);
            break;
        case 2:
            printf("Valor do Especial: %d\n", e.valor);
            break;
        default:
        break;
    }
    printf("============================================\n\n");
    
    }
}

int ultima_acao(tp_fila *f, acoes_monstro *e){
    if(fila_vazia(f)) return 0;
    *e = f->acoes[proximo(f->ini)];

}

int verificarvida(tp_monstro monstro){
  
  if(monstro.vida != 0) return 1;
  return 0;
}

int criar_acoes_monstro(tp_fila *fila){

    acoes_monstro acoes[MAXF];
    
    // Ataque
    acoes[0].tipo = 0;
    acoes[0].valor = 27;

    acoes[1].tipo = 0;
    acoes[1].valor = 18;

    acoes[2].tipo = 0;
    acoes[2].valor = 23;

    acoes[3].tipo = 0;
    acoes[3].valor = 12;

    // Defesa
    acoes[4].tipo = 1;
    acoes[4].valor = 5;

    acoes[5].tipo = 1;
    acoes[5].valor = 12;

    acoes[6].tipo = 1;
    acoes[6].valor = 8;

    acoes[7].tipo = 1;
    acoes[7].valor = 15;

    // Especial
    acoes[8].tipo = 2;
    acoes[8].valor = 10;

    acoes[9].tipo = 2;
    acoes[9].valor = 12;

    srand(time(NULL));
    for (int i=0; i<MAXF; i++){
        int random = rand()%10;
        acoes_monstro aux = acoes[i];
        acoes[i] = acoes[random];
        acoes[random] = aux;
        
    }
    for(int e=0; e<10; e++){
        insere_fila(fila, acoes[e]);
        }
    return 1;
}

void criarmonstro(tp_monstro *monstro, tp_player *player){
    
    monstro->vida = 200;
    monstro->escudo = 0;

    if(player->level == 1){
        monstro->tipo = 0;
        strcpy(monstro->name, "Mafia Chinesa");
    }
    if(player->level == 2){
        monstro->tipo = 0;
        strcpy(monstro->name, "Elon Musk");
    }
    if(player->level == 3){
        monstro->tipo = 0;
        strcpy(monstro->name, "Aluno do SESI");
    }
    if(player->level == 4){
        monstro->tipo = 0;
        strcpy(monstro->name, "Picos e Vales");
    }
    if(player->level == 5){
        strcpy(monstro->name, "Marcio Soussa");
        monstro->tipo = 1;
        monstro->vida = 400;
    }
  
}



#endif


