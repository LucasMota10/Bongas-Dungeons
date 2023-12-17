#ifndef COMBATE_H
#define COMBATE_H
#include <stdio.h>
#include "player.h"
#include "monstro.h"
#include "caminho.h"
#include "maojogador.h"
#include <string.h>
#include <stdlib.h>

#include "arte.h"


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
  if(monstro.tipo == 1)printf("Vida: %d/200                               |Vida: %d/400\n", jogador->vida,monstro.vida);
  else printf("Vida: %d/200                               |Vida: %d/200\n", jogador->vida,monstro.vida);
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


//Mecânica do combate
void initcombate(tp_player *player, tp_listad *c, tp_pilha *baralho, tp_pilha *descarte, tp_level *caminho){

  clear();

  tp_monstro monstro;
  tp_fila fila_monstro; acoes_monstro acao_monstro;
  tp_cartas carta_jogar;


  if(player->level == 6){//Cena final do jogo
    dialogo_final();

  }


  else if(caminho->info == 0){

    if(tamanho_listad(c) == 0)sacar_deck(baralho, c);
     //monstro E suas ações
    inicializa_fila(&fila_monstro); 
    
    const LPCSTR monstermsc;
    criarmonstro(&monstro, player); //Criando o monstro
    criar_acoes_monstro(&fila_monstro);
    
    switch (player->level)
    {
    case 1:
        const LPCSTR song1 = "./sounds/monstro1.wav";
        PlaySound(song1, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        break;

      case 2:

        const LPCSTR song2 = "./sounds/monstro2.wav";
        PlaySound(song2, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        break;
        
      case 3:
        const LPCSTR song3 = "./sounds/monstro3.wav";
        PlaySound(song3, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        break;
      case 4:
        const LPCSTR song4 = "./sounds/monstro4.wav";
        PlaySound(song4, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        break;
      case 5:

        printColoredText("Espera...", COLOR_CYAN);
        Sleep(TRES);

        clear();
        printColoredText("Tem algo de errado...", COLOR_CYAN);
      
        clear();
        printColoredText("Tem algo de errado... Entao, esse é o fim?", COLOR_CYAN);
        Sleep(TRES);

        clear();

        const LPCSTR passos = "./sounds/passos.wav";
        PlaySound(passos, NULL, SND_ASYNC | SND_FILENAME);
        

        const LPCSTR song5 = "./sounds/bossfinal.wav";
        Sleep(5000);
        PlaySound(song5, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        break;
    
      default:
        break;
    }

    int turno;

    while(player->vida > 0 && monstro.vida > 0){ //Se o player ou o monstro morrer, a vida acaba
      
      //system("cls");
      turno = 1; //O monstro só vai atacar quando acabar o turno do jogador
  
      do
      {
            
        if(monstro.vida <= 0){  //Verifica a vida do monstro
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
        
        if(i == 230102){

          monstro.vida = 0; //Comando secreto para dar insta kill no monstro, utilizado para testes com o código
          turno = 0; 
          break;
        }

        if(i==0){
          turno = 0;
          break;
        }

        if(!busca_listade(c, i-1, &carta_jogar))printf("Nao foi possível encontrar essa carta!\n"); //Não encontrou a carta do jogador
        else{
          
          if(usar_carta(carta_jogar, player, &monstro)){ //Verifica se tem mana o suficiente para jogar e usa a carta

            cartasupdate(player, carta_jogar, 1);
            clear();
            push(descarte, carta_jogar);
            remove_listad(c, i-1);
          }
        }

        //system("cls");
          
        } while (turno); // -  Do/While


          //Ataque do monstro

        if(monstro.vida <= 0)break;

        printf("Vez do monstro!\n");
        remove_fila(&fila_monstro, &acao_monstro);
        switch (acao_monstro.tipo) //Verifica se o monstro usou defesa, ataque ou cura
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

          //Reseta mana e escudo do jogador no fim do turno

          player->mana = 50;
          player->escudo = 0;

          limpar_restobaralho(c, descarte); //Jogando o resto das cartas da mão do jogador no baralho
          if(!pilha_vazia(baralho))sacar_deck(baralho, c); 
          
          //Caso tiver acabado a mão do jogador, vai pegar do descarte e embaralhar
          else{

            srand(time(NULL));
            remover_descarte(descarte,baralho, c);
            sacar_deck(baralho, c);
          }
          }

        //Verifica quem ganhou, o jogador ou o monstro

        if(player->vida <= 0){

          printf("Voce perdeu no level %d! Deseja continuar? [1 - Sim/2 - Não]\n\n", player->level);
          int resp;
          scanf("%d", &resp);
          if(resp == 1){

            player->vida = 200;
            monstro.vida = 200;
            
            caminho->existe.desvio = true;
            initcombate(player, c, baralho, descarte,caminho); //Recursividade para chamar o combate novamente

            }

          else{

            menu(player); //Voltando para o menu

          }
      }else{
          
          player->level += 1;
          playerupdate(player, player->nome);

          if(player->level != 6){
          printf("\n-----------------------------------------------------------------------------\n");
          printf("Parabens %s, Voce acaba de derrotar o monstro -%s-!\n",player->nome, monstro.name);
          printf("-----------------------------------------------------------------------------\n");

           //Atualiza o level do player
          
          playerupdate(player, player->nome);
         // adicionar_cartas(baralho); // VERIFICAR ERRO AQUI
          
          //so vai entrar nessa condicao aqui
          
          if(caminho->existe.desvio && player->level != 6){

          int x = 0;
          do{

            printf("Digite 1 para combater outro monstro!\nDigite 2 para ir ao descanso!\n");
            scanf("%d",&x);

            if(x != 1 && x != 2){
              x = 0;
              //system("cls");
              printf("Não foi possivel identificar o numero que escolheu, por favor digite novamente.\n");
            }
          }
          while(!x);

            caminho->info = x-1;

            caminho->existe.desvio = false;

            novolevel(&caminho, player->level, x-1);
            initcombate(player, c, baralho, descarte,caminho);
          }

          else{
            
            caminho->info = 0;
            caminho->existe.desvio = true;

            novolevel(&caminho, player->level, 0);
            initcombate(player, c, baralho, descarte,caminho);
            

          }
        }
        else{
          dialogo_final();
        }

      }

  }

  else if(caminho->info == 1 && player->level != 6){

    const LPCSTR parada = "./sounds/break.wav";
    PlaySound(parada, NULL, SND_ASYNC | SND_FILENAME);
    player->vida = 200;
    player->mana = 50;

    clear();

    printColoredText("Voce encontrou um quarto abandonado e resolveu tirar um cochilo.", COLOR_GREEN);
    Sleep(UM);
    clear();
    
    printColoredText("Voce encontrou um quarto abandonado e resolveu tirar um cochilo..", COLOR_GREEN);
    Sleep(UM);
    clear();
    
    printColoredText("Voce encontrou um quarto abandonado e resolveu tirar um cochilo...", COLOR_GREEN);
    Sleep(UM);
    clear();
    
    printColoredText("Voce encontrou um quarto abandonado e resolveu tirar um cochilo... Vida e mana recuperadas!", COLOR_GREEN);
    Sleep(TRES);

    caminho->info = 0;
    caminho->existe.desvio = true;

    player->level += 1; //Atualiza o level do player  
    
    playerupdate(player, player->nome);

    novolevel(&caminho, player->level, 0);
    initcombate(player, c, baralho, descarte,caminho);



  }


      //descanso

}





#endif