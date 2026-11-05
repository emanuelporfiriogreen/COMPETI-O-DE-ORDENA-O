Competição de Ordenação: O Desafio dos Milissegundos

Repositório dedicado à implementação e otimização de algoritmos de ordenação em linguagem C para o menor tempo de processamento de CPU, isolando a medição de tempo estritamente na função de ordenação conforme o regulamento da competição.

Pré-requisitos

Certifique-se de ter um compilador C compatível instalado, como o GCC ou MinGW-w64.

Como Compilar e Executar

Certifique-se de que o arquivo de dados (ListahAhSerOrdenada.txt ou numeros.txt) está na mesma pasta do código-fonte ordenador_v2.c.

Abra o terminal na pasta do projeto e compile o código utilizando as flags de otimização máxima:

gcc -O3 -flto -march=native ordenador_v2.c -o ordenador.exe

Execute o programa no terminal:

./ordenador.exe
