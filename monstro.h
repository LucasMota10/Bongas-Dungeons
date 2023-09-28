#ifndef monstro_h
#define monstro_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Fila.h"
#include "carta.h"
#include "player.h"

typedef struct{
char name[30];
int vida = 200;
int escudo, tipo;

} monsters;

typedef struct{
char tipo[10]; // Ataque, Defesa, Especial
int valor; // Poder
} acoes;

// ● A ação do monstro deve ser apresentada ao jogador no começo da rodada. Entretanto, ela só é realizada no final da rodada.

void start_acoes(tp_fila *fila, acoes *a){
insere_fila(fila, &a);
}

int acoes_monstro(monsters *monstro, tp_fila *fila, acoes *a, player *jogador){
remove_fila(fila, a);
switch(a->tipo){
case 'Ataque':
ataque_monstro(jogador, a);
break;

    case 'Defesa':
        monstro->escudo += a->valor;
        break;
    
    case 'Especial':
        // ???
        break;
    
    default:
        break;
}
queue(fila, &a);
}

int monstro_morto(monsters *monstro){
if(monstro->vida <= 0) return 1;
return 0;
}

int ataque_monstro(player *jogador, acoes *a){
if(jogador->escudo > 0){
if(jogador->escudo > a->valor){
jogador->escudo -= a->valor;
}
else if(jogador->escudo = a->valor){
jogador->escudo = 0;
}
}
else if(jogador->escudo = 0){
jogador->vida -= a->valor;
}
}

int defesa_monstro(monsters *monstro, acoes *a){
if(monstro->escudo > 0){
if(monstro->escudo > a->valor){
monstro->escudo -= a->valor;
}
else if(monstro->escudo = a->valor)
monstro->escudo = 0;
}

    return 0;
}
else if(monstro->escudo = 0){
    monstro->vida -= a->valor;
    monstro_morto(monstro);
    
    return 1;
}
}

int tipo_monstro(monsters *monstro){
// Tipos: Regeneracao, Drenagem de mana, Mimetismo
}

#endif