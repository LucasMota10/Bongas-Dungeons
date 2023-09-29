#ifndef menu_h
#define menu_h
#include "carta.h"
#include "player.h"
#include "monstro.h"
#include <stdio.h>
#include "arte.h"

int menu(tp_player *jogador) {
  asciiart();
  printf(" #################################################\n # #\n # #\n # "
         "#\n # Digite: 1- Novo Jogo 2- Encerrar Jogo #\n # #\n # #\n # #\n "
         "#################################################\n\n\n");

  int i;
  scanf("%d", &i);
  if (i == 1) {
    printf("Qual será o nome do jogador?\n");
    scanf(" %[^\n]s", jogador->nome);


    printf("Bem vindo, %s!\n\n", jogador->nome);
    
    printf("\n");

    criarplayer(jogador);

    return 1;
    }

  return 0;
}



#endif