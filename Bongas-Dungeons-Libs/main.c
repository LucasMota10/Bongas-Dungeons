#include "libs/player.h"
#include <stdio.h>
#include <locale.h>
#include "libs/maojogador.h"
#include "libs/combate.h"
#include "libs/caminho.h"
#include <windows.h>

int main() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    setlocale(LC_ALL,"");
    tp_player player; //Jogador
    tp_listade *caminho;
    caminho = inicializa_listade();
    criacaminho(caminho);


//LOAD DATA
    if (start(&player)) {

    //Deck
        tp_pilha cartas_baralho, cartas_descarte;
        tp_listad *maojogador;
        maojogador = inicializa_listad();

        inicializa_pilha(&cartas_baralho);
        inicializa_pilha(&cartas_descarte);
        criar_cartas(&cartas_baralho, 10);



        //imprime_pilha(cartas_baralho);
    //PRIMEIRO LEVEL

    //INICIANDO COMBATE
        initcombate(&player, maojogador, &cartas_baralho, &cartas_descarte,caminho);

    }
    return 0;
}
