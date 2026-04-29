#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void FillInc(int* arr, int n) {
    for (int i = 1; i <= n; i++)
        arr[i] = i;
}

void FillDec(int* arr, int n) {
    for (int i = 1; i <= n; i++)
        arr[i] = n - i + 1;
}

void FillRand(int* arr, int n) {
    for (int i = 1; i <= n; i++)
        arr[i] = rand() % 1000;
}

int summ_mass(int* arr, int n) {
    int summ = 0;
    for (int i = 1; i <= n; i++)
        summ += arr[i];
    return summ;
}

int count_series(int* arr, int n) {
    int series = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[i] < arr[i - 1])
            series++;
    }
    return series;
}

void BuildHeap(int* a, int L, int R, long* Cf, long* Mf) {
    int x = a[L];
    (*Mf)++;
    int i = L;
    while (1) {
        int j = 2 * i;
        if (j > R) break;
        if (j < R) {
            (*Cf)++;
            if (a[j + 1] > a[j])  
                j = j + 1;
        }
        (*Cf)++;
        if (x >= a[j]) break;
        
        a[i] = a[j];
        (*Mf)++;
        i = j;
    }
    a[i] = x;
    (*Mf)++;
}



void HeapSort(int* a, int n, long* Cf, long* Mf) {
    *Cf = 0;
    *Mf = 0;
    for (int L = n / 2; L >= 1; L--)
        BuildHeap(a, L, n, Cf, Mf);
    for (int R = n; R > 1; R--) {
        int temp = a[1];
        a[1] = a[R];
        a[R] = temp;
        (*Mf) += 3;
        BuildHeap(a, 1, R - 1, Cf, Mf);
    }
}

long theoretical_build_MC(int n) {
    double sum = 0;
    for (int L = n / 2; L >= 1; L--) {
        sum += log2((double)n / L) + 2;
        sum += 2 * log2((double)n / L);
    }
    return (long)sum;
}

long theoretical_sort_MC(int n) {
    double log_n = log2(n);
    double C = 2 * n * log_n + n + 2;
    double M = n * log_n + 6.5 * n - 4;
    return (long)(C + M);
}
void BuildOnly(int* a, int n, long* Cf, long* Mf) {
    *Cf = 0;
    *Mf = 0;
    for (int L = n / 2; L >= 1; L--)
        BuildHeap(a, L, n, Cf, Mf);
}
int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    
    printf("проверка правильности heapsort (n=500)\n");
    
    int n_test = 500;
    int* arr = malloc((n_test + 1) * sizeof(int));
    long Cf, Mf;
    
    // убывающий
    FillDec(arr, n_test);
    int sum_ub_before = summ_mass(arr, n_test);
    int series_ub_do = count_series(arr, n_test);
    HeapSort(arr, n_test, &Cf, &Mf);
    int sum_ub_after = summ_mass(arr, n_test);
    int series_ub = count_series(arr, n_test);
    printf("убывающий:\n сумма до: %d; сумма после: %d; серий до: %d; серий после: %d\n\n",
           sum_ub_before, sum_ub_after, series_ub_do, series_ub);
    
    // случайный
    FillRand(arr, n_test);
    int sum_cr_before = summ_mass(arr, n_test);
    int series_cr_do = count_series(arr, n_test);
    HeapSort(arr, n_test, &Cf, &Mf);
    int sum_cr_after = summ_mass(arr, n_test);
    int series_cr = count_series(arr, n_test);
    printf("случайный:\n сумма до: %d; сумма после: %d; серий до: %d; серий после: %d\n\n",
           sum_cr_before, sum_cr_after, series_cr_do, series_cr);
    
    // возрастающий
    FillInc(arr, n_test);
    int sum_inc_before = summ_mass(arr, n_test);
    int series_inc_do = count_series(arr, n_test);
    HeapSort(arr, n_test, &Cf, &Mf);
    int sum_inc_after = summ_mass(arr, n_test);
    int series_inc = count_series(arr, n_test);
    printf("возрастающий:\n сумма до: %d; сумма после: %d; серий до: %d; серий после: %d\n\n",
           sum_inc_before, sum_inc_after, series_inc_do, series_inc);
    
    free(arr);
    
    printf("таблица 1: трудоемкость построения пирамиды\n");
    printf("--------------------------------------------------\n");
    printf("|   n  | теоретич. |  убыв.  |  возр.  |  случ.  |\n");
    printf("|------|-----------|---------|---------|---------|\n");
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* a = malloc((n + 1) * sizeof(int));
        
        long theor = theoretical_build_MC(n);
        long MC_ub, MC_voz, MC_sl;
        
        FillDec(a, n);
        BuildOnly(a, n, &Cf, &Mf);
        MC_ub = Cf + Mf;
        
        FillInc(a, n);
        BuildOnly(a, n, &Cf, &Mf);
        MC_voz = Cf + Mf;
        
        FillRand(a, n);
        BuildOnly(a, n, &Cf, &Mf);
        MC_sl = Cf + Mf;
        
        printf("| %4d | %9ld | %7ld | %7ld | %7ld |\n",
               n, theor, MC_ub, MC_voz, MC_sl);
        printf("|------|-----------|---------|---------|---------|\n");
        
        free(a);
    }
    
    printf("\n");
    printf("таблица 2: трудоемкость пирамидальной сортировки\n");
    printf("--------------------------------------------------\n");
    printf("|   n  | теоретич. |  убыв.  |  возр.  |  случ.  |\n");
    printf("|------|-----------|---------|---------|---------|\n");
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* a = malloc((n + 1) * sizeof(int));
        
        long theor = theoretical_sort_MC(n);
        long MC_ub, MC_voz, MC_sl;
        
        FillDec(a, n);
        HeapSort(a, n, &Cf, &Mf);
        MC_ub = Cf + Mf;
        
        FillInc(a, n);
        HeapSort(a, n, &Cf, &Mf);
        MC_voz = Cf + Mf;
        
        FillRand(a, n);
        HeapSort(a, n, &Cf, &Mf);
        MC_sl = Cf + Mf;
        
        printf("| %4d | %9ld | %7ld | %7ld | %7ld |\n",
               n, theor, MC_ub, MC_voz, MC_sl);
        printf("|------|-----------|---------|---------|---------|\n");
        
        free(a);
    }
    
    printf("\n");
    printf("вывод:\n");
    printf("1. пирамидальная сортировка не зависит от исходной упорядоченности\n");
    printf("2. m+c для убыв., возр. и случ. массивов примерно одинаковы\n");
    
    return 0;
}