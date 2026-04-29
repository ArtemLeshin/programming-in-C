#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}

void FillDec(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
}

void FillRand(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;
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
void SelectSortImproved(int* arr, int n, long* Cf, long* Mf){
    *Cf = 0;
    *Mf = 0;
    for (int i = 0; i < n - 1; i++){
        int minIndex = i;
        for (int j = i + 1; j < n; j++){
            (*Cf)++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (minIndex != i){
            int temp = arr[i]; 
            (*Mf)++;
            arr[i] = arr[minIndex]; 
            (*Mf)++;
            arr[minIndex] = temp; 
            (*Mf)++;
        }
    }
}

int main()
{
    srand(time(NULL));
    int sizes[] = {10, 100};
    printf("---------------------------------------------------------------------------\n");
    printf("| size | M+C теоретич. | Исходный Mфакт + Cфакт | Улучшенный Mфакт + Cфакт |\n");
    printf("---------------------------------------------------------------------------\n");
    printf("|      |               | Убыв. | Случ. | Возр.  | Убыв. | Случ. | Возр.    |\n");
    printf("---------------------------------------------------------------------------\n");
    
    for (int idx = 0; idx < 2; idx++)
    {
        int n = sizes[idx];
        int* arr = malloc(sizeof(int) * n);
        long Cf, Mf;
        long Cf_imp, Mf_imp;
        
        long C_theor = n * (n - 1) / 2;
        long M_theor_min = 0;             
        long M_theor_max = 3 * (n - 1);     
        long MC_theor = C_theor + M_theor_max;
        
        long MC_ub_orig, MC_sl_orig, MC_voz_orig;
        long MC_ub_imp, MC_sl_imp, MC_voz_imp;
        
        
        // Убывающий
        FillDec(arr, n);
        SelectSort(arr, n, &Cf, &Mf);
        MC_ub_orig = Cf + Mf;
        
        FillDec(arr, n);
        SelectSortImproved(arr, n, &Cf_imp, &Mf_imp);
        MC_ub_imp = Cf_imp + Mf_imp;
        
        // Случайный
        FillRand(arr, n);
        SelectSort(arr, n, &Cf, &Mf);
        MC_sl_orig = Cf + Mf;
        
        FillRand(arr, n);
        SelectSortImproved(arr, n, &Cf_imp, &Mf_imp);
        MC_sl_imp = Cf_imp + Mf_imp;
        
        // Возрастающий
        FillInc(arr, n);
        SelectSort(arr, n, &Cf, &Mf);
        MC_voz_orig = Cf + Mf;
        
        FillInc(arr, n);
        SelectSortImproved(arr, n, &Cf_imp, &Mf_imp);
        MC_voz_imp = Cf_imp + Mf_imp;
        
        printf("| %4d | %13ld | %5ld | %5ld | %5ld | %5ld | %5ld | %5ld    |\n", 
               n, MC_theor, 
               MC_ub_orig, MC_sl_orig, MC_voz_orig,
               MC_ub_imp, MC_sl_imp, MC_voz_imp);
        printf("---------------------------------------------------------------------------\n");
        free(arr);
    }

    return 0;
}