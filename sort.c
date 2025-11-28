//Файл, предназначен для сортировки целых чисел по возрастанию
#include <stdlib.h>
#include <stdio.h>

// Функция-компаратор для сортировки целых чисел по возрастанию
int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int main() {
    int numbers[] = {5, 2, 8, 1, 9};
    size_t numbers_size = sizeof(numbers) / sizeof(numbers[0]);

    qsort(numbers, numbers_size, sizeof(int), compare_ints);

    for (size_t i = 0; i < numbers_size; ++i) {
        printf("%d ", numbers[i]);
    }
    // Вывод: 1 2 5 8 9

    return 0;
}
