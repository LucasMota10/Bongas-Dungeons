#ifndef CAMINHO_H
#define CAMINHO_H

#include <stdio.h>
#include <stdlib.h>

typedef char tp_item; 

//dados estruturado que representa o descritor
typedef struct tp_no_auxs {   
  struct tp_no_auxs *ant;  
  tp_item info;  
  struct tp_no_auxs *prox;   
} tp_nos; 

//dado estruturado que representa o n� da lista
typedef struct {   
  tp_nos *ini;   
  tp_nos *fim;   
//  int tamanho;   
} tp_listade;

//aloca-se mem�ria para o descritor (explicado no �nicio deste arquivo) e faz o seus ponteiros apontarem para o Nulo
tp_listade *inicializa_listade(){
   tp_listade *lista=(tp_listade*) malloc(sizeof(tp_listade));   
   lista->ini = NULL;   
   lista->fim = NULL;   
 // lista->tamanho = 0;   
   return lista;
}  


int listade_vazia(tp_listade *lista) {
	if ( (lista->ini == NULL) ) 
		return 1;
	return 0;	
}

//Aloca um n� da lista
tp_nos *alocade() {
	tp_nos* pt;
	pt=(tp_nos*) malloc(sizeof(tp_nos));
	return pt;
}

//insere um novo n� na lista
int insere_listade_no_fim (tp_listade *lista, tp_item e){   
  tp_nos *novo;   
  novo=alocade();
  if (!novo) return 0;
  novo->info = e;  
  if ( listade_vazia(lista) ){ //Se for o primeiro elemento da lista
     novo->prox = NULL;   
     novo->ant = NULL; 
     lista->ini = lista->fim = novo;
     }  
  else {
     novo->prox = NULL;   
     novo->ant = lista->fim; 
     lista->fim->prox = novo;
     lista->fim = novo;
     }  
  //lista->tamanho++;   
  return 1;   
}        

//imprime os conte�dos da lista (de frente para tr�s ou de tr�s pra frente)
void imprime_listade(tp_listade *lista, int ordem) {
	if (lista==NULL)
		printf("Lista n�o inicializada");
	else {
     tp_nos *atu;     
     switch (ordem) {
        case 1: atu = lista->ini;
                while (atu != NULL) {
                   printf("%c ", atu->info);
                   atu=atu->prox;           
                   }
                break;   
        case 2: atu = lista->fim;
                while (atu != NULL) {
                   printf("%d ", atu->info);
                   atu=atu->ant;           
                   }
                break;   
        default: printf("codigo invalido");        
     }
	}
     printf("\n");
}


//remove um elemento da lista
int remove_listade (tp_listade *lista, tp_item e){   
  tp_nos *atu;
  atu = lista->ini;
  while ( (atu != NULL) && (atu->info != e) ) { 
        atu=atu->prox;}
  if ( atu == NULL) return 0;  
  if (lista->ini == lista->fim) { //Se o for o unico elemento da lista
      lista->ini = lista->fim = NULL; }
  else {   
   if (lista->ini == atu) {  //Se for o primeiro elemento da lista
      lista->ini = atu->prox;
      atu->prox->ant = NULL;
      }  
   else {
      if (lista->fim == atu) { // se for o �ltimo n� da lista
       lista->fim = atu->ant;
       atu->ant->prox = NULL;              
       }
      else {
        atu->prox->ant = atu->ant;   
        atu->ant->prox = atu->prox;
        } 
      }
     }   
   free(atu);  
  //lista->tamanho--;   
  return 1;   
}        

//Com base em um conte�do, retorna-se o endere�o do n� que cont�m o conte�do
tp_nos * busca_listades (tp_listade *lista, tp_item e){   
  tp_nos *atu;
  atu = lista->ini;
  while ( (atu != NULL) && (atu->info != e) ) { 
        atu=atu->prox;}
  return atu;
}        

//Retira da mem�ria todos os n�s da lista e tamb�m o descritor
tp_listade * Destroi_listade (tp_listade *lista){   
  tp_nos *atu;
  atu = lista->ini;
  while (atu != NULL)  { 
        lista->ini = atu->prox;
        free(atu);
        atu=lista->ini;
		}
  free(lista);
  return NULL;
}  

void criacaminho(tp_listade *caminho){
    insere_listade_no_fim(caminho,'E');
    insere_listade_no_fim(caminho,'C');
    insere_listade_no_fim(caminho,'D');
    insere_listade_no_fim(caminho,'E');
    insere_listade_no_fim(caminho,'D');
    insere_listade_no_fim(caminho,'C');
    insere_listade_no_fim(caminho,'B');
}

void manipulacaminho(tp_listade *caminho){
    tp_nos *atu = caminho->ini;
    int x = 0;
    if(atu->info == 'E'){
        // Combate
        do{
        printf("Parabens Pela vitoria! Agora voce pode escolher seu caminho\nDigite (1) para descansar e recuperar suas energias!\nDigite (2) para combater outro monstro!\n");
        scanf("%d",&x);
        if(x == 1){
            //manipulação para que o proximo elemento do caminho seja um descanso
        }else{
            if(x == 2){
                //manipulação para que o proximo elemento do caminho seja um combate
            }
            else{
                printf("Digite um numero valido!\n");
            }
        }
        }while(x != 1 || x != 2);
      }
    }


#endif