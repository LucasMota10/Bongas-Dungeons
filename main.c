#include "libs/player.h"
#include <stdio.h>
#include <locale.h>
#include "libs/maojogador.h"
#include "libs/combate.h"
#include "libs/caminho.h"
#include <windows.h>

int main() {

    setlocale(LC_ALL,"");
    
    tp_player player; //Jogador
    tp_level *caminho;
    
    
    caminho = inicializa_level();

    novolevel(&caminho, 0, 0); 

//LOAD DATA

    if (start(&player)) {

    //Deck
        tp_pilha cartas_baralho, cartas_descarte;
        tp_listad *maojogador;
        maojogador = inicializa_listad();

        inicializa_pilha(&cartas_baralho);
        inicializa_pilha(&cartas_descarte);
        criar_cartas(&cartas_baralho, 10);

    //INICIANDO COMBATE
        initcombate(&player, maojogador, &cartas_baralho, &cartas_descarte,caminho);

    }
    return 0;
}
