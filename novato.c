#include <stdio.h> // entrada e saída
#include <string.h> // manipular strings 
#include <stdlib.h> // alocação de memória e funções de utilidade geral 

#define NUM_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

typedef struct { //Utilizando o typedef para desenvolvimento de um código mais conciso.
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

int main() {

    Territorio mundo[NUM_TERRITORIOS]; // Reservando a memória para 5 structs.

    printf("SISTEMA DE CADASTRO DE TERRITÓRIOS \n");
    
    // Cadastro dos territórios
    for (int i = 0; i < NUM_TERRITORIOS; i++) {

        printf("\nCadastro do território %d\n", i + 1);

        printf("nome: ");
        scanf(" %29[^\n]", mundo[i].nome);

        printf("Cor do exército? ");
        scanf(" %9[^\n]", mundo[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mundo[i].tropas);
    }
    
    // Exibição dos dados cadastrados
    printf("\n ESTADO ATUAL DO MAPA \n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mundo[i].nome);
        printf("Cor: %s\n", mundo[i].cor);
        printf("Tropas: %d\n", mundo[i].tropas);
    }

    return 0;
}

