#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#define n 8

struct timeval t1, t2;

int max_threads = (n + 1) / 2;

int a[] = { 2, 1, 4, 9, 5, 3, 6, 10 };
int tmp;

void* compare(void* arg)
{
    int index = tmp;
    tmp = tmp + 2;

    if ((a[index] > a[index + 1]) && (index + 1 < n)) {
        int temp = a[index];
        a[index] = a[index + 1];
        a[index + 1] = temp;
    }
    return NULL;
}

void oddEven(pthread_t threads[])
{
    int i, j;

    for (i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            tmp = 0;

            for (j = 0; j < max_threads; j++)
                pthread_create(&threads[j], NULL, compare, NULL);

            for (j = 0; j < max_threads; j++)
                pthread_join(threads[j], NULL);
        }
        else {
            tmp = 1;

            for (j = 0; j < max_threads - 1; j++)
                pthread_create(&threads[j], NULL, compare, NULL);

            for (j = 0; j < max_threads - 1; j++)
                pthread_join(threads[j], NULL);
        }
    }
}

void printArray()
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main()
{
    pthread_t threads[max_threads];

    printf("Given array is: ");
    printArray();

    gettimeofday(&t1, NULL);
    oddEven(threads);
    gettimeofday(&t2, NULL);

    printf("\nSorted array is: ");
    printArray();
    
    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("tempo total = %f\n", t_total);

    return 0;
}
