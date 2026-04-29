#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
void FillInc(int* arr, int n){
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}
void FillDec(int* arr, int n){
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}
void FillRand(int* arr, int n){
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 1000;
}
int summ_mass(int* arr, int n){
    int summ=0;
    for (int i =0; i <n;i++){
        summ+=arr[i];
    }
    return summ;
}
int count_series(int* arr, int n){
    int series = 1;
    for (int i = 1; i < n; i++){
        if (arr[i] < arr[i - 1])
            series++;
    }
    return series;
}
void InsertSort(int* arr, int n, long* Cf, long* Mf) {
    *Cf = 0;
    *Mf = 0;
    for (int i = 1; i < n; i++) {
        int t = arr[i];
        (*Mf)++; 
        int j = i - 1;
        while (j >= 0) {
            (*Cf)++; 
            if (t < arr[j]) {
                arr[j + 1] = arr[j];
                (*Mf)++;
                j--;
            } else {
                break; 
            }
        }
        arr[j + 1] = t;
        (*Mf)++;
    }
}

void ShellSort_Knut(int* a, int n, long* Cf, long* Mf) {
    *Cf = 0;
    *Mf = 0;

    int h = 1;
    while (h <= pow(2,log2(n)-2)) {
        h = 2 * h + 1;
    }
    while (h > 0) {
        for (int i = h; i < n; i++) {
            int t = a[i];
            (*Mf)++;
            int j = i - h;
            while (j >= 0) {
                if (t < a[j]) {
                    (*Cf)++;
                    a[j + h] = a[j];
                    (*Mf)++;
                    j -= h;
                } else {
                    break;
                }
            }
            a[j + h] = t;
            (*Mf)++;
        }
        h /= 2;
    }
}

void ShellSort_nk(int* a, int n, long* Cf, long* Mf) {
    *Cf = 0;
    *Mf = 0;

    int h = 1;
    while (h <= n / 3) {
        h = 2 * h + 1;
    }

    while (h > 0) {
        for (int i = h; i < n; i++) {
            int t = a[i];
            (*Mf)++;
            int j = i - h;
            while (j >= 0) {
                if (t < a[j]) {
                    (*Cf)++;
                    a[j + h] = a[j];
                    (*Mf)++;
                    j -= h;
                } else {
                    break;
                }
            }
            a[j + h] = t;
            (*Mf)++;
        }
        h /= 2;
    }
}


int main(){
    srand(time(NULL));
    int sizes[] = {100,200,300,400,500};
    int n=500;
    int* arr = malloc(sizeof(int) * n);
    long Cf, Mf;
    printf("Проверим правильность сортировки для N=500:\n");


    // Убывающий
    FillDec(arr, n);
    int summ_ub_before=summ_mass(arr,n);
    int series_ub_do = count_series(arr, n);
    ShellSort_Knut(arr, n, &Cf, &Mf);
    int summ_ub_after=summ_mass(arr,n);
    int series_ub = count_series(arr, n);

    // Случайный
    FillRand(arr, n);
    int summ_cr_before=summ_mass(arr,n);
    int series_sr_do = count_series(arr, n);
    ShellSort_Knut(arr, n, &Cf, &Mf);
    int summ_cr_after=summ_mass(arr,n);
    int series_cr = count_series(arr, n);
    
    // Возрастающий
    FillInc(arr, n);
    int summ_voz_before=summ_mass(arr,n);
    int series_voz_do = count_series(arr, n);
    ShellSort_Knut(arr, n, &Cf, &Mf);
    int summ_voz_after=summ_mass(arr,n);
    int series_voz = count_series(arr, n);

    free(arr);
    printf("Убывающий:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_ub_before,summ_ub_after,series_ub_do,series_ub);
    printf("Случайный:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_cr_before,summ_cr_after,series_sr_do,series_cr);
    printf("Возрастающий:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_voz_before,summ_voz_after,series_voz_do,series_voz);    

    printf("-------------------------------------------------------------------------------------\n");
    printf("|   N  |      h1 … hm по      |         Insert Мф+Сф     |        Shell Мф+Сф       |\n");
    printf("|      |   формуле Д.Кнута    |  Убыв  |  Случ  |  Возр  |  Убыв  |  Случ  |  Возр  |\n");
    printf("|-----------------------------------------------------------------------------------|\n");
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* arr = malloc(sizeof(int) * n);
        int* work = malloc(sizeof(int) * n);
        long Cf, Mf;
        long MC_ub_K, MC_sl_K, MC_voz_K,MC_ub_I,MC_sl_I,MC_voz_I;

        // === УБЫВАЮЩИЙ МАССИВ ===
        FillDec(arr, n);                   
        for(int i=0; i<n; i++) work[i] = arr[i];  
        InsertSort(work, n, &Cf, &Mf);      
        MC_ub_I = Cf + Mf;
        
        for(int i=0; i<n; i++) work[i] = arr[i]; 
        ShellSort_Knut(work, n, &Cf, &Mf);
        MC_ub_K = Cf + Mf;

        // === СЛУЧАЙНЫЙ МАССИВ ===
        FillRand(arr, n);                   
        for(int i=0; i<n; i++) work[i] = arr[i];
        InsertSort(work, n, &Cf, &Mf);
        MC_sl_I = Cf + Mf;
        
        for(int i=0; i<n; i++) work[i] = arr[i];
        ShellSort_Knut(work, n, &Cf, &Mf);
        MC_sl_K = Cf + Mf;

        // === ВОЗРАСТАЮЩИЙ МАССИВ ===
        FillInc(arr, n);                    
        for(int i=0; i<n; i++) work[i] = arr[i];
        InsertSort(work, n, &Cf, &Mf);
        MC_voz_I = Cf + Mf;
        
        for(int i=0; i<n; i++) work[i] = arr[i];
        ShellSort_Knut(work, n, &Cf, &Mf);
        MC_voz_K = Cf + Mf;

        int m = (int)log2(n) - 1;
        int h[32];
        h[0] = 1;

        for (int i = 1; i < m; i++) {
            h[i] = 2 * h[i - 1] + 1;
        }

        char steps[256] = "";
        char temp[16];

        for (int i = 0; i < m; i++) {
            sprintf(temp, "%d ", h[i]);
            strcat(steps, temp);
        }
    
        
        printf("| %4d | %20s | %6ld | %6ld | %6ld | %6ld | %6ld | %6ld |\n", 
               n,steps,MC_ub_I,MC_sl_I,MC_voz_I, MC_ub_K, MC_sl_K, MC_voz_K);
        printf("|-----------------------------------------------------------------------------------|\n");
        free(arr);
        free(work);
    }
    printf("Шелл (по Кнуту) — лучший выбор для любых случайных данных.\n");
    printf("Вставки (Insert) — выигрывают только на идеально отсортированных массивах.\n");
    printf("---------------------------------------------------------------------------\n");
    printf("|   N  |       h1 … hm по     |  Shell |        h1 … hm по       |  Shell |\n");
    printf("|      |    формуле Д.Кнута   | Мф + Сф|      другой формуле     | Мф + Сф|\n");
    printf("|-------------------------------------------------------------------------|\n");
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* arr = malloc(sizeof(int) * n);
        int* work = malloc(sizeof(int) * n);
        FillRand(arr, n);

        long Cf, Mf;
        long MC_sl_nk, MC_sl_K;
        
        char knut_steps[256] = "";
        char other_steps[256] = ""; 
        char temp[16];
        int h = 1;

        while (h <= n / 3) {
            sprintf(temp, "%d ", h);
            strcat(knut_steps, temp);
            h = 3 * h + 1;
        }

        h = 1;
        other_steps[0] = '\0';

        while (h <= n / 3) {
            sprintf(temp, "%d ", h);
            strcat(other_steps, temp);
            h = 2 * h + 1;
        }
        
        for(int i=0; i<n; i++) work[i] = arr[i];
        ShellSort_nk(work, n, &Cf, &Mf);
        MC_sl_nk = Cf + Mf;

        for(int i=0; i<n; i++) work[i] = arr[i];
        ShellSort_Knut(work, n, &Cf, &Mf);
        MC_sl_K = Cf + Mf;

        printf("| %4d | %20s | %6ld | %23s | %6ld |\n", 
               n,knut_steps,MC_sl_K,other_steps,MC_sl_nk);
        printf("|-------------------------------------------------------------------------|\n");
        
        free(arr);
        free(work);
    }
    printf("Последовательность Дональда Кнута является более эффективным выбором.\n");
    return 0;
}

