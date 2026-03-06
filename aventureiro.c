#include <stdio.h> // entrada e saída
#include <string.h> // manipular strings 
#include <stdlib.h> // alocação de memória e funções de utilidade geral 
#include <time.h> // para usar a função time() na geração de números aleatórios

#define NUM_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

// Estrutura que representa um territorio no mapa.
typedef struct { //Utilizando o typedef para desenvolvimento de um código mais conciso.
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Função que executa ataque entre dois territorios
void atacar(Territorio  *origem, Territorio *destino) {
    
    // Regra: precisa ter pelo menos duas tropas para atacar.
    if (origem->tropas < 2) {
        printf("Impossível atacar, exército insuficiente: território de origem precisa ter pelo menos 2 tropas.\n");
        return;
    }

    printf("\n   BATALHA   \n");
    printf("%s (%s) ataca %s (%s)\n",
        origem->nome, origem->cor,
        destino->nome, destino->cor);

    //Simulação de dados (1 a 6)
    int dado_origem = rand() % 6 + 1;
    int dado_destino = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dado_origem);
    printf("Dado do defensor: %d\n", dado_destino);
    
    if (dado_origem > dado_destino) {
        printf("Atacante venceu a rodada!\n");
        destino->tropas--;

        //Se território foi conquistado
        if (destino->tropas == 0) {
            printf("Território conquistado!\n");

            // O conquistador assume a cor do território:
            strcpy(destino->cor, origem->cor);
            destino->tropas = 1;
            origem->tropas--;
        }

    } else {
        printf("Defensor venceu a rodada.\n");
        origem->tropas--;
    }
}
int main() {
    
    // Inicializa gerador de numeros aleatórios
    srand(time(NULL));

    // Alocação dinamica de memoria para o mundo
    Territorio *mundo = calloc(NUM_TERRITORIOS, sizeof(Territorio)); 
    
    // Verificação de falha na alocação
    if (mundo == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1; // Encerra o programa com código de erro.
    }

    printf(" MODO AVENTUREIRO - SISTEMA DE CADASTRO DE TERRITÓRIOS \n");

    // SISTEMA DE CADASTRO DE TERRITÓRIOS 
    for (int i = 0; i < NUM_TERRITORIOS; i++) {

        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mundo[i].nome);

        printf("Cor do exército: ");
        scanf(" %9[^\n]", mundo[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mundo[i].tropas);
    }

     int continuar = 1;

    while (continuar) {

        printf("\n=== MAPA ATUAL ===\n");
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            printf("%d - %s (%s) - Tropas: %d\n",
                   i,
                   mundo[i].nome,
                   mundo[i].cor,
                   mundo[i].tropas);
        }

        int origem, destino;

        printf("\nEscolha o território atacante (indice): ");
        scanf("%d", &origem);

        printf("Escolha o território defensor (indice): ");
        scanf("%d", &destino);

        // Validação básica
        if (origem < 0 || origem >= NUM_TERRITORIOS ||
            destino < 0 || destino >= NUM_TERRITORIOS ||
            origem == destino) {

            printf("Índices inválidos!\n");
            continue;
        }

        atacar(&mundo[origem], &mundo[destino]);

        printf("\nDeseja continuar? (1 = sim / 0 = não): ");
        scanf("%d", &continuar);
    }

    free(mundo);
    return 0;
}
