#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include 'constants.h'

struct timeval t1, t2;

// Função para trocar dois elementos de um vetor
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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
    const int* arrays = {constants.ARRAY_SIZE_10, constants.ARRAY_SIZE_100, constants.ARRAY_SIZE_500, constants.ARRAY_SIZE_1000, constants.ARRAY_SIZE_5000, constants.ARRAY_SIZE_7000, constants.ARRAY_SIZE_10000, constants.ARRAY_SIZE_20000, constants.ARRAY_SIZE_50000, constants.ARRAY_SIZE_1000000};
    int n_repeticoes = 1;

    // printf("Vetor original: ");
    // for (int i = 0; i < tamanho; i++) {
    //    printf("%d ", vetor[i]);
    // }
    // printf("\n");

    for (int i = 0; i < sizeof(arrays); i++) {
        double tempo_total = 0;

        for (int j = 0; j < n_repeticoes; i++) {
            gettimeofday(&t1, NULL);	
            bubbleSort(vetor, tamanho); // Chama a função de ordenação Bubble Sort
            gettimeofday(&t2, NULL);
            double t_ordenacao = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
            tempo_total += t_ordenacao;
        }

        double tempo_medio = tempo_total / n_repeticoes;
        printf("Array de tamanho %f ordenado.", sizeof(arrays[i]));
        printf("%f iterações realizadas. \n", n_repeticoes);
        printf("Tempo médio de ordenação: %f", tempo_medio);
    }

    // printf("Vetor ordenado: ");
    // for (int i = 0; i < tamanho; i++) {
    //     printf("%d ", vetor[i]);
    //}
    // printf("\n");
    
    // printf("tempo total = %f\n", t_total);

    return 0;
}

