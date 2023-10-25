#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

struct timeval t1, t2;

// Função para trocar dois elementos de um vetor
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para escolher um pivô e particionar o vetor
int particionar(int vetor[], int inicio, int fim) {
    int pivô = vetor[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (vetor[j] < pivô) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[fim]);
    return (i + 1);
}

// Função Quick Sort
void quickSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int pi = particionar(vetor, inicio, fim);
        quickSort(vetor, inicio, pi - 1);
        quickSort(vetor, pi + 1, fim);
    }
}

int main() {
    const int tamanho = 20; // Tamanho do vetor
    int *vetor = malloc(tamanho * sizeof(int)); // Alocar espaço para o vetor

    if (vetor == NULL) {
        printf("Falha na alocação de memória\n");
        return -1;
    }

    // Inicialização do gerador de números aleatórios
    srand(time(0));

    // Atribuir valores aleatórios de 1 a 20 não repetidos ao vetor
    for (int i = 0; i < tamanho; i++) {
        int numero;
        do {
            numero = rand() % 20 + 1;
            int repetido = 0;
            for (int j = 0; j < i; j++) {
                if (vetor[j] == numero) {
                    repetido = 1;
                    break;
                }
            }
            if (!repetido) {
                vetor[i] = numero;
                break;
            }
        } while (1);
    }

    printf("Vetor original: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    gettimeofday(&t1, NULL);
    quickSort(vetor, 0, tamanho - 1); // Chama a função Quick Sort
    gettimeofday(&t2, NULL);

    printf("Vetor ordenado: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("tempo total = %f\n", t_total);

    free(vetor); // Liberar memória alocada

    return 0;
}

