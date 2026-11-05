#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparar(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    // A leitura do arquivo em disco NÃO deve entrar na contagem de tempo da ordenação
    FILE *arquivo = fopen("ListahAhSerOrdenada.txt", "rb");
    if (!arquivo) {
        // Tenta o nome alternativo caso o arquivo se chame numeros.txt
        arquivo = fopen("numeros.txt", "rb");
    }
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de entrada!\n");
        return 1;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_bytes = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);

    char *buffer = malloc(tamanho_bytes + 1);
    if (!buffer) {
        printf("Erro de alocação de memória para o buffer!\n");
        fclose(arquivo);
        return 1;
    }

    long lidos = fread(buffer, 1, tamanho_bytes, arquivo);
    buffer[lidos] = '\0';
    fclose(arquivo);

    int capacidade = 12000000;
    int *numeros = malloc(capacidade * sizeof(int));
    if (!numeros) {
        printf("Erro de alocação de memória para os números!\n");
        free(buffer);
        return 1;
    }

    int tamanho = 0;
    char *cursor = buffer;
    while (*cursor) {
        while (*cursor && *cursor <= ' ') cursor++;
        if (!*cursor) break;
        
        int num = 0;
        int negativo = 0;
        if (*cursor == '-') {
            negativo = 1;
            cursor++;
        }
        while (*cursor >= '0' && *cursor <= '9') {
            num = num * 10 + (*cursor - '0');
            cursor++;
        }
        numeros[tamanho++] = negativo ? -num : num;
    }
    free(buffer);

    // ==========================================
    // INÍCIO DA MEDIÇÃO EXATA DA ORDENAÇÃO (Regra da competição)
    // ==========================================
    clock_t inicio = clock();

    qsort(numeros, tamanho, sizeof(int), comparar);

    clock_t fim = clock();
    // ==========================================
    // FIM DA MEDIÇÃO
    // ==========================================

    double tempo_gasto_ms = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;

    printf("Total de elementos ordenados: %d\n", tamanho);
    printf("Tempo de processamento da ordenacao: %.2f ms\n", tempo_gasto_ms);

    free(numeros);
    return 0;
}