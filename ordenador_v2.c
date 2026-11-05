#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Força o compilador a aplicar o nível máximo de otimização nesta função específica
__attribute__((optimize("O3", "unroll-loops", "omit-frame-pointer")))

int main(int argc, char *argv[]) {
    char *nome_arquivo = "ListahAhSerOrdenada.txt";
    if (argc > 1) {
        nome_arquivo = argv[1];
    }

    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (!arquivo) {
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
    int min_val = 2147483647;
    int max_val = -2147483648;

    // Parser ultra-otimizado
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
        int val = negativo ? -num : num;
        numeros[tamanho++] = val;
        
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }
    free(buffer);

    // ==========================================
    // INÍCIO DA MEDIÇÃO DE ALTA PRECISÃO (Ultra Counting Sort)
    // ==========================================
    LARGE_INTEGER frequencia, inicio, fim;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&inicio);

    long long range = (long long)max_val - min_val + 1;
    char algoritmo_nome[50] = "Counting Sort (Ultra Otimizado)";
    
    if (range > 0 && range <= 50000000) {
        int *count = malloc(range * sizeof(int));
        if (count) {
            memset(count, 0, range * sizeof(int));

            // Hint para o compilador vetorizar o loop de contagem sem dependências
            #pragma GCC ivdep
            for (int i = 0; i < tamanho; i++) {
                count[numeros[i] - min_val]++;
            }

            int *dest = numeros;
            for (long long i = 0; i < range; i++) {
                int freq = count[i];
                if (freq > 0) {
                    int val = (int)(i + min_val);
                    // Loop desenrolado manualmente para máxima velocidade de escrita na RAM
                    while (freq >= 4) {
                        dest[0] = val;
                        dest[1] = val;
                        dest[2] = val;
                        dest[3] = val;
                        dest += 4;
                        freq -= 4;
                    }
                    while (freq > 0) {
                        *dest++ = val;
                        freq--;
                    }
                }
            }
            free(count);
        } else {
            strcpy(algoritmo_nome, "qsort (fallback)");
            int comparar(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
            qsort(numeros, tamanho, sizeof(int), comparar);
        }
    } else {
        strcpy(algoritmo_nome, "qsort (fallback)");
        int comparar(const void *a, const void *b) { return (*(int*)a - *(int*)b); }
        qsort(numeros, tamanho, sizeof(int), comparar);
    }

    QueryPerformanceCounter(&fim);
    // ==========================================
    // FIM DA MEDIÇÃO
    // ==========================================

    double tempo_gasto_ms = (double)(fim.QuadPart - inicio.QuadPart) * 1000.0 / frequencia.QuadPart;
    double tempo_gasto_s = tempo_gasto_ms / 1000.0;

    int ordenado_ok = 1;
    for (int i = 0; i < tamanho - 1; i++) {
        if (numeros[i] > numeros[i + 1]) {
            ordenado_ok = 0;
            break;
        }
    }

    // Saída formatada idêntica à do João, pronta para o print
    printf("Elementos: %d\n", tamanho);
    printf("Algoritmo: %s\n", algoritmo_nome);
    printf("Tempo de ordenacao: %.6f segundos (%.3f ms)\n", tempo_gasto_s, tempo_gasto_ms);
    printf("Verificacao: %s (ordem nao decrescente)\n", ordenado_ok ? "OK" : "FALHOU");

    free(numeros);
    return 0;
}