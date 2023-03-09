#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX 100001
#define NUM 50
#define ALGOS 3

typedef double (*Algorithm)(int*, int);
typedef struct timespec Time;

void random_fill(int*, int);
double calc_time(Time, Time);
double* func_exe(short int*, Algorithm);
double bubble1(int*, int);
double bubble2(int*, int);
double bubble3(int*, int);

int main()
{
    srand((unsigned) time(NULL));
    short int elements[5] = {20, 50, 100, 500, 1000};
    Algorithm algorithms[ALGOS] = {bubble1, bubble2, bubble3};
    double* table[ALGOS];

    for (int i = 0; i < ALGOS; i++)
    {
        table[i] = func_exe(elements, algorithms[i]);
    }

    for (int i = 0; i < ALGOS; i++)
    {
        printf("Algorithm %d:\n", i+1);
        for (int j = 0; j < 5; j++)
        {
            printf("\tInput size: %d, average time: %lf\n", elements[j], table[i][j]);
        }
        free(table[i]);
    }

    return 0;
}

void random_fill(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % MAX;
}

double* func_exe(short int *elems, Algorithm algo)
{
    double *times = malloc(5 * sizeof(double));
    double mean_time, sum_time;
    int *nums = NULL;
    for (int i = 0; i < 5; i++)
    {
        sum_time = 0;
        nums = malloc(elems[i] * sizeof(int));
        printf("%d elementi:\n", elems[i]);
        for (int j = 0; j < NUM; j++)
        {
            random_fill(nums, elems[i]);
            printf("%d)\t", j + 1);
            sum_time += algo(nums, elems[i]);
        }
        mean_time = sum_time / NUM;
        times[i] = mean_time;
        free(nums);
        nums = NULL;
    }
    return times;
}

double calc_time(Time start, Time end)
{
    Time elapsed_time;
    elapsed_time.tv_sec = end.tv_sec - start.tv_sec;
    elapsed_time.tv_nsec = end.tv_nsec - start.tv_nsec;
    if(elapsed_time.tv_nsec < 0)
    {
        elapsed_time.tv_sec--;
        elapsed_time.tv_nsec += 1000000000;
    }
    return ((double)elapsed_time.tv_sec + ((double)elapsed_time.tv_nsec / 1000000000));
}

double bubble1(int *arr, int n)
{
    Time start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            if (arr[j] > arr[j + 1]) {
                arr[j] += arr[j + 1];
                arr[j + 1] = arr[j] - arr[j + 1];
                arr[j] -= arr[j + 1];
            }
    clock_gettime(CLOCK_REALTIME, &end_time);
    printf("Bubble1 done!\t");
    return calc_time(start_time, end_time);
}

double bubble2(int *arr, int n)
{
    Time start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (arr[j] > arr[j + 1]) {
                arr[j] += arr[j + 1];
                arr[j + 1] = arr[j] - arr[j + 1];
                arr[j] -= arr[j + 1];
            }
    clock_gettime(CLOCK_REALTIME, &end_time);
    printf("Bubble2 done!\t");
    return calc_time(start_time, end_time);
}

double bubble3(int *arr, int n)
{
    int ordered;
    Time start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);
    do{
        ordered = 1;
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - 1 - i; j++)
                if (arr[j] > arr[j + 1]) {
                    arr[j] += arr[j + 1];
                    arr[j + 1] = arr[j] - arr[j + 1];
                    arr[j] -= arr[j + 1];
                    ordered = 0;
                }
    }while(!ordered);
    clock_gettime(CLOCK_REALTIME, &end_time);
    printf("Bubble3 done!\t");
    return calc_time(start_time, end_time);
}