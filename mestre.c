#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5
#define MAX_NOME 30
#define MAX_COR 10

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

void cadastrarTerritorios(Territorio *mapa) {

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
void exibirMapa(const Territorio *mapa) {
    printf("\n   MAPA ATUAL   \n");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {

        printf("%d - %s (%s) - Tropas: %d\n",
        i,
        mapa[i].nome,
        mapa[i].cor,
        mapa[i].tropas);
    }
}
int sortearMissao() {
    return rand() % 2 + 1;
}
int verificarMissao(const Territorio *mapa, const char *corJogador, int missao) {
    //Missão 1: Destruir o Exército VERDE:
    if (missao == 1) {

        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "verde") == 0) {
                return 0; // ainda existe territorio verde.
            }
        }

        return 1; // nenhum território verde encontrado.
    }

    // Missão 2: Conquistar 3 Territórios:
    if (missao == 2) {

        int contador = 0;

        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            
            if (strcmp(mapa[i].cor, corJogador) == 0) { // em C nao podemos comparar strings com ""=="", então usamos o strcmp.
                contador++;
            }
        }
        
        if (contador >= 3) {
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}
void atacar(Territorio *origem, Territorio *destino) {

    if (origem->tropas < 2) {
        printf("Tropas insuficientes para atacar.\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nBATALHA\n");
    printf("%s ataca %s\n", origem->nome, destino->nome);
    printf("Dado atacante: %d\n", dadoAtaque);
    printf("Dado defensor: %d\n", dadoDefesa);

    if (dadoAtaque >= dadoDefesa) {

        printf("Atacante venceu!\n");
        destino->tropas--;

        if (destino->tropas <= 0) {

            printf("Território conquistado!\n");

            strcpy(destino->cor, origem->cor);

            destino->tropas = 1;
            origem->tropas--;
        }

    } else {

        printf("Defensor venceu!\n");
        origem->tropas--;
    }
}

int main() {

    srand(time(NULL));

    Territorio *mundo = calloc(NUM_TERRITORIOS, sizeof(Territorio));

    if (mundo == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    char corJogador[MAX_COR];
    int missao;

    printf("=== WAR - MODO MESTRE ===\n");

    cadastrarTerritorios(mundo);

    printf("\nQual a cor do seu exército? ");
    scanf(" %9[^\n]", corJogador);
    
    do {
        missao = sortearMissao();
    } while (missao == 1 && strcmp(corJogador, "Verde") == 0);

    if (missao == 1)
        printf("Missao: Destruir o exército verde\n");
    else
        printf("Missao: Conquistar 3 territórios\n");
        
    int opcao = -1;

    while (opcao != 0) {

        printf("\n=== MENU ===\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {

            exibirMapa(mundo);

            int origem, destino;

            printf("\nTerritório atacante: ");
            scanf("%d", &origem);

            printf("Território defensor: ");
            scanf("%d", &destino);

            if (origem >= 0 && origem < NUM_TERRITORIOS &&
                destino >= 0 && destino < NUM_TERRITORIOS &&
                origem != destino) {

            // verificar se o território pertence ao jogador
            if (strcmp(mundo[origem].cor, corJogador) != 0) {
                printf("Você só pode atacar com seus próprios territórios.\n");
                continue;
            }

            // impedir atacar território aliado
            if (strcmp(mundo[origem].cor, mundo[destino].cor) == 0) {
                printf("Não é possível atacar um território aliado.\n");
                continue;
            }

            atacar(&mundo[origem], &mundo[destino]);

        } else {
            printf("Territórios inválidos!\n");
        }

    } 
        else if (opcao == 2) {

            if (verificarMissao(mundo, corJogador, missao)) {
                printf("\nMISSÃO CUMPRIDA! Você venceu o jogo!\n");
                break;
            } else {
                printf("\nMissão ainda não concluída.\n");
            }

        }
    }

    free(mundo);

    return 0;
} 
