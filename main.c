#include "avl.c"
#include "rn.c"
#include "b.c"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define NUM_SETS 10            // Número de conjuntos por tamanho
#define RESETA 0
#define MAX_RANDOM 10000       // Tamanho máximo de chave

extern long int avlCount;
extern long int rnCount;
extern long int bCount;  

// Função para preencher o vetor com números aleatórios únicos
void fillArrayWithUniqueValues(int arr[], int size) {
    int i = 0;
    while (i < size) {
        int num = rand() % MAX_RANDOM; // Gerando números entre 0 e 9999
        int found = 0;

        // Verifica se o número já foi adicionado ao vetor
        for (int j = 0; j < i; j++) {
            if (arr[j] == num) {
                found = 1;
                break;
            }
        }

        if (!found) {
            arr[i++] = num;
        }
    }
}

// Função para obter o diretório atual e abrir o arquivo CSV
FILE* obterDiretorioEAbrirArquivo(const char* nomeArquivo) {
    char* path = (char*)malloc(FILENAME_MAX);
    if (!path) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    // Obtém o diretório do arquivo atual
    strcpy(path, __FILE__);
    char* separator = strrchr(path, '\\');
    if (separator) {
        *separator = '\0'; // Remove o nome do arquivo do caminho
    }

    // Cria o caminho completo do arquivo a ser aberto
    char filePath[FILENAME_MAX];
    snprintf(filePath, FILENAME_MAX, "%s\\csv\\%s", path, nomeArquivo);
    printf("Caminho do arquivo: %s\n", filePath);

    free(path);

    // Abre o arquivo para escrita e retorna o ponteiro do arquivo
    return fopen(filePath, "w");
}

int main() {
    srand(time(NULL));

    // Abre os arquivos para gravação
    FILE* addFile = obterDiretorioEAbrirArquivo("resultadoAdicao.csv");
    if (!addFile) {
        printf("Erro ao abrir arquivo para adição\n");
        return 1;
    }

    FILE* removeFile = obterDiretorioEAbrirArquivo("resultadoRemocao.csv");
    if (!removeFile) {
        printf("Erro ao abrir arquivo para remoção\n");
        fclose(addFile);
        return 1;
    }

    // Escreve os cabeçalhos no arquivo CSV
    fprintf(addFile, "n;RN;AVL;B-1;B-5;B-10\n");
    fprintf(removeFile, "n;RN;AVL;B-1;B-5;B-10\n");

    // Loop principal para diferentes tamanhos de conjuntos multiplos de 2
    for (int j = 1; j <= MAX_RANDOM; j *= 2) {  
        long int rnAdd = RESETA,
        avlAdd = RESETA,
        b1Add = RESETA,
        b5Add = RESETA,
        b10Add = RESETA;
        long int rnRemove = RESETA,
        avlRemove = RESETA,
        b1Remove = RESETA,
        b5Remove = RESETA,
        b10Remove = RESETA;

        // Aloca espaço para o vetor de números
        int* arr = malloc(j * sizeof(int));

        // Preenche o vetor com valores únicos aleatórios
        fillArrayWithUniqueValues(arr, j);

        // Realiza a execução 10 vezes para cada conjunto
        for (int set = 0; set < NUM_SETS; set++) {

            // Cria as árvores
            ArvoreAVL* avlTree = criarArvoreAVL();
            ArvoreRN* rnTree = criarArvoreRN();
            ArvoreB* bTree1 = criarArvoreB(1);
            ArvoreB* bTree5 = criarArvoreB(5);
            ArvoreB* bTree10 = criarArvoreB(10);

            // Adiciona os valores do conjunto nas árvores
            for (int i = 0; i < j; i++) {
                int value = arr[i];

                avlCount = RESETA;
                adicionarValorAVL(avlTree, value);
                avlAdd += avlCount;

                rnCount = RESETA;
                adicionarValorRN(rnTree, value);
                rnAdd += rnCount;

                bCount = RESETA;
                adicionaChaveB(bTree1, value);
                b1Add += bCount;

                bCount = RESETA;
                adicionaChaveB(bTree5, value);
                b5Add += bCount;

                bCount = RESETA;
                adicionaChaveB(bTree10, value);
                b10Add += bCount;
            }

            // Remove os valores do conjunto das árvores
            for (int i = 0; i < j; i++) {
                int randIdx = rand() % (j + 1);
                int randVal = (randIdx == j) ? -1 : arr[randIdx];

                avlCount = RESETA;
                removerValorAVL(avlTree, randVal);
                avlRemove += avlCount;

                rnCount = RESETA;
                removerValorRN(rnTree, randVal);
                rnRemove += rnCount;

                bCount = RESETA;
                removerChaveB(bTree1, randVal);
                b1Remove += bCount;

                bCount = RESETA;
                removerChaveB(bTree5, randVal);
                b5Remove += bCount;

                bCount = RESETA;
                removerChaveB(bTree10, randVal);
                b10Remove += bCount;
            }

            // Libera memória das árvores
            free(avlTree);
            free(rnTree);
            free(bTree1);
            free(bTree5);
            free(bTree10);
        }

        // Escreve as médias no arquivo CSV
        fprintf(addFile,
                "%d;%ld;%ld;%ld;%ld;%ld\n",
                j,
                rnAdd / NUM_SETS,
                avlAdd / NUM_SETS,
                b1Add / NUM_SETS,
                b5Add / NUM_SETS,
                b10Add / NUM_SETS
        );

        fprintf(removeFile,
                "%d;%ld;%ld;%ld;%ld;%ld\n",
                j,
                rnRemove / NUM_SETS,
                avlRemove / NUM_SETS,
                b1Remove / NUM_SETS,
                b5Remove / NUM_SETS,
                b10Remove / NUM_SETS
        );
    }

    fclose(addFile);
    fclose(removeFile);

    printf("Encerrou");

    return 0;
}
