#ifndef CARTA_H
#define CARTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX 100

typedef struct {
  char nome[100];
  int tipodacarta; // tipo de carta por num (0==ataque , 1==defesa, especial ==
                   // 2)
  int power, mana, level;
} tp_cartas;


// LIB DE PILHA

typedef struct {
  tp_cartas item[MAX];
  int topo;
} tp_pilha;

void inicializa_pilha(tp_pilha *p) { p->topo = -1; }

int pilha_vazia(tp_pilha *p) {
  if (p->topo == -1)
    return 1;
  return 0;
}

int pilha_cheia(tp_pilha *p) {
  if (p->topo == MAX - 1)
    return 1;
  return 0;
}

int push(tp_pilha *p, tp_cartas f) {
  if (pilha_cheia(p))
    return 0;
  p->topo++;
  p->item[p->topo] = f;
  return 1;
}
int pop(tp_pilha *p, tp_cartas *e) {
  if (pilha_vazia(p))
    return 0;
  *e = p->item[p->topo];
  p->topo--;
  return 1;
}

int top(tp_pilha *p, tp_cartas *e) {
  if (pilha_vazia(p))
    return 0;
  *e = p->item[p->topo];
  return 1;
}

int altura_pilha(tp_pilha *p) { return p->topo + 1; }


// cartas do deck
void imprime_pilha(tp_pilha p){
    tp_cartas e;
    printf("\n");
    while (!pilha_vazia(&p)){
        pop(&p, &e);
        printf("Carta: %s\n", e.nome);
    }
}
int criar_cartas(tp_pilha *pilha, int quant){

  tp_cartas cartas[12];


  //manipulação do arquivo txt
  FILE *carta_nome, *carta_specs; //dois arquivos, um para ler os nomes e outro para as habilidades
  char name[100];
  char *token;

  int tipo, poder, level, mana;

  carta_nome= fopen("./data/cartas/nome.txt", "r");
  carta_specs = fopen("./data/cartas/habilidades.txt", "r");

  if(!carta_nome || !carta_specs)printf("erro ao abrir");
  
  int i = 0;

  while(fgets(name, sizeof(name), carta_nome)){
    strcpy(cartas[i].nome, name);
    i++;
  }

  i=0;
  while(fscanf(carta_specs, "%d %d %d %d", &tipo, &poder, &level, &mana) != EOF){
    //atribuir valores as cartas
    cartas[i].tipodacarta = tipo;
    cartas[i].level = level;
    cartas[i].mana = mana;
    cartas[i].power = poder;
    i++;
  }

  // Função preencher pilha:
  srand(time(NULL));
  for (int i = 0; i < quant; i++) { // shuffle array
    int random = rand() % 12;
    push(pilha, cartas[random]);
  }

  //FECHAR OS ARQUIVOS
  fclose(carta_nome); fclose(carta_specs);

}

void adicionar_cartas(tp_pilha *baralho){
  tp_pilha aux;
  criar_cartas(&aux, 3);

  printf("Parabéns, você matou o monstro! Escolha 1 carta para adicionar ao seu baralho!\n");

  imprime_pilha(aux);

  int i;
  scanf("%d", &i);

  for(int j=0; j<i-1; j++){
    pop(&aux, NULL);
  }

  tp_cartas selec;
  pop(&aux, &selec);

  push(baralho, selec);


}




#endif