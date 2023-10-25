#include <stdio.h>
#include <omp.h>
#include <sys/time.h>

#define n 8

struct timeval t1, t2;

int a[] = {2, 1, 4, 9, 5, 3, 6, 10};

void compare(int index)
{
    if (a[index] > a[index + 1] && index + 1 < n)
    {
        int temp = a[index];
        a[index] = a[index + 1];
        a[index + 1] = temp;
    }
}

void oddEven()
{
    int i, j;
    for (i = 1; i <= n; i++)
    {
        if (i % 2 == 1)
        {
#pragma omp parallel for shared(a) private(j) 
            for (j = 0; j < n - 1; j += 2)
            {
                compare(j);
            }
        }
        else
        {
#pragma omp parallel for shared(a) private(j) 
            for (j = 1; j < n - 1; j += 2)
            {
                compare(j);
            }
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
    printf("Given array is: ");
    printArray();

    gettimeofday(&t1, NULL);
    oddEven();
    gettimeofday(&t2, NULL);

    printf("\nSorted array is: ");
    printArray();
    
    double t_total = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("tempo total = %f\n", t_total);

    return 0;
}
