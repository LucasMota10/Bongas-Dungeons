#ifndef COMBATE_H
#define COMBATE_H
#include <stdio.h>
#include "player.h"
#include "monstro.h"
#include "caminho.h"
#include "maojogador.h"
#include <string.h>


void remover_descarte(tp_pilha *descarte, tp_pilha *baralho, tp_listad *c){  
  int size = altura_pilha(descarte);
  tp_cartas carta[10];
  int i=0;

  while(!pilha_vazia(descarte)){
    pop(descarte, &carta[i]);
    i++;
 
  }
  tp_cartas auxc;
  for (int k = 0; k < size; k++) { // shuffle array
    int random = rand() % size;
    auxc = carta[k];
    carta[k] = carta[random];
    carta[random] = auxc;
  }


  for (int j = 0; j < size; j++){
    push(baralho, carta[j]);
  }


}

int usar_carta(tp_cartas cartas_jogador, tp_player *jogador, tp_monstro *monstro) {
  
  if (!checar_custo(jogador, cartas_jogador)) {
    printf("Mana insuficiente.\n");
    return 0;
  } else {

    jogador->mana = jogador->mana - cartas_jogador.mana;
    switch (cartas_jogador.tipodacarta) { //SWITCH CASE
    case 0:

      monstro->escudo -= cartas_jogador.power;
      if(monstro->escudo < 0){
        monstro->vida +=monstro->escudo;
        monstro->escudo = 0;
      }
      break;

    case 1:
      if(jogador->escudo + cartas_jogador.power > 50)jogador->escudo = 50;
      else{jogador->escudo += cartas_jogador.power;}
      break;

    case 2:
      if(jogador->vida + cartas_jogador.power > 200)jogador->vida = 200;
      else{jogador->vida + cartas_jogador.power;};
      break;
    default:
      printf("Ocorreu algum erro ao executar o programa.\n tente novamente\n");
      break;
    }

  return 1;
  }
}

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

void imprime_combate(tp_player *jogador, tp_listad *carta, tp_monstro monstro, tp_fila *fila) {

  acoes_monstro acao;  
  ultima_acao(fila, &acao);
  
  printf("====================================================================================\n");
  printf("Nome: %s                                |Monstro: %s\n", jogador->nome,monstro.name);
  printf("Vida: %d/200                               |Vida: %d/200\n", jogador->vida,monstro.vida);
  printf("Mana: %d/50                                 |Escudo: %d/50\n", jogador->mana,monstro.escudo);
  printf("Escudo: %d/50                                |Proximo Movimento: ", jogador->escudo);

  switch (acao.tipo)
    {
    case 0:
        printf("Ataque\n");
        break;
    case 1:
        printf("Defesa\n");
        break;
    case 2:
        printf("Cura\n");
        break;
    default:
        break;
    }
  printf("====================================================================================\n\n");
  imprime_listad(carta);
}

//mecânica do combate
void initcombate(tp_player *player, tp_level *level, tp_listad *c, tp_pilha *baralho, tp_pilha *descarte){
    
    if(tamanho_listad(c) == 0)sacar_deck(baralho, c);
    tp_monstro monstro; //monstro E suas ações
    tp_fila fila_monstro; acoes_monstro acao_monstro;
    tp_cartas carta_jogar;

    inicializa_fila(&fila_monstro);

    if(level->tipo == 0){//SE O LEVEL FOR DE COMBATE -> INICIAR LUTA
        
        criarmonstro(&monstro, level); //Criando o monstro
        criar_acoes_monstro(&fila_monstro);


        int turno;
        while(player->vida > 0 && monstro.vida > 0){ //SE O PLAYER OU O MONSTRO MORRER, A LUTA ACABA
          turno = 1;
          //uso da carta
          do
          {
            
            if(monstro.vida <= 0){
              turno = 0;
              break;
            }

            if(listad_vazia(c)){
              turno = 0;
              break;
            }

           imprime_combate(player,c,monstro,&fila_monstro);

            printf("Baralho: %d Descarte: %d\n\n", altura_pilha(baralho), altura_pilha(descarte));

            printf("----- Digite de 1 a 5 para escolher qual carta vai utilizar\n----- Digite 0 para encerrar o turno\n");
            int i;
            scanf("%d", &i);
            if(i==0){
              turno = 0;
              break;
            }
            if(!busca_listade(c, i-1, &carta_jogar))printf("Nao foi possível encontrar essa carta!\n");
            else{
            if(usar_carta(carta_jogar, player, &monstro)){
              push(descarte, carta_jogar);
              remove_listad(c, i-1);
            }
            }
          } while (turno);
          //ATAQUE MONSTRO

          if(monstro.vida <= 0)break;

          printf("Vez do monstro!\n");
          remove_fila(&fila_monstro, &acao_monstro);
          switch (acao_monstro.tipo)
          {
          case 0:

            printf("O monstro atacou o %s e causou %d de dano!\n", player->nome, acao_monstro.valor);
            
            player->escudo -= acao_monstro.valor;
            if(player->escudo < 0){
              player->vida += player->escudo;
              player->escudo = 0;

            }
            break;
          case 1:
            printf("O monstro usou o escudo e ganhou %d de protecao!\n", acao_monstro.valor);
            if(monstro.escudo + acao_monstro.valor > 30)monstro.escudo = 30;
            else{monstro.escudo += acao_monstro.valor;}
            break;
          case 2:
            printf("O monstro se curou e ganhou %d de vida!\n", acao_monstro.valor);
            if(monstro.vida + acao_monstro.valor > 200)monstro.vida = 200;
            else{monstro.vida += acao_monstro.valor;}
          default:
            break;
          }

          insere_fila(&fila_monstro, acao_monstro);

          //RESETAR MANA DO JOGADOR

          player->mana = 50;
          player->escudo = 0;
          //FIM DA RODADA 

          limpar_restobaralho(c, descarte);
          if(!pilha_vazia(baralho))sacar_deck(baralho, c);
          else{

            srand(time(NULL));
            remover_descarte(descarte,baralho, c); //verificar erro
            sacar_deck(baralho, c);
          }

          }

        //VERIFICAR QUEM GANHOU, O JOGADOR OU O MONSTRO
        if(player->vida <= 0){

          printf("Voce perdeu no level %d! Deseja continuar? [1 - Sim/2 - Não]\n\n", player->level);
          int resp;
          scanf("%d", &resp);
          if(resp == 1){

            player->vida = 200;
            monstro.vida = 200;

            initcombate(player, level, c, baralho, descarte);}

          else{

            menu(player);
          }

        }
        else{
          printf("\n-----------------------------------------------------------------------------\n");
          printf("PARABENS %s, VOCE ACABA DE DERROTAR O PRIMEIRO MONSTRO\n",player->nome);
          printf("PROXIMO MES VOCE PODERA DERROTAR OS OUTROS MONSTROS E CONCLUIR SUA JORNADA\n");
          printf("-----------------------------------------------------------------------------\n");
          player->level += 1;
          playerupdate(player, player->nome);

          adicionar_cartas(baralho); // VERIFICAR ERRO AQUI


        }
          
    }
    //REPOUSO

    if(level->tipo == 1);
}



#endif