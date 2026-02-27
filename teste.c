#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*   DEFINIÇÕES GLOBAIS  */

#define NUM_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10
#define NUM_MISSOES 2

/*   ESTRUTURA   */

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

/*   PROTÓTIPOS   */

Territorio* alocarMapa();
void inicializarTerritorios(Territorio *mapa);
void exibirMapa(const Territorio *mapa);
void liberarMemoria(Territorio *mapa);
int sortearMissao();
int verificarVitoria(const Territorio *mapa, const char *corJogador, int missao);

/*    IMPLEMENTAÇÃO    */

/* Aloca memória dinamicamente para os territórios */
Territorio* alocarMapa() {
    Territorio *mapa = malloc(NUM_TERRITORIOS * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    return mapa;
}

/* Cadastro dos territórios */
void inicializarTerritorios(Territorio *mapa) {

    for (int i = 0; i < NUM_TERRITORIOS; i++) {

        printf("\nCadastro do território %d\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %9[^\n]", mapa[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

/* Exibição do mapa */
void exibirMapa(const Territorio *mapa) {

    printf("\n========== ESTADO ATUAL DO MAPA ==========\n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {

        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

/* Liberação da memória */
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

/* Sorteio de missão */
int sortearMissao() {
    srand(time(NULL));
    return rand() % NUM_MISSOES;
}

/* Verificação de vitória */
int verificarVitoria(const Territorio *mapa, const char *corJogador, int missao) {

    if (missao == 0) {
        /* Missão 0: Conquistar pelo menos 3 territórios */
        int contador = 0;

        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contador++;
            }
        }

        return contador >= 3;
    }

    if (missao == 1) {
        /* Missão 1: Somar pelo menos 50 tropas */
        int total = 0;

        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                total += mapa[i].tropas;
            }
        }

        return total >= 50;
    }

    return 0;
}

/*    FUNÇÃO PRINCIPAL   */

int main() {

    printf("SISTEMA DE CADASTRO DE TERRITÓRIOS\n");

    /* Alocação dinâmica */
    Territorio *mapa = alocarMapa();

    /* Cadastro */
    inicializarTerritorios(mapa);

    /* Exibição */
    exibirMapa(mapa);

    /* Sistema de missão */
    char corJogador[MAX_COR];

    printf("\nDigite sua cor para verificar a missão: ");
    scanf(" %9[^\n]", corJogador);

    int missao = sortearMissao();

    printf("Missão sorteada: %d\n", missao);

    if (verificarVitoria(mapa, corJogador, missao)) {
        printf("Você venceu a missão!\n");
    } else {
        printf("Missão não concluída.\n");
    }

    /* Liberação da memória */
    liberarMemoria(mapa);

    return 0;
}
