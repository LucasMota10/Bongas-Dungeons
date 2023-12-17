#ifndef arte_h
#define arte_h
#include <stdio.h>
#include <windows.h>
#include <string.h>



void text(){
    
    FILE *lore = fopen("lore.txt", "r");

    const LPCSTR typing = "./sounds/typing.wav";

    char linha[300];
    PlaySound(typing, NULL, SND_ASYNC);
    while(fscanf(lore, " %[^\n]s", linha) != EOF){
        for(int i = 0; i<strlen(linha); i++){
            printf("%c", linha[i]);
            Sleep(80);
        }
    }

    fclose(lore);

}
void asciiart(){
    
    const LPCSTR opening = "./sounds/opening.wav";  

    Sleep(5000);

     printf("\n\n\n" );
     printf("                                                       ...                      \n");
    Sleep(20);
     printf("                          %%##(*      %%######(#  (########                   \n");
    Sleep(20);
     printf("                          ###(*      #(. .*/((*(##,  *##/(                  \n");
    Sleep(20);
     printf("                          ###(/&     #.   / /(*(#.  (#,(//                  \n");
    Sleep(20);
     printf("                         %%###(/#     //    ,/*(((.    ,(*/                  \n");
    Sleep(20);
     printf("                         ####(/*    /(///(##########/***,                   \n");
    Sleep(20);
     printf("                        /####((*    ((#############(((//*                   \n" );
    Sleep(20);
     printf("                       ######((**   ((#############(((//*                   \n" );
    Sleep(20);
     printf("                  3(((########(/*   /((############((//*,                   \n" );
    Sleep(20);
     printf("            (3########(/(######((*  ///((#########((//*,(                   \n" );
    Sleep(20);
     printf("            (########(/(######(/*(   ///((#####((((/**,.                    \n" );
    Sleep(20);
     printf("            ((############((((//,(     %%*/((((((///*,,                      \n" );
    Sleep(20);
     printf("              #############(((/*,          ,#****                           \n") ;
    Sleep(20);
     printf("              (###########((((/,(                                            \n" );
    Sleep(20);
     printf("              (*((((((((((((/,,                                              \n" );
    Sleep(20);
     printf("                   (/,**,,.(                                                 \n" );
    Sleep(20);
     printf("\n\n\n" );
    
    Sleep(5000);
    
    
     printf("       _______  _______ ______  _______ _______ _______ \n" );
     printf("      |   _   \\|   _   |   _  \\|   _   |   _   |   _   |\n" );
     printf("      |.  1   /|.  |   |.  |   |.  |___|.  1   |   1___|\n" );
     printf("      |.  _   \\|.  |   |.  |   |.  |   |.  _   |____   |\n" );
     printf("      |:  1    |:  1   |:  |   |:  1   |:  |   |:  1   |\n" );
     printf("      |::.. .  |::.. . |::.|   |::.. . |::.|:. |::.. . |\n" );
     printf("`      -------'`-------`--- ---`-------`--- ---`-------'\n" );
     printf("                D    U    N    G    E    O    N \n\n\n\n\n\n");
    PlaySound(opening, NULL, SND_ASYNC | SND_FILENAME);
    Sleep(5000);

    



    
}

void dialogo_final(){
    
    clear();
    Sleep(3000);
    const LPCSTR creditos = "./sounds/creditos.wav";
    PlaySound(creditos, NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);

    printColoredText("Ei! Voce ai! ", COLOR_RED);
    Sleep(3000);
    

    printColoredText("Como voce me derrotou?\n", COLOR_RED);
    Sleep(3000);

    printColoredText("Eu? Eu consegui enfim...", COLOR_GREEN);
    Sleep(1000);

    printColoredText(" Tudo isso nao foi em vao...\n", COLOR_GREEN);
    Sleep(3000);
    

    printColoredText("NAO ERA PARA TER ME DERROTADO!", COLOR_RED);
    Sleep(1000);

    printColoredText(" NINGUEM DEVIA GANHAR DE MIM!!\n", COLOR_RED);
    Sleep(2000);

    printColoredText("Mas aconteceu, nao?\n", COLOR_GREEN);
    Sleep(1000);

    printColoredText("TODAS AS LISTAS ENCADEADAS!\n", COLOR_RED);
    Sleep(500);
    printColoredText("TODAS AS ARVORES QUE EU UTILIZEI!\n", COLOR_RED);
    Sleep(500);
    printColoredText("NENHUMA ESTRUTURA DE DADOS FOI CAPAZ DE TE DESTRUIR!\n", COLOR_RED);
    Sleep(500);
    printColoredText("So me resta uma opcao... ", COLOR_RED);
    Sleep(5000);
    printColoredText("Aprovado!", COLOR_CYAN);
    Sleep(10000);

    clear();
    printColoredText("Créditos: ", COLOR_YELLOW);
    Sleep(2000);

    printColoredText("Andre Delarovera Rezende\n", COLOR_YELLOW);
    Sleep(2000);
    printColoredText("Daniel Fernandes da Cunha Vasconcelos\n", COLOR_YELLOW);
    Sleep(2000);
    printColoredText("Guilherme Soares May Rios\n", COLOR_YELLOW);
    Sleep(2000);
    printColoredText("Henrique Barros Araujo Correia\n", COLOR_YELLOW);
    Sleep(2000);
    printColoredText("Lucas Barbosa Bulcao Mota\n", COLOR_YELLOW);
    Sleep(10000);

    asciiart();

}

#endif


