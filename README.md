# Competição de Ordenação: O Desafio dos Milissegundos

Repositório dedicado à implementação e otimização de algoritmos de ordenação em linguagem C para o menor tempo de processamento de CPU, isolando a medição de tempo estritamente na função de ordenação (`qsort`) conforme o regulamento da competição.

## ⚙️ Pré-requisitos
Certifique-se de ter um compilador C compatível instalado (como o GCC / MinGW-w64).

## 🚀 Como Compilar e Executar

1. Certifique-se de que o arquivo de dados (`ListahAhSerOrdenada.txt` ou `numeros.txt`) está na mesma pasta do código-fonte (`main.c`).
2. Abra o terminal na pasta do projeto e compile o código utilizando as flags de otimização máxima (`-O3` e `-flto`):
   ```bash
   gcc -O3 -flto main.c -o ordenador.exe

Execute o programa 
./ordenador.exe
