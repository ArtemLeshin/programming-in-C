#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long Cf = 0;
long Mf = 0;

void FillInc(int* arr, int n) {
    for (int i = 1; i <= n; i++) arr[i] = i;
}

void FillDec(int* arr, int n) {
    for (int i = 1; i <= n; i++) arr[i] = n - i + 1;
}

void FillRand(int* arr, int n) {
    for (int i = 1; i <= n; i++) arr[i] = rand() % 1000;
}

int summ_mass(int* arr, int n) {
    int summ = 0;
    for (int i = 1; i <= n; i++) summ += arr[i];
    return summ;
}

int count_series(int* arr, int n) {
    int series = 1;
    for (int i = 2; i <= n; i++) {
        if (arr[i] < arr[i - 1]) series++;
    }
    return series;
}

void QuickSort(int* a, int L, int R) {
    int x = a[L];
    Mf++;
    int i = L, j = R;
    while (i <= j) {
        while (a[i] < x) {
            Cf++;
            i++;
        }
        Cf++;
        while (a[j] > x) {
            Cf++;
            j--;
        }
        Cf++;
        if (i <= j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            Mf += 3;
            i++;
            j--;
        }
    }
    if (L < j) QuickSort(a, L, j);
    if (i < R) QuickSort(a, i, R);
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500};
    int n_test = 500;
    int* arr = malloc((n_test + 1) * sizeof(int));
    
    printf("Проверка правильности QuickSort (n=%d)\n", n_test);
    
    FillRand(arr, n_test);
    int s_before = summ_mass(arr, n_test);
    int ser_before = count_series(arr, n_test);
    
    Cf = 0; Mf = 0;
    QuickSort(arr, 1, n_test);
    
    printf("Случайный массив:\n");
    printf(" Сумма: до = %d, после = %d\n", s_before, summ_mass(arr, n_test));
    printf(" Серий: до = %d, после = %d\n\n", ser_before, count_series(arr, n_test));

    printf("Таблица: Трудоемкость метода Хоара\n");
    printf("-------------------------------------------------------\n");
    printf("|  N  |  Убыв. (M+C)  |  Возр. (M+C)  |  Случ. (M+C)  |\n");
    printf("-------------------------------------------------------\n");

    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* a = malloc((n + 1) * sizeof(int));
        long MC_ub, MC_voz, MC_sl;

        FillDec(a, n); Cf = 0; Mf = 0;
        QuickSort(a, 1, n);
        MC_ub = Cf + Mf;

        FillInc(a, n); Cf = 0; Mf = 0;
        QuickSort(a, 1, n);
        MC_voz = Cf + Mf;

        FillRand(a, n); Cf = 0; Mf = 0;
        QuickSort(a, 1, n);
        MC_sl = Cf + Mf;

        printf("| %3d | %13ld | %13ld | %13ld |\n", 
               n, MC_ub, MC_voz, MC_sl);
        
        free(a);
    }
    printf("------------------------------------------------------\n");

    printf("\nВывод:\n");
    printf("Метод Хоара с опорным первым элементом сильно зависит от упорядоченности.\n");
    printf("На возр./убыв. массивах трудоемкость растет как N^2 (худший случай),\n");
    printf("в то время как на случайных данных она близка к N*logN.\n");

    free(arr);
    return 0;
}
