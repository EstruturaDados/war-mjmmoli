// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO

// ============================================================================
//        
// ============================================================================
/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a estrutura basica do Territorio
struct Territorio {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
};

#define NUM_TERRITORIOS_NOVATO 5

// Funcao para imprimir o mapa
void exibir_mapa_novato(struct Territorio mapa[]) {
    printf("\n--- Estado Atual do Mapa (Nível Novato) ---\n");
    for (int i = 0; i < NUM_TERRITORIOS_NOVATO; i++) {
        // Imprime os dados de cada struct no vetor
        printf("[%d] %s | Exército: %s | Tropas: %d\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor_exercito, 
               mapa[i].num_tropas);
    }
    printf("------------------------------------------\n");
}

int main() {
    // Vetor estatico de structs
    struct Territorio mapa[NUM_TERRITORIOS_NOVATO];
    char buffer[100]; // Buffer para leitura de strings

    printf("--- Cadastro Inicial de Territórios (Nível Novato) ---\n");

    // Cadastro manual dos 5 territorios
    for (int i = 0; i < NUM_TERRITORIOS_NOVATO; i++) {
        printf("\nCadastrando Território #%d:\n", i + 1);

        // Nome (uso de fgets para strings)
        printf("Nome: ");
        fflush(stdin); 
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0; 
            strcpy(mapa[i].nome, buffer);
        }
        
        // Cor do Exército
        printf("Cor do Exército: ");
        fflush(stdin);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            buffer[strcspn(buffer, "\n")] = 0; 
            strcpy(mapa[i].cor_exercito, buffer);
        }

        // Numero de Tropas (uso de scanf para inteiros)
        printf("Número de Tropas: ");
        if (scanf("%d", &mapa[i].num_tropas) != 1) {
            mapa[i].num_tropas = 0;
        }
    }

    exibir_mapa_novato(mapa);
    
    return 0;
}