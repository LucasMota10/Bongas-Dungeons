#ifndef menu_h
#define menu_h
#include <stdio.h>
#include "player.h"
#include "carta.h"

int menu(tp_player *jogador){
printf(" #################################################\n # #\n # #\n # #\n # Digite: 1- Novo Jogo 2- Encerrar Jogo #\n # #\n # #\n # #\n #################################################\n\n\n");

int i; 
scanf("%d", &i);
if(i==1){
    printf("Qual será o nome do jogador?\n");
    scanf(" %[^\n]s", jogador->nome);

    printf("Bem vindo, %s!", jogador->nome);

    return 1;
}
 
return 0;
}

#endif