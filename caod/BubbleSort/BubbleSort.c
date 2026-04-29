#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
//возрастающ
void FillInc(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}
//убываюш
void FillDec(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}
//случайный
void FillRand(int* arr, int n)
{
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

int main()
{
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
    BubbleSort(arr, n, &Cf, &Mf);
    int summ_ub_after=summ_mass(arr,n);
    int series_ub = count_series(arr, n);

    // Случайный
    FillRand(arr, n);
    int summ_cr_before=summ_mass(arr,n);
    int series_sr_do = count_series(arr, n);
    BubbleSort(arr, n, &Cf, &Mf);
    int summ_cr_after=summ_mass(arr,n);
    int series_cr = count_series(arr, n);
    
    // Возрастающий
    FillInc(arr, n);
    int summ_voz_before=summ_mass(arr,n);
    int series_voz_do = count_series(arr, n);
    BubbleSort(arr, n, &Cf, &Mf);
    int summ_voz_after=summ_mass(arr,n);
    int series_voz = count_series(arr, n);

    free(arr);
    printf("Убывающий:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_ub_before,summ_ub_after,series_ub_do,series_ub);
    printf("Случайный:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_cr_before,summ_cr_after,series_sr_do,series_cr);
    printf("Возрастающий:\n Сумма до: %d; Сумма после: %d; кол-во серий до: %d; кол-во серий после: %d\n",summ_voz_before,summ_voz_after,series_voz_do,series_voz);    

    printf("--------------------------------------------------------------\n");
    printf("|      |       M+C теоретич.      |      Mфакт + Cфакт       |\n");
    printf("|   N  |  Убыв  |  Случ  |  Возр  |  Убыв  |  Случ. | Возр.  |\n");
    printf("|------------------------------------------------------------|\n");
    
    for (int idx = 0; idx < 5; idx++)
    {
        int n = sizes[idx];
        int* arr = malloc(sizeof(int) * n);
        long Cf, Mf;
        
        long C_theor = (n * n - n) / 2;
        long M_theor_min = 0;             
        long M_theor_max = 3 * ((n*n - n))/2;
        long M_theor_cred = (3 * ((n*n - n)))/4;     
        long MC_theor_max = C_theor + M_theor_max;
        long MC_theor_min = C_theor + M_theor_min;
        long MC_theor_cred = C_theor + M_theor_cred;
        
        
        long MC_ub, MC_sl, MC_voz; 
        // Убывающий
        FillDec(arr, n);
        BubbleSort(arr, n, &Cf, &Mf);

        MC_ub = Cf + Mf;
        
        // Случайный
        FillRand(arr, n);
        BubbleSort(arr, n, &Cf, &Mf);
        MC_sl = Cf + Mf;
        
        // Возрастающий
        FillInc(arr, n);
        BubbleSort(arr, n, &Cf, &Mf);
        MC_voz = Cf + Mf;
        
        
        printf("| %4d | %6ld | %6ld | %6ld | %6ld | %6ld | %6ld |\n", 
               n, MC_theor_max,MC_theor_cred,MC_theor_min,
               MC_ub, MC_sl, MC_voz);
        printf("|------------------------------------------------------------|\n");
        free(arr);
    }
    printf("\nBubbleSort зависит от исходной упорядоченности массива:\nдля убывающего массива число операций максимально\nдля возрастающего — 0\nдля случайного — промежуточное\n");

    return 0;
}

