#ifndef player_h
#define player_h
#include <stdio.h>
#include "pilha.h"

typedef struct{
char nome[50];
int vida, mana, escudo;

}tp_player;

void sacar_deck(tp_pilha *cartas_baralho, tp_pilha *cartas_jogador){

tp_cartas deck;
for(int i = 0; i<5; i++){

    pop(cartas_baralho, &deck);
    push(cartas_jogador, deck);
}
}

void imprime_deck(tp_pilha cartas_jogador){
imprime_pilha(cartas_jogador);
}

void imprime_player(tp_player jogador, tp_pilha pilha){
printf("Nome: %s\n", jogador.nome);
printf("Vida: %d/100 \n", jogador.vida);
printf("Mana: %d/50 \n", jogador.mana);
printf("Escudo: %d/50 \n", jogador.escudo);
imprime_pilha(pilha);
}

int checar_custo(tp_player *jogador, tp_pilha *e){

tp_cartas j;

top(e, &j);
if(j.mana > jogador->mana) return 0;
return 1;
}

void usar_cartas(tp_pilha *cartas_jogador, tp_player *jogador){
tp_cartas e;

if(!checar_custo(jogador, cartas_jogador)){
     printf("Mana insuficiente\n");
}
else{

pop(cartas_jogador, &e);
jogador->mana = jogador->mana - e.mana;
switch (e.tipodacarta)
{
case 0:
    /* code */
    break;

case 1:
    /* code */
    break;

case 2:
    /* code */
    break;
default:
    break;
}
}
}

#endif