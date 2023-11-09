#ifndef MAOJOGADOR_H
#define MAOJOGADOR_H
#include <stdio.h>
#include <stdlib.h>
#include "carta.h"

//struct da lista duplamente encadeada
typedef struct tp_no_aux{
    struct tp_no_aux *ant;
    struct tp_no_aux *prox;
    tp_cartas carta;

}tp_no;

typedef struct {
    tp_no *ini;
    tp_no *fim;

} tp_listad;

//alocamento de memoria
tp_listad *inicializa_listad(){
    tp_listad *lista=(tp_listad*) malloc(sizeof(tp_listad));
    lista->ini = NULL;
    lista->fim = NULL;

return lista;
}

//lista vazia
int listad_vazia(tp_listad *lista) {
    if ( (lista->ini == NULL) )return 1;
return 0;
}

//aloca no
tp_no *aloca() {
    tp_no* pt;
    pt=(tp_no*) malloc(sizeof(tp_no));
    return pt;
}

//insere lista
int insere_listad_no_fim (tp_listad *lista, tp_cartas e){
    tp_no *novo;
    novo=aloca();
    if (!novo) return 0;
    novo->carta = e;
    if ( listad_vazia(lista) ){ 
        novo->prox = NULL;
        novo->ant = NULL;
        lista->ini = lista->fim = novo;
    }
    else {
        novo->prox = NULL;
        novo->ant = lista->fim;
        lista->fim->prox = novo;
        lista->fim = novo;
    }

    return 1;
}

//printar mao do jogador

void imprime_listad(tp_listad *lista) {
    if (lista==NULL)printf("Lista não inicializada.");
    else {
        int i = 1;
        tp_no *atu;
        printf("============== Mão do Jogador ==============\n\n");
        atu = lista->ini;
        while (atu != NULL) {
            printf("%d.: %s\n", i, atu->carta.nome);
            atu=atu->prox;
            i++;
        }
        printf("\n============================================\n\n");
    
    }

    printf("\n");
}


//remove um elemento da lista
int remove_listad (tp_listad *lista, int num){
    tp_no *atu;
    atu = lista->ini;
    for(int i = 0; i<num; i++){
        atu=atu->prox;
    }
    if ( atu == NULL) return 0;
    if (lista->ini == lista->fim) {
        lista->ini = lista->fim = NULL; 
        }
    else {
        if (lista->ini == atu) {
            lista->ini = atu->prox;
            atu->prox->ant = NULL;
        }
        else {
            if (lista->fim == atu) {
            lista->fim = atu->ant;
            atu->ant->prox = NULL;
            }
            else {
                atu->prox->ant = atu->ant;
                atu->ant->prox = atu->prox;
            }
        }
    }
    free(atu);
    return 1;
}

//retornar a carta escolhida, similar a função TOP da pilha
tp_cartas busca_listade(tp_listad *lista, int num){
    tp_no *atu;
    atu = lista->ini;
    for(int i = 0; i<num; i++) {
        atu=atu->prox;
        }
return atu->carta;
}

//criando a mao do jogador
void sacar_deck(tp_pilha *cartas_baralho, tp_listad *cartas_jogador) {

    tp_cartas deck;

    for (int i = 0; i < 5; i++) {

        pop(cartas_baralho, &deck);
        insere_listad_no_fim(cartas_jogador, deck);
    
  }
}




#endif