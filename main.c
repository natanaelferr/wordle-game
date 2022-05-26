#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "dicionario.h"


bool youWin(char []);
void drawWord(char []);
void showVector(int []);
bool dictionaryHas(char []);
bool verificaDentro(int,int []);
void guardaPalavras(int , char *[][6], char []);
void vetorCores(int [], char [], char [], int);
void guardaVetorCores(int [], int [][5], int);

char mainWord[6];



int main(void)
{
    int  menuOption;
    bool isPlaying;


    while(1){
        printf(AZUL_COR "Bem vindo ao jogo Wordle, logo abaixo estao as instrucoes.\n\n");
        printf(VERMELHO_COR "->" AZUL_COR " Em cada uma das seis rodadas, voce precisa inserir uma nova palavra de cinco digitos.\n");
        printf(VERMELHO_COR "->" AZUL_COR " Se voce acertar a letra e a posicao dela, o caractere fica em verde.\n");
        printf(VERMELHO_COR "->" AZUL_COR " Caso acerte a presenca dela, mas nao o posicionamento, ela fica em amarelo.\n");
        printf(VERMELHO_COR "->" AZUL_COR " Letras incorretas e ausentes ganham um tom cinza escurecido.\n\n" RESET_COR);
        isPlaying = 1;


        while(isPlaying){
            printf(BRANCO_COR "Menu:\n");
            printf("|1| Sortear uma palavra\n");
            printf("|2| Instrucoes\n");
            printf("|3| Sair\n");
            printf("Digite aqui: " VERMELHO_COR);
            scanf("%d", &menuOption);
            fflush(stdin);
            printf(RESET_COR "\n");


            if(menuOption > 3 && menuOption < 1){printf(VERMELHO_COR "Entrada Invalida!" RESET_COR);}
            //quando a opção 1 é escolhida
            if(menuOption == 1 ){
                drawWord(mainWord);             //sorteia
                bool isGaming = true;
                int attempts = 6;  
                int userCount = 0;          //numero de tentativas restantes, inicia o jogo com 6

                char userOpinion[6];            //palpite do usuario
                //este vetor possui as letras da palavra e os espaços 
                char *chart[7][6];
                int  colors[5];                 //vetor de indicação de cores para 
                int allColors[6][5];

                //aqui entra no loop das tentativas do jogo
                while(isGaming){
                    printf(BRANCO_COR "\nTentativas restantes: " VERMELHO_COR "%d\n", attempts);
                    printf("\n");
                    printf("Palavra certa para teste: %s", mainWord);
                    printf("\n" BRANCO_COR);
                    printf("\n");
                    printf("Digite aqui seu palpite: " VERMELHO_COR);
                    scanf("%s", &userOpinion);
                    printf("\n");
                    fflush(stdin);

                    
                    userCount++;
                    //verifica se a palavra existe no dicionario
                    if(dictionaryHas(userOpinion)){
                        if(youWin(userOpinion)){
                            printf(VERDE_COR "Voce venceu, parabens!\n \n" RESET_COR);
                            isGaming = false;
                        }else{
                            if(attempts > 1){//entra aqui se ainda n venceu e se tem tentativa sobrando
                                guardaPalavras(attempts, &chart, userOpinion);//imprime as palavras válidas que o usuário ja digitou
                                vetorCores(colors, userOpinion, mainWord, attempts);
                                guardaVetorCores(colors, allColors, attempts);

                                for(int i = 0;i < 5;i++){
                                    printf("%d ", allColors[userCount][i]);
                                }
                                userCount += 1;
                            attempts--; // diminui uma tentativa
                                

                            }else{
                                printf("\nVoce perdeu!\n");
                                isGaming = false;
                            }
                        }
                    }else{
                        printf("\nEsta palavra nao existe no dicionario!\n\n");
                    }
                    
                }
                }
            if(menuOption == 2 ){isPlaying = 0;}
            if(menuOption == 3 ){exit(0);}
        }
    } 
}


void guardaVetorCores(int colors[], int allColors[][5], int attempt){
    for(int i=0;i < 6 - attempt;i++){
        for(int j=0;j < 5;j++){
            allColors[i][j] = colors[j];
        }
    }
}


//função que emite um vetor com indicações de cores
void vetorCores(int colors[], char userWord[], char mainWord[], int attempt){   
    //ok
    for(int i = 0; i < 5; i++){
        if(userWord[i] == mainWord[i]){
            colors[i] = 2;
        }else{
            colors[i] = 0;
        }
    }
    //printf("");
    //showVector(colors);

    //printf("Entrou no loop\n");
    //showVector(colors);
    for(int i=0;i<5;i++){
        //printf("\ni = %d;  \n", i);
        for(int l=0;l < 5;l++){
            //printf("\nentra no for l\n");
            //printf("i = %d;  l = %d;",i, l);
            //printf("\nmainWord[i] = %c; userWord[l] = %c;\n",  mainWord[i], userWord[l]);
            //showVector(colors);
            //getch();

            if(mainWord[i] == userWord[l] && i != l && colors[l] != 2 && colors[i] != 2){
                //printf("\nmainWord[i]: %c e igual a userWord[l]:  entao: %c\n", mainWord[i], userWord[l]);
                //showVector(colors);
                //getch();
                colors[l] = 1;
                //printf("colors[%d] = %d", l, colors[l]);

            }else{
                //printf("\nmainWord[i]: %c nao e igual a userWord[l]: %c entao: l++\n",mainWord[i], userWord[l]);
                //showVector(colors);
                //getch();
                continue;
            }
        }
    }




    //pega a mainWord
    //ve quantas vezes cada letra se repete na mainWord e salva a 
    //ve quantas vezes cada letra se repete na userWord
    //ve se o numero de vezes na userWord é maior que na mainWord
    //se for verifica se os espaços que se repete ja tem o n 2



    // for(int i=0;i<5;i++){
    //     if(colors[i] != 1 && colors[i] != 2){
    //         for(int l=0;l < 5;l++){
    //             if(colors[i] != 1 && colors[i] != 2){
    //                 if(mainWord[i] == userWord[i] && i != l){
    //                     colors[l] = 1;
    //                 }else if(mainWord[i] != userWord[i]){
    //                     l++;
    //                 }
    //             }else{
    //                 l++;
    //             }
    //         }
    //     }else{
    //         i++;
    //     }
    // }

    // for(int i = 0; i < 5; i++){
    //     if(verificaDentro(i, outPosMain)){i++;}//se está no vetor excluidas
    //     showVector(outPosMain);//1111111111111111111111111
    //     for(int l = 0; l < 5; l++){
    //         if(verificaDentro(l, outPosUser)){l++;}//se está no vetor de excluidas
    //         showVector(outPosUser);//2222222222222222222222222222222222
    //         if(userWord[l] == mainWord[i] && l != i){
    //             colors[l] = 1;
    //             outPosMain[countPos] = i;
    //             outPosUser[countPos] = l;
    //             countPos++;
    //         }else{
    //             l++;
    //         }
    //     }
    // }
    //showVector(colors);//3333333333333333333333333333333
}


//guarda as palavras que o usuário ja digitou
                    //tentativas      palavras tentadas      palavra do usuario
void guardaPalavras(int attempt, char *wordAttempts[][6], char userWord[]){
    //printf("Palavra do usuario: %s\n", userWord);
    //printf("Tentativas restantes: %d\n", attempt);
    for(int i = 0; i <= 5; i++){
        if(i >= 0 && i < 5){
            wordAttempts[6 - attempt][i] = userWord[i];
            //printf("Caractere [%d][%d]: %c \n", 6 - attempt,i, wordAttempts[6 - attempt][i]);
        }else{
            wordAttempts[6 - attempt][5] = '\0';
        }    
    }
    
}


//verifica se o usuário já venceu
bool youWin(char userWord[]){
    if(
        userWord[0] == mainWord[0]  &&
        userWord[1] == mainWord[1]  &&
        userWord[2] == mainWord[2]  &&
        userWord[3] == mainWord[3]  &&
        userWord[4] == mainWord[4]
    ){
        return true;
    }else{
        return false;
    }

    // for(int i = 0; i < 5; i++){
    //     if(userWord[i] == mainWord[i]){
    //         if(mainWord[i] == userWord[i] && i == 4){
    //             return true;
    //         }
    //         i++;
    //     }else{
    //         return false;
    //     }
    // }
}


//verifica se a palavra existe no dicionário
bool dictionaryHas(char userWord[6]){
    int escopoInicial = 0;
    int escopoFinal = DICIONARIO_TAM-1;

    for(int a = 0;a <= 5;a++){
        for(int b=escopoInicial; b <= escopoFinal; b++){
            if(userWord[a] == dicionario[b][a]){
                escopoInicial = b;
                b = escopoFinal + 1;
            }
            if(b == escopoFinal && userWord[a] != dicionario[b][a]){
                return false;
            }
        }

        for(int c=escopoInicial; c <= escopoFinal; c++){
            if(userWord[a] != dicionario[c][a]){
                escopoFinal = c-1;
                c = escopoFinal+1;
                c = escopoFinal + 1;
            }
            if(escopoInicial == escopoFinal && a == 5 && userWord[a] == dicionario[c][a]){
                return true;
            }
        }
    }
}


//sorteia a palavra e adiciona a um vetor
void drawWord(char hasWord[]){
int i = 0;
int index = 0;

srand( (unsigned)time(NULL) );
index = 0 + rand() % (DICIONARIO_TAM - 0);

for (i = 0; dicionario[index][i] != '\0'; i++){
    hasWord[i] = dicionario[index][i];
}
    hasWord[i]='\0';
}


//verifica se n esta dentro de box
bool verificaDentro(int n, int box[]){
        for(int i = 0;i < 5;i++){
            if(n == box[i]){
                return true;
            }if(i == 4 && n != box[i]){
                return false;
            }
        }
    }


//imprime um vetor na tela
void showVector(int vet[]){
    for(int i=0;i<5;i++){
        printf("vet[%d]: %d  ",i, vet[i]);
    }
    printf("\n\n");
}