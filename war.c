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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

// Função portatil para limpar o buffer de entrada
void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Constantes e Tipos ---
#define NUM_TERRITORIOS_MESTRE 5
#define COR_JOGADOR "Preto" 

// Struct de Territorio
typedef struct {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
} Territorio; 

// Enum para os tipos de missao
typedef enum {
    MISSAO_DESTRUIR_VERDE,
    MISSAO_CONQUISTAR_3,
    MISSAO_CONQUISTAR_TOTAL 
} TipoMissao;

// Struct de Missao
typedef struct {
    TipoMissao tipo;
    char descricao[100];
    int progresso; 
    const char *alvo_cor;
} Missao;


// --- Protótipos das Funções ---
void inicializar_territorios(Territorio *mapa);
void inicializar_missao(Missao *missao);
void exibir_mapa_mestre(const Territorio *mapa); 
void executar_batalha(Territorio *atacante, Territorio *defensor, Missao *missao);
int verificar_missao(const Territorio *mapa, Missao *missao);


// --- Implementação das Funções ---

void inicializar_territorios(Territorio *mapa) {
    strcpy(mapa[0].nome, "Atletico"); strcpy(mapa[0].cor_exercito, COR_JOGADOR); mapa[0].num_tropas = 13;
    strcpy(mapa[1].nome, "America"); strcpy(mapa[1].cor_exercito, "Verde"); mapa[1].num_tropas = 10;
    strcpy(mapa[2].nome, "Cruzeiro"); strcpy(mapa[2].cor_exercito, "Azul"); mapa[2].num_tropas = 10;
    strcpy(mapa[3].nome, "Democrata"); strcpy(mapa[3].cor_exercito, "Vermelho"); mapa[3].num_tropas = 9;
    strcpy(mapa[4].nome, "Caldense"); strcpy(mapa[4].cor_exercito, "Amarelo"); mapa[4].num_tropas = 8;
}

void inicializar_missao(Missao *missao) {
    int sorteio = rand() % 3; 

    if (sorteio == 0) {
        missao->tipo = MISSAO_DESTRUIR_VERDE;
        strcpy(missao->descricao, "Destruir completamente o exército VERDE.");
        missao->alvo_cor = "Verde";
    } else if (sorteio == 1) {
        missao->tipo = MISSAO_CONQUISTAR_3;
        strcpy(missao->descricao, "Conquistar 3 territórios de qualquer cor. (Progresso: 0)");
    } else {
        missao->tipo = MISSAO_CONQUISTAR_TOTAL;
        strcpy(missao->descricao, "Conquistar TODOS os territórios do mapa.");
    }
    missao->progresso = 0;
    printf("\n*** MISSAO ATUAL ***\n%s\n********************\n", missao->descricao);
}

void exibir_mapa_mestre(const Territorio *mapa) {
    printf("\n--- Mapa Atual ---\n");
    for (int i = 0; i < NUM_TERRITORIOS_MESTRE; i++) {
        printf("[%d] %s | Exército: %s | Tropas: %d\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor_exercito, 
               mapa[i].num_tropas);
    }
    printf("------------------\n");
}

void executar_batalha(Territorio *atacante, Territorio *defensor, Missao *missao) {
    int dado_ataque = (rand() % 6) + 1; 
    int dado_defesa = (rand() % 6) + 1;
    char cor_defensor_original[20];
    
    strcpy(cor_defensor_original, defensor->cor_exercito);

    printf("\n--- Batalha entre %s (D:%d) e %s (D:%d) ---\n", 
           atacante->nome, dado_ataque, defensor->nome, dado_defesa);

    if (dado_ataque >= dado_defesa) {
        printf("Vitória do Atacante! Defensor perde 1 tropa.\n");
        defensor->num_tropas -= 1;
        
        if (defensor->num_tropas <= 0) {
            printf("!!! CONQUISTA !!! %s agora pertence a %s.\n", 
                   defensor->nome, atacante->nome);
            
            if (strcmp(atacante->cor_exercito, COR_JOGADOR) == 0) { 
                if (missao->tipo == MISSAO_CONQUISTAR_3) {
                    missao->progresso++;
                }
            }

            strcpy(defensor->cor_exercito, atacante->cor_exercito);
            defensor->num_tropas = 1; 
            atacante->num_tropas--;
            if (atacante->num_tropas < 1) atacante->num_tropas = 1;

            if (missao->tipo == MISSAO_DESTRUIR_VERDE && strcmp(cor_defensor_original, missao->alvo_cor) == 0) {
                 printf("Avanco na Missão: %s não é mais %s.\n", defensor->nome, missao->alvo_cor);
            }
        }
    } else {
        printf("Vitória do Defensor! Atacante perde 1 tropa.\n");
        atacante->num_tropas -= 1; 
        if (atacante->num_tropas < 1) {
            atacante->num_tropas = 1;
        }
    }
}

int verificar_missao(const Territorio *mapa, Missao *missao) {
    printf("\n--- Verificação de Missão ---\n");
    int territorios_jogador = 0;

    for (int i = 0; i < NUM_TERRITORIOS_MESTRE; i++) {
        if (strcmp(mapa[i].cor_exercito, COR_JOGADOR) == 0) {
            territorios_jogador++;
        }
    }

    if (missao->tipo == MISSAO_DESTRUIR_VERDE) {
        for (int i = 0; i < NUM_TERRITORIOS_MESTRE; i++) {
            if (strcmp(mapa[i].cor_exercito, missao->alvo_cor) == 0) {
                printf("Missão não cumprida. O exército %s ainda está presente.\n", missao->alvo_cor);
                return 0; 
            }
        }
        printf("!!! SUCESSO !!! O exército %s foi destruído!\n", missao->alvo_cor);
        return 1; 
    } 
    
    else if (missao->tipo == MISSAO_CONQUISTAR_3) {
        if (missao->progresso >= 3) {
            printf("!!! SUCESSO !!! Você conquistou %d territórios!\n", missao->progresso);
            return 1; 
        } else {
            printf("Missão em progresso: %d/3 territórios conquistados.\n", missao->progresso);
            return 0;
        }
    }

    else if (missao->tipo == MISSAO_CONQUISTAR_TOTAL) {
        if (territorios_jogador == NUM_TERRITORIOS_MESTRE) {
            printf("!!! SUCESSO !!! Você dominou TODOS os %d territórios!\n", NUM_TERRITORIOS_MESTRE);
            return 1;
        } else {
            printf("Missão em progresso: Você domina %d/%d territórios.\n", territorios_jogador, NUM_TERRITORIOS_MESTRE);
            return 0;
        }
    }
    
    return 0;
}


// --- Função Principal ---

int main() {
    srand(time(NULL)); 
    
    Territorio *mapa = (Territorio *)calloc(NUM_TERRITORIOS_MESTRE, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    Missao missao_jogador;
    int escolha_menu, idx_atacante, idx_defensor;
    int jogo_finalizado = 0;
    
    printf("--- Nível Mestre: Missões e Modularização Total ---\n");

    inicializar_territorios(mapa);
    inicializar_missao(&missao_jogador); 

    while (!jogo_finalizado) {
        exibir_mapa_mestre(mapa); 
        
        printf("\n--- Menu Principal ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &escolha_menu) != 1) {
            printf("Opção inválida. Tente novamente.\n");
            limpar_buffer_entrada(); 
            continue;
        }
        
        limpar_buffer_entrada(); // Limpeza após a leitura do menu

        switch (escolha_menu) {
            case 1: 
                printf("Território ATACANTE (1-%d): ", NUM_TERRITORIOS_MESTRE);
                if (scanf("%d", &idx_atacante) != 1) { limpar_buffer_entrada(); break; }
                
                printf("Território DEFENSOR (1-%d): ", NUM_TERRITORIOS_MESTRE);
                if (scanf("%d", &idx_defensor) != 1) { limpar_buffer_entrada(); break; }
                
                limpar_buffer_entrada(); // Limpeza após as duas leituras

                idx_atacante--;
                idx_defensor--;
                
                if (idx_atacante < 0 || idx_atacante >= NUM_TERRITORIOS_MESTRE ||
                    idx_defensor < 0 || idx_defensor >= NUM_TERRITORIOS_MESTRE ||
                    strcmp(mapa[idx_atacante].cor_exercito, COR_JOGADOR) != 0 ||
                    mapa[idx_atacante].num_tropas < 2 || idx_atacante == idx_defensor) {
                    printf("Ataque inválido. Verifique o índice, tropas (min. 2) ou posse.\n");
                    break;
                }
                
                executar_batalha(&mapa[idx_atacante], &mapa[idx_defensor], &missao_jogador);
                break;
                
            case 2: 
                if (verificar_missao(mapa, &missao_jogador)) {
                    printf("\n*** PARABÉNS! VOCÊ VENCEU! ***\n");
                    jogo_finalizado = 1;
                }
                break;

            case 0: 
                jogo_finalizado = 1;
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção de menu não reconhecida.\n");
                break;
        }
    }

    free(mapa);
    
    printf("\nFim do Desafio WAR Estruturado.\n");

    return 0;
}