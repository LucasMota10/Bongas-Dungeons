#ifndef COMBATE_H
#define COMBATE_H
#include <stdio.h>
#include "player.h"
#include "monstro.h"
#include "caminho.h"
#include "maojogador.h"
#include <string.h>
#include <stdlib.h>


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
void initcombate(tp_player *player, tp_listad *c, tp_pilha *baralho, tp_pilha *descarte, tp_listade *caminho){

    tp_nos *atu;
    atu = caminho->ini;
    tp_nos *ant = NULL;
    tp_nos *prox = NULL;
    tp_monstro monstro;
    tp_fila fila_monstro; acoes_monstro acao_monstro;
    tp_cartas carta_jogar;

    while(1){

      if(atu->info == 'E'){
        if(tamanho_listad(c) == 0)sacar_deck(baralho, c);
     //monstro E suas ações
        inicializa_fila(&fila_monstro); 
        
        criarmonstro(&monstro, player); //Criando o monstro
        criar_acoes_monstro(&fila_monstro);

        int turno;
        while(player->vida > 0 && monstro.vida > 0){ //SE O PLAYER OU O MONSTRO MORRER, A LUTA ACABA
        system("cls");
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

            initcombate(player, c, baralho, descarte,caminho);
            }
          else{
            menu(player);
          }
      }else{
          printf("\n-----------------------------------------------------------------------------\n");
          printf("PARABENS %s, VOCE ACABA DE DERROTAR O MONSTRO -%s-\n",player->nome, monstro.name);
          printf("-----------------------------------------------------------------------------\n");
          player->level += 1;
          //playerupdate(player, player->nome);

          //adicionar_cartas(baralho); // VERIFICAR ERRO AQUI
           int x = 0;
          do{
        printf("Parabens Pela vitoria! Escolha uma das opcoes para continuar sua jornada\nDigite (1) para descansar e recuperar suas energias!\nDigite (2) para combater outro monstro!\n");
        scanf("%d",&x);
        if(x == 1){
            while(atu->info != 'D'){
              atu = atu->prox;
              }
              ant = atu->ant;
              if(ant->info != 'E'){
                ant = ant->ant;
              }
              atu->ant = ant;
              ant->prox = atu;
              prox = atu->prox;
              while(prox->info != 'E'){
                prox = prox->prox;
              }  
              atu->prox = prox;
              atu = prox;           
              //manipulação para que o proximo elemento do caminho seja um descanso
        }else{
            if(x == 2){
              while(atu->info != 'C'){
              atu = atu->prox;
              }
              ant = atu->ant;
              if(ant->info != 'E'){
                ant = ant->ant;
              }
              atu->ant = ant;
              ant->prox = atu; 
              while(prox->info != 'E'){
                prox = prox->prox;
              }
                atu->prox = prox;
                atu = prox; 
                //manipulação para que o proximo elemento do caminho seja um combate
            }
            else{
                printf("Digite um numero valido!\n");
            }
        }
        }while(x != 1 || x != 2);

        } //venceu
    
        } // escolha
        else{
          if(atu->info == 'C'){
            if(tamanho_listad(c) == 0)sacar_deck(baralho, c);
     //monstro E suas ações
        inicializa_fila(&fila_monstro); 
        
        criarmonstro(&monstro, player); //Criando o monstro
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

            initcombate(player, c, baralho, descarte,caminho);
            }
          else{
            menu(player);
          }
      }else{
          printf("\n-----------------------------------------------------------------------------\n");
          printf("PARABENS %s, VOCE ACABA DE DERROTAR O MONSTRO -%s-\n",player->nome, monstro.name);
          printf("-----------------------------------------------------------------------------\n");
          player->level += 1;
          atu = atu->prox;
          playerupdate(player, player->nome);

          adicionar_cartas(baralho); // VERIFICAR ERRO AQUI
          }
        } // C
        else{
          if(atu->info == 'D'){
            player->vida = 200;
            printf("Voce encontrou um quarto abandonado e resolveu tirar um cochilo - Vida e mana Recuperadas! - \n");
            atu = atu->prox;
          }
        }
    } // while
} // initcombate
}



#endif