#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct timeval t1, t2;

void compare(int vetor[], int index1, int index2)
{
    if (vetor[index1] > vetor[index2])
    {
        int temp = vetor[index1];
        vetor[index1] = vetor[index2];
        vetor[index2] = temp;
    }
}

void oddEven(int vetor[], int tamanho)
{
    int i, j;
    for (i = 0; i < tamanho; i++)
    {
        if (i % 2 == 0)
        {
            #pragma omp parallel for
            for (j = 1; j < tamanho - 1; j += 2)
            {
                compare(vetor, j, j + 1);
            }
        }
        else
        {
            #pragma omp parallel for
            for (j = 0; j < tamanho - 1; j += 2)
            {
                compare(vetor, j, j + 1);
            }
        }
    }
}

int* gerarArrayAleatorio(int tamanho) {
    srand(time(NULL));
    int* array = (int*)malloc(sizeof(int) * tamanho);
    if (array == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < tamanho; i++) {
        array[i] = rand()%1000;
    }

    return array;
}

// void printArray()
// {
//     int i;
//     for (i = 0; i < n; i++)
//         printf("%d ", a[i]);
//     printf("\n");
// }

int main() {
    int n_repeticoes = 5;
    int tamanhos[1] = {500000};
    int n_threads[2] = {16, 32};

    for (int i = 0; i < 1; i++) {
        int tamanho_do_array = tamanhos[i];

        int* array_to_order = gerarArrayAleatorio(tamanho_do_array);

        for (int t = 0; t < 5; t++) {
            int max_threads = n_threads[t];
            omp_set_num_threads(max_threads);
            double tempo_total = 0;

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
                oddEven(array_copy, tamanho_do_array);
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
            printf("Numero de Threads utilizadas: %u \n", max_threads);
            printf("Array de tamanho %u ordenado. \n", tamanho_do_array);
            printf("%d iterações realizadas. \n", n_repeticoes);
            printf("Tempo médio de ordenação: %f.\n", tempo_medio);
            printf("\n");
        }

        free(array_to_order);
    }

    return 0;
}
