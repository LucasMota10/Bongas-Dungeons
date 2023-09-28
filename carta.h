#ifndef carta_h
#define carta_h
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "pilha.h"

//tipo de carta por num (0==ataque , 1==defesa , especial == 2)

//cartas do deck
void criar_cartas(tp_pilha *pilha){

tp_cartas cartas[12];

//cartas de ataque

strcpy(cartas[0].nome,"Bola de Fogo");
cartas[0].tipodacarta = 0;
cartas[0].power = 10;
cartas[0].mana = 20;

strcpy(cartas[1].nome,"Soco");
cartas[1].tipodacarta = 0;
cartas[1].power = 5;
cartas[1].mana = 5;

strcpy(cartas[2].nome,"Flecha da tormenta");
cartas[2].tipodacarta = 0;
cartas[2].power = 15;
cartas[2].mana = 10;

strcpy(cartas[3].nome,"Sistemas Digitais");
cartas[3].tipodacarta = 0;
cartas[3].power = 25;
cartas[3].mana = 30;

//cartas de defesa

strcpy(cartas[4].nome,"Camisa Laranja");
cartas[4].tipodacarta = 1;
cartas[4].mana = 10;
cartas[4].escudo = 20;

strcpy(cartas[5].nome,"Lando Lando");
cartas[5].tipodacarta = 1;
cartas[5].mana = 15;
cartas[5].escudo = 30;

strcpy(cartas[6].nome,"Obrigado Soussa");
cartas[6].tipodacarta = 1;
cartas[5].mana = 5;
cartas[5].escudo = 20;

strcpy(cartas[7].nome,"Pato");
cartas[7].tipodacarta = 1;
cartas[7].mana = 50;
cartas[7].escudo = 30;

// cartas de especial

strcpy(cartas[8].nome,"Lanche no garfo de ouro");
cartas[8].tipodacarta = 2;
cartas[8].vida = 20;
cartas[8].mana = 10;

strcpy(cartas[9].nome,"Neneca no cyber");
cartas[9].tipodacarta = 2;
cartas[9].vida = 50;
cartas[9].mana = 30;

strcpy(cartas[10].nome,"Masterizou AED");
cartas[10].tipodacarta = 2;
cartas[10].mana = 0;
cartas[10].regmana = 60;

strcpy(cartas[11].nome,"Sabedoria suprema");
cartas[11].tipodacarta = 2;
cartas[11].power = 10;
cartas[11].mana = 10;
cartas[11].vida = 10;
cartas[11].escudo = 10;

//Atribuindo os niveis das cartas
int lvl = 1;
for(int i = 0 ; i<12 ; i++){
    cartas[i].level = lvl;
    lvl++;
    if(lvl>4) lvl = 1;
}

//Função preencher pilha:
srand(time(NULL));
for (int i = 0; i < 12; i++) {    // shuffle array
    
    int random = rand()%11;
    push(pilha, cartas[random]);

}
}

#endif