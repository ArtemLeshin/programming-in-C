#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void FillInc(int* arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
}

int Binary_Search1(int* arr, int n, int X, long* Cf) {
    int L = 0;
    int R = n - 1;
    *Cf = 0;
    while (L <= R) {
        int m = (L + R) / 2;
        (*Cf)++;
        if (arr[m] == X) {
            return m;
        }
        (*Cf)++;
        if (arr[m] < X) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }
    return -1;
}

int Binary_Search2(int* arr, int n, int X, long* Cf) {
    int L = 0;
    int R = n - 1;
    *Cf = 0;
    while (L < R) {
        int m = (L + R) / 2;
        (*Cf)++; 
        if (arr[m] < X) {
            L = m + 1;
        } else {
            R = m;
        }
    }
    (*Cf)++;
    if (arr[R] == X) {
        return R;
    } else {
        return -1;
    }
}

void ShowResult(int* arr, int n, int X, const char* test_name) {
    long Cf1, Cf2;
    int pos = Binary_Search1(arr, n, X, &Cf1);
    Binary_Search2(arr, n, X, &Cf2);

    printf("%s\n", test_name);
    if (pos != -1) {
        printf("Найден элемент: %d, Позиция: %d\n", arr[pos], pos);
    } else {
        printf("Элемент не найден\n");
    }
}

int main() {
    srand(time(NULL));
    int n = 1000;
    int* arr = malloc(n * sizeof(int));
    FillInc(arr, n);

    printf("Проверка поиска для N=1000\n");
    ShowResult(arr, n, arr[0], "Поиск первого элемента:");
    ShowResult(arr, n, arr[n - 1], "Поиск последнего элемента:");
    ShowResult(arr, n, -5, "Поиск отсутвующего элемента:");

    int userX;
    printf("\nВведите ваш ключ для поиска: ");
    scanf("%d", &userX);
    ShowResult(arr, n, userX, "Поиск введенного ключа");

    printf("\n-----------------------------------------------------\n");
    printf("|   N  | C1 теор | C2 теор |Сф I версия|Сф II версия|\n");
    printf("|------|---------|---------|-----------|------------|\n");

    int sizes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    for (int i = 0; i < 10; i++) {
        int N = sizes[i];
        int* t_arr = malloc(N * sizeof(int));
        FillInc(t_arr, N);
        
        long Cf1, Cf2;
        int random_index = rand() % N; 
        int sl = t_arr[random_index];
        Binary_Search1(t_arr, N, sl, &Cf1);
        Binary_Search2(t_arr, N, sl, &Cf2);
        int teoric1=(int)(2*(log2(N)))+1;
        int teoric2=(int)(log2(N))+2;

        printf("| %4d | %7d | %7d | %9ld | %10ld |\n", N, teoric1,teoric2, Cf1, Cf2);
        printf("-----------------------------------------------------\n");

        free(t_arr);
    }
    printf("В первой версии количество сравнений в 1.5–2 раза выше, так как внутри цикла выполняются сразу две проверки\n");
    free(arr);
    return 0;
}
