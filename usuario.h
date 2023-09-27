#ifndef usuario_h
#define usuario_h
#include <stdio.h>
#include "Fila.h"
#include "pilha.h"

typedef struct {
    char nome_do_jogador[20];
    int mana = 100, vida = 200,escudo = 0;
}jogador;


#endif