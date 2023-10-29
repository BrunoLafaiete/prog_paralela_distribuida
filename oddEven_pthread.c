#include <pthread.h>
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct timeval t1, t2;
int tmp;

struct ArrayData {
    int *array;
    int size;
};

void* compare(void* arg) {
    struct ArrayData *data = (struct ArrayData*)arg;
    int index = tmp;
    tmp = tmp + 2;

    if (data->array[index] > data->array[index + 1] && index + 1 < data->size) {
        int temp = data->array[index];
        data->array[index] = data->array[index + 1];
        data->array[index + 1] = temp;
    }

    return NULL;
}

int* gerarArrayAleatorio(int tamanho) {
    srand(time(NULL));
    int* array = (int*)malloc(sizeof(int) * tamanho);
    if (array == NULL) {
        printf("Falha na alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < tamanho; i++) {
        array[i] = rand()%10;
    }

    return array;
}

void oddEven(int max_threads, struct ArrayData* arrayData) {
    int i, j;
    pthread_t threads[max_threads];

    for (i = 0; i < arrayData->size; i++) {
        tmp = i % 2; // Use tmp as a flag to determine whether to start from even or odd index

        for (j = 0; j < max_threads; j++) {
            pthread_create(&threads[j], NULL, compare, arrayData);
        }

        for (j = 0; j < max_threads; j++) {
            pthread_join(threads[j], NULL);
        }
    }
}

// void printArray()
// {
//     int i;
//     for (i = 0; i < n; i++)
//         printf("%d ", vetor[i]);
//     printf("\n");
// }

int main() {
    int n_repeticoes = 50;
    int tamanhos[9] = {10, 100, 1000, 5000, 10000, 20000, 50000, 100000, 500000};
    int n_threads[5] = {2, 4, 8, 16, 32};

    for (int i = 0; i < 9; i++) {
        int tamanho_do_array = tamanhos[i];

        int* array_to_order = gerarArrayAleatorio(tamanho_do_array);

        for (int t = 0; t < 5; t++) {
            int max_threads = n_threads[t];
            pthread_t threads[max_threads];

            double tempo_total = 0;

            for (int j = 0; j < n_repeticoes; j++) {
                if (j==0 && (tamanho_do_array == 10 || tamanho_do_array == 100)) {
                    printf("array para ordenar \n");
                    for (int s = 0; s < tamanho_do_array; s++) {
                        printf("%d ", array_to_order[s]);
                    }
                    printf("\n");
                }

                struct ArrayData* thread_data = (struct ArrayData*)malloc(sizeof(struct ArrayData));
                thread_data->size = tamanho_do_array;
                thread_data->array = (int*)malloc(sizeof(int) * tamanho_do_array);
                memcpy(thread_data->array, array_to_order, sizeof(int) * tamanho_do_array);
                gettimeofday(&t1, NULL);
                oddEven(max_threads, thread_data);
                gettimeofday(&t2, NULL);
                double t_ordenacao = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
                tempo_total += t_ordenacao;

                if (j == 0 && (tamanho_do_array == 10 || tamanho_do_array == 100)) {
                    printf("array ordenado \n");
                    for (int s = 0; s < tamanho_do_array; s++) {
                        printf("%d ", thread_data->array[s]);
                    }
                    printf("\n");
                }

                free(thread_data);
            }

            double tempo_medio = tempo_total / n_repeticoes;
            printf("\n");
            printf("Numero de Threads utilizadas: %u \n", max_threads);
            printf("Array de tamanho %u ordenado. \n", tamanho_do_array);
            printf("%d iterações realizadas. \n", n_repeticoes);
            printf("Tempo médio de ordenação: %f.\n", tempo_medio);
            printf("\n");

        }
    }
    return 0;
}
