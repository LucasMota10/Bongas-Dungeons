#ifndef STYLES_H
#define STYLES_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>
#include <locale.h>

//tempo padrao de espera do terminal para comandos antes do clear:
#define UM 1000
#define DOIS 2000
#define TRES 3000

//cores

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"


// Função para imprimir texto com estilo

void printColoredText(char *text, char *color){

      printf("%s%s%s", color, text, COLOR_RESET);
}

void clear(){system("cls");}

#endif