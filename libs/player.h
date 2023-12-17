#ifndef player_h
#define player_h
#include "carta.h"
#include "caminho.h"
#include "maojogador.h"
#include <stdio.h>
#include <dirent.h>

#include <conio.h>
#include "utils.h"
#include "arte.h"

typedef struct {
  char nome[30];
  int vida, mana, escudo, level; // 200 de vida, 50 de mana, 0 de escudo

} tp_player;

void criarplayer(tp_player *jogador) {
  jogador->vida = 200;
  jogador->mana = 50;
  jogador->escudo = 0;
  jogador->level = 1;
  
}

int cartasupdate(tp_player *jogador, tp_cartas carta, int modo){
  
  char direcartas[100] = "./data/player/";

  strcat(direcartas, jogador->nome);
  strcat(direcartas, "_save");
  strcat(direcartas, ".txt");

  FILE *savecartas = fopen(direcartas, "a");

  switch (modo)
  {
  case 1:
    fprintf(savecartas, "Carta usada: %s Nivel: %d\n", carta.nome, jogador->level);
    break;
  case 2:
    char linha[100];
    while(fscanf(savecartas, " %[^\n]s", linha)){
      printf("%s", linha);
    }
  default:
    break;
  }
  
  fclose(savecartas);


}




int playerupdate(tp_player *jogador, char *nome){
  
  char direc[60] = "./data/player/";

  strcat(direc, nome);
  

  
  strcat(direc, ".dat");

  

  FILE *update = fopen(direc, "w+");
  if(!update)return 0;

  strcpy(jogador->nome, nome);
  fprintf(update, "%s\n", jogador->nome);
  fprintf(update, "%d %d %d %d\n", jogador->vida, jogador->mana, jogador->escudo, jogador->level);



  fclose(update);

  return 1;
}

void carregarjogador(tp_player *jogador, FILE *arquivo){
  char nome[30];

  fscanf(arquivo, " %[^\n]s", nome);
  strcpy(jogador->nome, nome);

  fscanf(arquivo, "%d %d %d %d", &jogador->vida, &jogador->mana, &jogador->escudo, &jogador->level);

}

int start(tp_player *jogador){
  text();
  asciiart();
  menu(jogador);
}


int menu(tp_player *jogador) {

  clear();
  
  const LPCSTR menusong = "./sounds/menu.wav";
  PlaySound(menusong, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
  printColoredText("#################################################################################\n"
         "#                                                                               #\n" 
         "#                                                                               #\n" 
         "#                                                                               #\n" 
         "#     1- Novo Jogo 2- Carregar Jogo 3- Deletar Jogo 4-Instrucoes 5- Encerrar    #\n" 
         "#                                                                               #\n" 
         "#                                                                               #\n" 
         "#                                                                               #\n" 
         "#################################################################################\n\n\n", COLOR_YELLOW);

  int i, k, pos = 0;

  char names_save[5][30];
  char direc[60] = "./data/player/";

  scanf("%d", &i);

  DIR *saves;
  struct dirent *dir;
  const LPCSTR parada = "./sounds/break.wav";
  switch (i)
  {
  case 1:

  
  //VERIFICAR SE POSSUI MAIS DE 5 SAVES
    pos = 0;
    saves = opendir(direc);
    while((dir = readdir(saves)) != NULL){
      if(strstr(dir->d_name, ".dat"))pos++;
    }
    if(pos==5){
      printColoredText("\n\nLimite Máximo de 5 saves atingido!\n", COLOR_RED);
      Sleep(5000);
      menu(jogador);
      return 1;
    }
    closedir(saves);

    char nome[30];

    printf("Qual sera o nome do jogador? (recomendado nome com 6 caracteres)\n");
    scanf(" %26[^\n]s", nome);


    strcat(direc, nome);

    strcat(direc, ".dat");

    FILE *newgame = fopen(direc, "w");
    if(!newgame)return 0;
    fclose(newgame);

    criarplayer(jogador);

    if(!playerupdate(jogador, nome))printf("Ocorreu algum erro ao atualizar o jogador.\n");

    
    printColoredText("------------------------------------------------------\n", COLOR_CYAN);
    printf("%sBem Vindo, %s%s%s!\n", COLOR_CYAN, COLOR_GREEN, jogador->nome, COLOR_CYAN);
    Sleep(UM);
    printColoredText("Voce esta Adentrando em um Mundo Repleto de Tesouros e Misterios\n", COLOR_CYAN);
    Sleep(DOIS);
    printColoredText("Derrote o Seguinte Monstro para Prosseguir:\n------------------------------------------------------\n", COLOR_CYAN);
    Sleep(5000);

    
    PlaySound(parada, NULL, SND_ASYNC | SND_FILENAME);
    return 1;
    break;
  
  case 2:
    
    clear();
    saves = opendir(direc);
    if(!saves)printf("Ocorreu erro ao abrir o diretorio dos saves\n");

    pos = 0;
    printf("######### SAVES #########\n\n");
    k = 0;
    while((dir = readdir(saves)) != NULL){
      
      if(pos == 5)break;

      if(dir->d_name[strlen(dir->d_name)-1] == 't' && dir->d_name[strlen(dir->d_name)-2] == 'a'){

        strcpy(names_save[k], dir->d_name);

        printf("%d.: ", pos+1);
        for(int i=0; i<strlen(dir->d_name)-4; i++)printf("%c", dir->d_name[i]);
        printf("\n\n");
        pos++;
        k++;
        }


    }
    closedir(saves);

    if(pos == 0){
      printColoredText("Nao existe nenhum save para carregar!\n\n", COLOR_RED);
      Sleep(3000);
      menu(jogador);
      return 1;
    }

    printf("Digite qual save deseja carregar [1/5]\n\n");
    int load;

    scanf("%d", &load);
    strcat(direc, names_save[load-1]);

    printf("%s\n", direc);

    FILE *carregargame = fopen(direc, "r");;

    if(!carregargame)printf("Ocorreu erro ao abrir o diretório dos saves\n");
    
    clear();
    carregarjogador(jogador, carregargame);
    
    printColoredText("------------------------------------------------------\n", COLOR_CYAN);
    printf("%sBem Vindo, %s%s%s!\n", COLOR_CYAN, COLOR_GREEN, jogador->nome, COLOR_CYAN);
    Sleep(UM);
    printColoredText("Voce esta Adentrando em um Mundo Repleto de Tesouros e Misterios\n", COLOR_CYAN);
    Sleep(DOIS);
    printColoredText("Derrote o Seguinte Monstro para Prosseguir:\n------------------------------------------------------\n", COLOR_CYAN);
    Sleep(DOIS);
    PlaySound(parada, NULL, SND_ASYNC | SND_FILENAME);
    return 1;


  case 3:
    
    clear();
    saves = opendir(direc);
       if (!saves)
      printf("Ocorreu erro ao abrir o diretorio dos saves\n");

    pos = 0;
    printf("######### SAVES #########\n\n");
    k = 0;
    while ((dir = readdir(saves)) != NULL)
    {

      if (pos == 5)
        break;

      if (dir->d_name[strlen(dir->d_name) - 1] == 't' && dir->d_name[strlen(dir->d_name) - 2] == 'a')
      {

        strcpy(names_save[k], dir->d_name);

        printf("%d.: ", pos + 1);
        for (int i = 0; i < strlen(dir->d_name) - 4; i++)
          printf("%c", dir->d_name[i]);
        printf("\n\n");
        pos++;
        k++;
      }
    }

    closedir(saves);

    if (pos == 0)
    {
      printf("Nao existe nenhum save para  deletar,  crie um save antes!\n\n");
      menu(jogador);
      return 1;
    }

    printf("Digite qual save deseja deletar [1/5]\n\n");


    scanf("%d", &load);
    strcat(direc, names_save[load - 1]);

    if(remove(direc) == 0){

      printf("save removido com sucesso! aperte qualquer coisa para continuar...\n");

    }else printf("erro ao deletar o save, aperte qualquer coisa para continuar...\n");

    getch();
    menu(jogador);

    break;
  
  case 4:

    clear();
    printColoredText("----------------------------------------------------------------\n\n", COLOR_CYAN);
    printColoredText("Ao Iniciar o Jogo, seu Deck eh Gerado Aleatoriamente, Contendo Diversas Cartas que Possuem seu Proprio Tipo, podendo ser: Dano, Cura ou Escudo\n\n", COLOR_CYAN);
    Sleep(DOIS);
    printColoredText("Seu Objetivo eh Derrotar Todos os Monstros sem Zerar sua Vida!\n Para isso voce Deve Utilizar as Cartas Mencionadas em Seu Deck, Podendo usar Todas ate sua Mana acabar ou Acabar seu Turno!", COLOR_CYAN);
    Sleep(DOIS);
    printColoredText("\n\nBoa Sorte Aventureiro!\n\n", COLOR_CYAN);
    printColoredText("----------------------------------------------------------------\n\n", COLOR_CYAN);
    printColoredText("Digite qualquer tecla para voltar ao menu...", COLOR_YELLOW);
    getch();
    menu(jogador);
    return 1;
    break;

  case 5:
    return 0;
    break;
  default:

    system("cls");
    printf("Caractere Invalido ;-;, Digite outro numero!\n");
    menu(jogador);
    return 1;
    break;
  }


}

int checar_custo(tp_player *jogador, tp_cartas e) {

  if (e.mana > jogador->mana) return 0;
  return 1;
}
#endif
