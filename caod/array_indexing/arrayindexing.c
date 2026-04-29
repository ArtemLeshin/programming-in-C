#include <stdio.h>
#include <string.h>
#include <locale.h>

struct PhoneBook {
    char surname[30];
    char name[30];
    char phone[15];
    char city[20];
};

int sortMode = 0;   // 0 - по фамилии+имени, 1 - по городу

int less(struct PhoneBook* x, struct PhoneBook* y) {
    if (sortMode == 0) {
        int cmp = strcmp(x->surname, y->surname);
        if (cmp < 0) return 1;      // x раньше
        if (cmp > 0) return 0;      // x позже
        return strcmp(x->name, y->name) < 0;
    }
    else {
        int cmp = strcmp(x->city, y->city);
        if (cmp < 0) return 1;      // x раньше
        if (cmp > 0) return 0;      // x позже
        return strcmp(x->surname, y->surname) < 0;
    }
}


void InsertSort(struct PhoneBook** idx, int n, int (*compare)(struct PhoneBook*, struct PhoneBook*)) {
    for (int i = 1; i < n; i++) {
        struct PhoneBook* current = idx[i];
        int j = i - 1;
                while (j >= 0 && compare(current, idx[j])) {
            idx[j + 1] = idx[j];
            j--;
        }
        idx[j + 1] = current;  
    }
}

// двоичный поиск по фамилии 
int binarySearchBySurname(struct PhoneBook** idx, int n, char* target) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (strcmp(idx[mid]->surname, target) < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    if (strcmp(idx[right]->surname, target) == 0) {
        return right;
    }
    return -1;
}

// двоичный поиск по городу
int binarySearchByCity(struct PhoneBook** idx, int n, char* target) {
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (strcmp(idx[mid]->city, target) < 0) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    if (strcmp(idx[right]->city, target) == 0) {
        return right;
    }
    return -1;
}

// вывод таблицы
void printTable(struct PhoneBook** idx, int n, const char* title) {
    printf("\n-----------------------------------------------------\n");
    printf("%s\n", title);
    printf("фамилия\t|\tимя\t|\tтелефон\t|\tгород\n");
    printf("--------|---------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%s\t|\t%s\t|\t%s|\t%s\n", 
               idx[i]->surname, idx[i]->name, idx[i]->phone, idx[i]->city);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    
    // исходный массив структур (5 записей)
    struct PhoneBook directory[] = {
        {"лёшин", "иван", "89001112233", "москва"},
        {"качар", "кирилл", "89112223344", "тула"},
        {"лёшин", "артём", "89001112233", "омск"}, 
        {"колесов", "георгий", "89334445566", "сочи"},
        {"абрамов", "олег", "89445556677", "москва"}
    };
    
    int n = 5;
    char searchTarget[30];
    
    // ========== индексные массивы (массивы указателей) ==========
    struct PhoneBook* idxOriginal[5];   // для вывода исходного порядка
    struct PhoneBook* idxBySurname[5];  // для сортировки по фамилии
    struct PhoneBook* idxByCity[5];     // для сортировки по городу
    
    // инициализация: заполняем индексные массивы адресами элементов directory
    for (int i = 0; i < n; i++) {
        idxOriginal[i] = &directory[i];
        idxBySurname[i] = &directory[i];
        idxByCity[i] = &directory[i];
    }
    
    // вывод исходного справочника
    printTable(idxOriginal, n, "исходные данные:");
    
    // ===== 1. сортировка по фамилии + имени =====
    sortMode = 0;
    InsertSort(idxBySurname, n, less);
    printTable(idxBySurname, n, "1. фамилия и имя (возрастание):");
    
    // ===== 2. сортировка по городу =====
    sortMode = 1;
    InsertSort(idxByCity, n, less);
    printTable(idxByCity, n, "2. город:");
    
    // ===== 3. двоичный поиск по фамилии =====
    // заново инициализируем и сортируем по фамилии
    for (int i = 0; i < n; i++) {
        idxBySurname[i] = &directory[i];
    }
    sortMode = 0;
    InsertSort(idxBySurname, n, less);
    
    printf("\nдвоичный поиск:");
    printf("\nвведите фамилию: ");
    scanf("%29s", searchTarget);
    
    int pos = binarySearchBySurname(idxBySurname, n, searchTarget);
    
    if (pos != -1) {
        printf("результаты поиска:\n");
        
        // ищем начало диапазона (все с такой фамилией)
        int start = pos;
        while (start > 0 && strcmp(idxBySurname[start-1]->surname, searchTarget) == 0) {
            start--;
        }
        
        // ищем конец диапазона
        int end = pos;
        while (end < n-1 && strcmp(idxBySurname[end+1]->surname, searchTarget) == 0) {
            end++;
        }
        
        // выводим всех найденных
        for (int i = start; i <= end; i++) {
            printf("- %s %s, %s, %s\n", 
                   idxBySurname[i]->surname, idxBySurname[i]->name, 
                   idxBySurname[i]->phone, idxBySurname[i]->city);
        }
    } else {
        printf("записи с фамилией '%s' не найдены\n", searchTarget);
    }
    
    // ===== 4. двоичный поиск по городу =====
    // заново инициализируем и сортируем по городу
    for (int i = 0; i < n; i++) {
        idxByCity[i] = &directory[i];
    }
    sortMode = 1;
    InsertSort(idxByCity, n, less);
    
    printf("\nвведите город: ");
    scanf("%29s", searchTarget);
    
    pos = binarySearchByCity(idxByCity, n, searchTarget);
    
    if (pos != -1) {
        printf("результаты поиска:\n");
        
        int start = pos;
        while (start > 0 && strcmp(idxByCity[start-1]->city, searchTarget) == 0) {
            start--;
        }
        
        int end = pos;
        while (end < n-1 && strcmp(idxByCity[end+1]->city, searchTarget) == 0) {
            end++;
        }
        
        for (int i = start; i <= end; i++) {
            printf("- %s %s, %s, %s\n", 
                   idxByCity[i]->surname, idxByCity[i]->name, 
                   idxByCity[i]->phone, idxByCity[i]->city);
        }
    } else {
        printf("записи с городом '%s' не найдены\n", searchTarget);
    }
    
    return 0;
}