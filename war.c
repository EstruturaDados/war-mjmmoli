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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para srand()

// Define a estrutura basica
struct Territorio {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
};

const int NUM_TERRITORIOS_AVENTUREIRO = 5;

// Funcao para exibir o mapa (recebe um ponteiro para o inicio do vetor)
void exibir_mapa_aventureiro(struct Territorio *mapa) {
    printf("\n--- Estado Atual do Mapa (Nível Aventureiro) ---\n");
    for (int i = 0; i < NUM_TERRITORIOS_AVENTUREIRO; i++) {
        // Acessa o struct como um vetor
        printf("[%d] %s | Exército: %s | Tropas: %d\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor_exercito, 
               mapa[i].num_tropas);
    }
    printf("------------------------------------------------\n");
}

// Funcao de batalha (recebe ponteiros para as structs atacante e defensor)
void simular_batalha(struct Territorio *atacante, struct Territorio *defensor) {
    // Sorteio de dados de 6 faces
    int dado_ataque = (rand() % 6) + 1; 
    int dado_defesa = (rand() % 6) + 1;

    printf("\n--- Simulação de Batalha ---\n");
    printf("Dados: Atacante (%d) vs. Defensor (%d)\n", dado_ataque, dado_defesa);

    // Batalha: Empates favorecem o atacante
    if (dado_ataque >= dado_defesa) {
        printf(">>> Vitória do Atacante! Defensor perde 1 tropa.\n");
        // Acesso via operador seta (->) pois sao ponteiros
        defensor->num_tropas -= 1; 
    } else {
        printf(">>> Vitória do Defensor! Atacante perde 1 tropa.\n");
        atacante->num_tropas -= 1; 
    }

    // Lógica de conquista
    if (defensor->num_tropas <= 0) {
        printf("!!! Território CONQUISTADO: %s agora é do exército %s !!!\n", 
               defensor->nome, atacante->cor_exercito);
        
        // Atacante assume o territorio
        strcpy(defensor->cor_exercito, atacante->cor_exercito);
        defensor->num_tropas = 1; // Coloca 1 tropa
        atacante->num_tropas -= 1; // Retira 1 tropa do atacante (para ocupar)
        if (atacante->num_tropas < 1) {
            atacante->num_tropas = 1; 
        }
    }
}

int main() {
    int idx_atacante, idx_defensor;
    
    srand(time(NULL)); 
    
    // Alocacao dinamica de memoria com calloc
    struct Territorio *mapa = (struct Territorio *)calloc(NUM_TERRITORIOS_AVENTUREIRO, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    // Inicialização dos dados (pode ser feita por input, mas hardcoded para simplicidade)
    strcpy(mapa[0].nome, "Atletico"); strcpy(mapa[0].cor_exercito, "Preto"); mapa[0].num_tropas = 13;
    strcpy(mapa[1].nome, "America"); strcpy(mapa[1].cor_exercito, "Verde"); mapa[1].num_tropas = 10;
    strcpy(mapa[2].nome, "Cruzeiro"); strcpy(mapa[2].cor_exercito, "Azul"); mapa[2].num_tropas = 10;
    strcpy(mapa[3].nome, "Democrata"); strcpy(mapa[3].cor_exercito, "Vermelho"); mapa[3].num_tropas = 9;
    strcpy(mapa[4].nome, "Caldense"); strcpy(mapa[4].cor_exercito, "Amarelo"); mapa[4].num_tropas = 8;
    
    printf("--- Nível Aventureiro: Batalhas Estratégicas ---\n");
    exibir_mapa_aventureiro(mapa);

    // Loop interativo de batalhas
    while (1) {
        printf("\nEscolha o ATACANTE (1 a 5, 0 para sair): ");
        if (scanf("%d", &idx_atacante) != 1 || idx_atacante < 0 || idx_atacante > 5) {
            printf("Opção inválida. Tente novamente.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n'); 
            continue;
        }

        if (idx_atacante == 0) break;
        idx_atacante--; // Ajusta para indice 0-based

        if (mapa[idx_atacante].num_tropas < 2) { 
            printf("O atacante deve ter no mínimo 2 tropas.\n");
            continue;
        }

        printf("Escolha o DEFENSOR (1 a 5): ");
        if (scanf("%d", &idx_defensor) != 1 || idx_defensor < 1 || idx_defensor > 5) {
            printf("Opção inválida. Tente novamente.\n");
            while (getchar() != '\n'); 
            continue;
        }
        idx_defensor--; 

        if (idx_atacante == idx_defensor) {
            printf("Não é possível atacar o próprio território.\n");
            continue;
        }
        
        // Chama a funcao de batalha, passando o endereço das structs
        simular_batalha(&mapa[idx_atacante], &mapa[idx_defensor]);
        
        exibir_mapa_aventureiro(mapa);
    }

    // Libera a memoria alocada
    free(mapa);
    mapa = NULL;
    
    return 0;
}