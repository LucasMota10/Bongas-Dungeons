#ifndef pilha_h
#define pilha_h
#include<stdio.h>
#define MAX 100

typedef struct {
char nome[30];
int tipodacarta;
int power, mana, regmana, vida, escudo, level;

}tp_cartas;

typedef struct
{
tp_cartas item[MAX];
int topo;
}tp_pilha;

void inicializa_pilha(tp_pilha *p)
{
p->topo = -1;
}

int pilha_vazia(tp_pilha *p)
{
if (p->topo == -1) return 1;
return 0;
}

int pilha_cheia(tp_pilha *p)
{
if(p->topo == MAX-1) return 1;
return 0;
}

int push(tp_pilha *p, tp_cartas f)
{
if(pilha_cheia(p)) return 0;
p->topo++;
p->item[p->topo] = f;
return 1;
}
int pop(tp_pilha *p, tp_cartas *e){
if(pilha_vazia(p)) return 0;
*e=p->item[p->topo];
p->topo--;
return 1;
}

int top(tp_pilha *p, tp_cartas *e){
if (pilha_vazia(p)) return 0;
*e=p->item[p->topo];
return 1;
}

void imprime_pilha(tp_pilha p){
tp_cartas e;
printf("Cartas do jogador: \n");

int i = 1;

while (!pilha_vazia(&p)){

    
    pop(&p, &e);
    printf("%d.: %s ", i, e.nome);
    i++;
}
}

int altura_pilha(tp_pilha *p){
return p->topo+1;
}
#endif