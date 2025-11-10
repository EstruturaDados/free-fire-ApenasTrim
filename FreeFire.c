#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CAPACIDADE 10
#define TAM_NOME 30
#define TAM_TIPO 20

typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

Item mochila[MAX_CAPACIDADE];
int numItens = 0;

void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void exibirMenu() {
    limparTela();
    printf("================================================\n");
    printf("🎒 INVENTÁRIO BÁSICO (Itens: %d/%d)\n", numItens, MAX_CAPACIDADE);
    printf("------------------------------------------------\n");
    printf("1. ➕ Cadastrar novo item\n");
    printf("2. ➖ Remover item pelo nome\n");
    printf("3. 📜 Listar todos os itens\n");
    printf("4. 🔍 Buscar item por nome (Sequencial)\n");
    printf("0. 🛑 Sair do Sistema\n");
    printf("================================================\n");
    printf("Escolha uma ação: ");
}

void inserirItem() {
    if (numItens >= MAX_CAPACIDADE) {
        printf("\n[ALERTA] A mochila está cheia! Não é possível adicionar mais itens.\n");
        goto fim_operacao;
    }

    printf("\n--- CADASTRO DE ITEM ---\n");
    
    int c;


    printf("Nome do item: ");
    fgets(mochila[numItens].nome, TAM_NOME, stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = '\0';

    printf("Tipo (arma, munição, cura, ferramenta): ");
    fgets(mochila[numItens].tipo, TAM_TIPO, stdin);
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    if (scanf("%d", &mochila[numItens].quantidade) != 1 || mochila[numItens].quantidade <= 0) {
        printf("\n[ERRO] Quantidade inválida. Operação cancelada.\n");
        while ((c = getchar()) != '\n' && c != EOF); 
        goto fim_operacao;
    }
    
    numItens++;
    printf("\n[SUCESSO] Item '%s' cadastrado na mochila.\n", mochila[numItens - 1].nome);

    fim_operacao:
    printf("\nPressione ENTER para voltar ao menu...");
    while ((c = getchar()) != '\n' && c != EOF); 
}

void removerItem() {
    if (numItens == 0) {
        printf("\n[INFO] A mochila está vazia. Nada para remover.\n");
        goto fim_operacao;
    }

    char nomeParaRemover[TAM_NOME];
    printf("\n--- REMOÇÃO DE ITEM ---\n");
    
    int c;

    printf("Nome exato do item a ser removido: ");
    fgets(nomeParaRemover, TAM_NOME, stdin);
    nomeParaRemover[strcspn(nomeParaRemover, "\n")] = '\0';

    int indiceEncontrado = -1;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeParaRemover) == 0) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1) {
        for (int i = indiceEncontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("\n[SUCESSO] Item '%s' removido.\n", nomeParaRemover);
    } else {
        printf("\n[ERRO] Item '%s' não encontrado na mochila.\n", nomeParaRemover);
    }
    
    fim_operacao:
    printf("Pressione ENTER para voltar ao menu...");
    while ((c = getchar()) != '\n' && c != EOF); 
}

void listarItens() {
    if (numItens == 0) {
        printf("\n[INFO] A mochila está vazia. Colete recursos primeiro!\n");
        goto fim_operacao;
    }

    printf("\n--- LISTAGEM DE ITENS DA MOCHILA ---\n");
    printf("========================================================\n");
    printf("| %-25s | %-15s | %-7s |\n", "NOME", "TIPO", "QTD");
    printf("========================================================\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-25s | %-15s | %-7d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }

    printf("========================================================\n");
    printf("Total de slots ocupados: %d\n", numItens);

    fim_operacao:
    printf("\nPressione ENTER para voltar ao menu...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

void buscarItem() {
    if (numItens == 0) {
        printf("\n[INFO] A mochila está vazia. Nada para buscar.\n");
        goto fim_operacao;
    }

    char nomeBuscar[TAM_NOME];
    printf("\n--- BUSCA SEQUENCIAL ---\n");
    
    int c;

    printf("Digite o NOME do item que deseja localizar: ");
    fgets(nomeBuscar, TAM_NOME, stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';
    
    int indiceResultado = -1;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            indiceResultado = i;
            break;
        }
    }
    
    printf("\n--- RESULTADO DA BUSCA ---\n");
    if (indiceResultado != -1) {
        printf("[SUCESSO] Item encontrado!\n");
        printf("Nome: %s\n", mochila[indiceResultado].nome);
        printf("Tipo: %s\n", mochila[indiceResultado].tipo);
        printf("Quantidade: %d\n", mochila[indiceResultado].quantidade);
    } else {
        printf("[FALHA] O item '%s' não foi encontrado na mochila.\n", nomeBuscar);
    }
    
    fim_operacao:
    printf("Pressione ENTER para voltar ao menu...");
    while ((c = getchar()) != '\n' && c != EOF); 
}

int main() {
    int opcao;
    int c; 

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            printf("\n[ERRO] Entrada inválida. Digite apenas números de 0 a 4.\n");
            opcao = -1;

            while ((c = getchar()) != '\n' && c != EOF); 
        } else {

            while ((c = getchar()) != '\n' && c != EOF); 
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\nSistema encerrado. Prepare-se para o próximo nível!\n");
                break;
            default:
                printf("\nOpção desconhecida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
