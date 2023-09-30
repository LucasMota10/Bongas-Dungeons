#include "arte.h"
#include "carta.h"
#include "menu.h"
#include "monstro.h"
#include "player.h"
#include "stdio.h"
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese"); // Jogo em português

    tp_player jogador; // jogador

    if(menu(&jogador)){ // Retorna 1 se o jogador quiser iniciar o Jogo

        tp_monstro monstro; //  monstro

        tp_level *levels; // caminho do jogador

        tp_fila fila_monstro; // fila de ações do monstro

        tp_pilha cartas_baralho; // (baralho do jogo)

        tp_cartas cartas_jogador[5]; // Mão do jogador, segura 5 cartas

        inicializa_fila(&fila_monstro); // inicializa a fila de ações do monstro

        inicializa_pilha(&cartas_baralho); // inicializa o baralho

        criar_cartas(&cartas_baralho); // cria as cartas jogo que foram predefinidias e insere aleatoriamente na pilha

        sacar_deck(&cartas_baralho, cartas_jogador); // insere as 5 cartas do topo da pilha do baralho na mão do jogador

        imprime_player(jogador, cartas_jogador); // Imprime os stats do jogador (Nome,Vida,Mana e escudo) e também as cartas em sua mão

        levels = inicializa_level(); // Como é uma fila, define o levels como nulo

        novolevel(&levels, 1, 0); //   

        criarmonstro(&monstro, levels); // cria os monstros

        criar_acoes_monstro(&fila_monstro); // define as ações do monstro e randomiza ela em uma fila.

        printar_monstro(monstro, &fila_monstro); // imprime os stats do monstro(Nome, Vida e escudo), além do seu proximo movimento

        imprime_acoes_monstro(fila_monstro); // imprime o valor do ataque do monstro ou o valor da defesa ou o valor do especial, dependendo do tipo da sua proxima ação  
    }

    return 0;

}