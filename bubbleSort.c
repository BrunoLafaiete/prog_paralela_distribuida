#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

struct timeval t1, t2;

// Função para trocar dois elementos de um vetor
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int* gerarArrayAleatorio(int tamanho) {
    srand(time(NULL));
    int* array = (int*)malloc(sizeof(int) * tamanho);
    if (array == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < tamanho; i++) {
        array[i] = rand();
    }

    return array;
}

// Função de ordenação Bubble Sort
void bubbleSort(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j] > vetor[j + 1]) {
                trocar(&vetor[j], &vetor[j + 1]);
            }
        }
    }
}

int main() {
    int n_repeticoes = 50;
    int tamanhos[9] = {10, 100, 1000, 5000, 10000, 20000, 50000, 100000, 500000};

    for (int i = 0; i < 9; i++) {
        int tamanho_do_array = tamanhos[i];
        double tempo_total = 0;

        int* array_to_order = gerarArrayAleatorio(tamanho_do_array);

        for (int j = 0; j < n_repeticoes; j++) {
            // if (j==0 && (tamanho_do_array == 10 || tamanho_do_array == 100)) {
            //     printf("array para ordenar \n");
            //     for (int s = 0; s < tamanho_do_array; s++) {
            //         printf("%d ", array_to_order[s]);
            //     }
            //     printf("\n");
            // }

            int* array_copy = malloc(sizeof(int) * tamanho_do_array); // Cria uma cópia do vetor
            memcpy(array_copy, array_to_order, sizeof(int) * tamanho_do_array);

            gettimeofday(&t1, NULL);
            bubbleSort(array_copy, tamanho_do_array); // Chama a função de ordenação Bubble Sort
            gettimeofday(&t2, NULL);
            double t_ordenacao = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
            tempo_total += t_ordenacao;

            // if (j == 0 && (tamanho_do_array == 10 || tamanho_do_array == 100)) {
            //     printf("array ordenado \n");
            //     for (int s = 0; s < tamanho_do_array; s++) {
            //         printf("%d ", array_copy[s]);
            //     }
            //     printf("\n");
            // }

            free(array_copy);
        }

        double tempo_medio = tempo_total / n_repeticoes;
        printf("\n");
        printf("Array de tamanho %u ordenado. \n", tamanho_do_array);
        printf("%d iterações realizadas. \n", n_repeticoes);
        printf("Tempo médio de ordenação: %f.\n", tempo_medio);
        printf("\n");
    }
    
    return 0;
}

