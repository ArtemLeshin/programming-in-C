#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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
void ShakerSort(int *arr, int n, long* Cf, long* Mf){
    *Cf = 0;
    *Mf = 0;
    int L=0;
    int R=n-1;
    int k=n-1;
    while (L<R){
        for (int j=R;j>L;j--){
            (*Cf)++;
            if (arr[j]<arr[j-1]){
                int temp = arr[j]; 
                arr[j] = arr[j-1]; 
                arr[j-1] = temp; 
                (*Mf)+=3;
                k=j;
            }
        }
        L=k;
        for (int j=L;j<R;j++){
            (*Cf)++;
            if (arr[j]>arr[j+1]){
                int temp = arr[j]; 
                arr[j] = arr[j+1]; 
                arr[j+1] = temp; 
                (*Mf)+=3;
                k=j;
            }
        }
        R=k;        
    }
}
void SelectSort(int* arr, int n, long* Cf, long* Mf){
    *Cf = 0;
    *Mf = 0;
    for (int i = 0; i < n - 1; i++){
        int minIndex = i;
        for (int j = i + 1; j < n; j++){
            (*Cf)++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[i]; 
        arr[i] = arr[minIndex]; 
        arr[minIndex] = temp; 
        (*Mf)+=3;
    }
}
void BubbleSort(int* arr, int n, long* Cf, long* Mf){
    *Cf = 0;
    *Mf = 0;
    for (int i = 0; i < n - 1; i++){
        for (int j = n-1; j > i; j--){
            (*Cf)++;
            if (arr[j] < arr[j-1]){
                int temp = arr[j]; 
                arr[j] = arr[j-1]; 
                arr[j-1] = temp; 
                (*Mf)+=3;
            }
        }
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
    InsertSort(arr, n, &Cf, &Mf);
    int summ_ub_after=summ_mass(arr,n);
    int series_ub = count_series(arr, n);

    // Случайный
    FillRand(arr, n);
    int summ_cr_before=summ_mass(arr,n);
    int series_sr_do = count_series(arr, n);
    InsertSort(arr, n, &Cf, &Mf);
    int summ_cr_after=summ_mass(arr,n);
    int series_cr = count_series(arr, n);
    
    // Возрастающий
    FillInc(arr, n);
    int summ_voz_before=summ_mass(arr,n);
    int series_voz_do = count_series(arr, n);
    InsertSort(arr, n, &Cf, &Mf);
    int summ_voz_after=summ_mass(arr,n);
    int series_voz = count_series(arr, n);

    free(arr);
    printf("Убывающий:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_ub_before,summ_ub_after,series_ub_do,series_ub);
    printf("Случайный:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_cr_before,summ_cr_after,series_sr_do,series_cr);
    printf("Возрастающий:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_voz_before,summ_voz_after,series_voz_do,series_voz);    

    printf("--------------------------------------------------------------\n");
    printf("|      |      M+C теоритич        |           Mф+Cф          |\n");
    printf("|   N  |  Убыв. |  Случ. | Возр.  |  Убыв. |  Случ. | Возр.  |\n");
    printf("|------------------------------------------------------------|\n");
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* arr = malloc(sizeof(int) * n);
        long Cf, Mf;
        long MC_ub, MC_sl, MC_voz;

        long C_theor_min = n - 1;
        long M_theor_min = 2*(n-1);   

        long C_theor_max = (n*(n - 1))/2;    
        long M_theor_max = ((n*n - n)/2)+2*n-2;

        long C_theor_sl = C_theor_max/2;    
        long M_theor_sl =M_theor_max/2;      

        long MC_theor_min = C_theor_min + M_theor_min;
        long MC_theor_max = C_theor_max + M_theor_max;
        long MC_theor_sl = C_theor_sl + M_theor_sl;

        // Убывающий
        FillDec(arr, n);
        InsertSort(arr, n, &Cf, &Mf);
        MC_ub = Cf + Mf;

        // Случайный
        FillRand(arr, n);
        InsertSort(arr, n, &Cf, &Mf);
        MC_sl = Cf + Mf;

        // Возрастающий
        FillInc(arr, n);
        InsertSort(arr, n, &Cf, &Mf);
        MC_voz = Cf + Mf;
    
        
        printf("| %4d | %6ld | %6ld | %6ld | %6ld | %6ld | %6ld |\n", 
               n,MC_theor_max,MC_theor_sl,MC_theor_min, MC_ub, MC_sl, MC_voz);
        printf("|------------------------------------------------------------|\n");
        free(arr);
    }
    printf("-------------------------------------------\n");
    printf("|      |                 Mф+Cф             |\n");
    printf("|   N  | Select |  Bubble | Shaker | Insert|\n");
    printf("|------------------------------------------|\n");
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        int* arr = malloc(sizeof(int) * n);
        int* work = malloc(sizeof(int) * n);
        FillRand(arr, n);

        long Cf, Mf;
        long MC_sl_I, MC_sl_B, MC_sl_Sh,MC_sl_sl;
        
        for(int i=0; i<n; i++) work[i] = arr[i];
        InsertSort(work, n, &Cf, &Mf);
        MC_sl_I = Cf + Mf;

        for(int i=0; i<n; i++) work[i] = arr[i];
        BubbleSort(work, n, &Cf, &Mf);
        MC_sl_B = Cf + Mf;

        for(int i=0; i<n; i++) work[i] = arr[i];
        ShakerSort(work, n, &Cf, &Mf);
        MC_sl_Sh = Cf + Mf;

        for(int i=0; i<n; i++) work[i] = arr[i];
        SelectSort(work, n, &Cf, &Mf);
        MC_sl_sl = Cf + Mf;

        printf("| %4d | %6ld | %6ld | %6ld | %6ld |\n", 
               n,MC_sl_sl,MC_sl_B,MC_sl_Sh,MC_sl_I);
        printf("|------------------------------------------|\n");
        
        free(arr);
        free(work);
    }
    return 0;
}

