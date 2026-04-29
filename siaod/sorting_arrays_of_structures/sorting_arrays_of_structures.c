#include <stdio.h>
#include <string.h>
#include <locale.h>

struct PhoneBook {
    char surname[30];
    char name[30];
    char phone[15];
    char city[20];
};


// По возрастанию
int cmpFullnameAsc(struct PhoneBook a, struct PhoneBook b) {
    int res = strcmp(a.surname, b.surname);
    if (res == 0) res = strcmp(a.name, b.name);
    return res; 
}

// По убыванию
int cmpFullnameDesc(struct PhoneBook a, struct PhoneBook b) {
    return -cmpFullnameAsc(a, b); 
}

// Ключ: Город | По возрастанию
int cmpCityAsc(struct PhoneBook a, struct PhoneBook b) {
    return strcmp(a.city, b.city);
}

//сортировка вставками
void InsertSort(struct PhoneBook* arr, int n, int (*compare)(struct PhoneBook, struct PhoneBook)) {
    for (int i = 1; i < n; i++) {
        struct PhoneBook t = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(t, arr[j]) < 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}

// двоичный поиск по фамилии
int binarySearchBySurname(struct PhoneBook* arr, int n, char* X) {
    int L = 0;
    int R = n - 1;
    while (L < R) {
        int m = (L + R) / 2;
        if (strcmp(arr[m].surname, X) < 0) {
            L = m + 1;
        } else {
            R = m;
        }
    }    
    if (strcmp(arr[R].surname, X) == 0) {
        return R;
    } else {
        return -1;
    }
}

void printTable(struct PhoneBook arr[], int n) {
    printf("\n-----------------------------------------------------\n");
    printf("фамилия\t|\tимя\t|\tтелефон\t|\tгород\n");
    printf("--------|---------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t|\t%s\t|\t%s|\t%s\n", 
               arr[i].surname, 
               arr[i].name, 
               arr[i].phone, 
               arr[i].city);
    }
    printf("------------------------------------------------------\n");
}

int main() {
    struct PhoneBook directory[] = {
        {"Лёшин", "Иван", "89001112233", "Москва"},
        {"Качар", "Кирилл", "89112223344", "Тула"},
        {"Лёшин", "Артём", "89223334455", "Омск"},
        {"Колесов", "Георгий", "89334445566", "Сочи"},
        {"Абрамов", "Олег", "89445556677", "Пермь"}
    };
    int n = 5;
    char searchTarget[30];

    printf("изначально:");
    printTable(directory, n);
    
    // 1. Сортировка по сложному ключу (Фамилия + Имя)
    InsertSort(directory, n, cmpFullnameAsc);
    printf("1. сортировка по фамилии и имени (возрастание):");
    printTable(directory, n);

    // 2. Изменение направления (Убывание)
    InsertSort(directory, n, cmpFullnameDesc);
    printf("2. сортировка по фамилии и имени (убывание):");
    printTable(directory, n);

    // 3. Изменение ключа (Сортировка по городу)
    InsertSort(directory, n, cmpCityAsc);
    printf("3.сортировка по городу:");
    printTable(directory, n);

    InsertSort(directory, n, cmpFullnameAsc);
    
    printf("двоичный поиск:");
    printf("\nВведите фамилию для поиска: ");
    scanf("%s", searchTarget);

    int foundIdx = binarySearchBySurname(directory, n, searchTarget);
    
    if (foundIdx != -1) {
        printf("Запись найдена в отсортированном списке (индекс %d):\n", foundIdx);
        printf("Результат: %s %s, тел: %s, г. %s\n", 
                directory[foundIdx].surname, directory[foundIdx].name, 
                directory[foundIdx].phone, directory[foundIdx].city);
    } else {
        printf("Запись с фамилией '%s' не найдена.\n", searchTarget);
    }

    return 0;
}
