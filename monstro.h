#ifndef monstro_h
#define monstro_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    char nome[20];
    int vida = 0,escudo = 0;
    
}monsters;

typedef struct {
    int dano;
    int escudo;
}deck_monstro; // CRIAR AS ACOES DOS MONSTROS


void criar_monstro(){
    monsters monstro[3];
    
    strcpy(monstro[0].nome, "Serpente Python");
    monstro[0].vida = 200;

    strcpy(monstro[1].nome, "Adam Sandler");
    monstro[1].vida = 300;

    strcpy(monstro[2].nome, "Monstro Recursivo");
    monstro[2].vida = 500;
}


#endif