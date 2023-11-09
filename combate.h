#ifndef combate_h
#define combate_h
#include <stdio.h>
#include "player.h"
#include "monstro.h"
#include "caminho.h"
#include "maojogador.h"


int remover_descarte(tp_pilha *descarte, tp_pilha *baralho, tp_listad *c){  
  tp_cartas carta[10];
  int i=0;
  while(!pilha_vazia(descarte)){
    pop(descarte, &carta[i]);
    i++;
 
  }

  srand(time(NULL));
  for (int k = 0; k < 10; k++) { // shuffle array
    tp_cartas aux;
    int random = rand() % 11;
    aux = carta[k];
    carta[k] = carta[random];
    carta[random] = aux;
  }


  for (int j = 0; j < 10; j++){
    push(baralho, carta[j]);
  }

  
  sacar_deck(baralho, c);
  printf("Status da lista: %d\n", listad_vazia(c));
  printf("Lista após sacar mão:\n");
  imprime_listad(c);
  
  return 1;
}


void usar_carta(tp_cartas cartas_jogador, tp_player *jogador, tp_monstro *monstro) {
  /*
  if (!checar_custo(jogador, cartas_jogador)) {
    printf("Mana insuficiente.\n");
  } else {
*/
    jogador->mana = jogador->mana - cartas_jogador.mana;
    switch (cartas_jogador.tipodacarta) { //SWITCH CASE
    case 0:
      monstro->vida -= cartas_jogador.power;
      break;

    case 1:
      jogador->escudo += cartas_jogador.power;
      break;

    case 2:
      jogador->vida += cartas_jogador.power;
      break;
    default:
      printf("Ocorreu algum erro ao executar o programa.\n tente novamente\n");
      break;
    }


  }
//}

void configcarta(tp_cartas carta){
  switch (carta.tipodacarta) { //SWITCH CASE
    case 0:
      printf("Nome: %s\nTipo: Combate\nPoder: %d\nMana: %d\n", carta.nome, carta.power, carta.mana);
      break;

    case 1:
      printf("Nome: %s\nTipo: Defesa\nPoder: %d\nMana: %d\n", carta.nome, carta.power, carta.mana);
      break;

    case 2:
      printf("Nome: %s\nTipo: Especial\nPoder: %d\nMana: %d\n", carta.nome, carta.power, carta.mana);
}

}
//mecânica do combate
void initcombate(tp_player *player, tp_level *level, tp_listad *c, tp_pilha *baralho, tp_pilha *descarte){
    
    sacar_deck(baralho, c);
    tp_monstro monstro; //monstro E suas ações
    tp_fila fila_monstro;
    tp_cartas carta_jogar;

    inicializa_fila(&fila_monstro);

    if(level->tipo == 0){//SE O LEVEL FOR DE COMBATE -> INICIAR LUTA
        
        criarmonstro(&monstro, level); //Criando o monstro
        criar_acoes_monstro(&fila_monstro);

        while(player->vida > 0 && monstro.vida > 0){ //SE O PLAYER OU O MONSTRO MORRER, A LUTA ACABA
          
          //uso da carta
            if(!listad_vazia(c)){

              printar_monstro(monstro, &fila_monstro);
              imprime_player(player, c);
              printf("Digite de 1 a 5 para escolher qual carta vai utilizar.\n\n");
              int i;
              scanf("%d", &i);
              

              carta_jogar = busca_listade(c, i-1);
              configcarta(carta_jogar);
              usar_carta(carta_jogar, player, &monstro);
              

          //descarte da carta
              push(descarte, carta_jogar);
              remove_listad(c, i-1);
                if(!pilha_vazia(baralho)){
                pop(baralho, &carta_jogar);
                insere_listad_no_fim(c, carta_jogar);
              }
            }
            else{
              printf("Chegou no else\n");
              if(!remover_descarte(descarte, baralho, c))printf("erro\n"); //ERRO
              printf("Debug\n");
            }
            
       
          }
        //VERIFICAR QUEM GANHOU, O JOGADOR OU O MONSTRO
            
    }
}

#endif