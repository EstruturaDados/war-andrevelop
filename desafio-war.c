#include <stdio.h> // entrada e saída
#include <string.h> // manipular strings 

typedef struct { //Utilizando o typedef para desenvolvimento de um código mais conciso.
    char nome[30];
    char cor[10];
    int tropas;
}Territorio;

int main() {

    Territorio territorios[5]; // Reservando a memória para 5 structs.

    printf("SISTEMA DE CADASTRO DE TERRITÓRIOS \n");
    
    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {

        printf("\nCadastro do território %d\n", i + 1);

        printf("nome: ");
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Cor do exército? ");
        scanf(" %9[^\n]", territorios[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    // Exibição dos dados cadastrados
    printf("\n ESTADO ATUAL DO MAPA \n");

    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}

