#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
    const int tamanho = 10; // Tamanho do vetor
    int vetor[] = {5, 2, 9, 1, 5, 6, 8, 3, 7, 4}; // Vetor de exemplo

    printf("Vetor original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    gettimeofday(&t1, NULL);	
    bubbleSort(vetor, tamanho); // Chama a função de ordenação Bubble Sort
    gettimeofday(&t2, NULL);

    printf("Vetor ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("tempo total = %f\n", t_total);

    return 0;
}

