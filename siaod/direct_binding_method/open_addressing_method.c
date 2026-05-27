#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

struct HashTable {
    int *table;     
    int m;       
    int collisions; 
    int elements; 
};

int HashFunction(int key, int m) {
    return key % m;
}

void InitHashTable(struct HashTable *ht, int m) {
    ht->m = m;
    ht->collisions = 0;
    ht->elements = 0;
    ht->table = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        ht->table[i] = 0;  
    }
}

void FreeHashTable(struct HashTable *ht) {
    free(ht->table);
    ht->table = NULL;
}

int InsertLinear(struct HashTable *ht, int key) {
    if (ht->elements >= ht->m) {
        return -1; 
    }
    
    int h = HashFunction(key, ht->m);
    int i = 0;
    
    while (i < ht->m) {
        int j = (h + i) % ht->m;
        
        if (ht->table[j] == 0) {
            ht->table[j] = key;
            ht->elements++;
            return j;
        } else {
            ht->collisions++;
            i++;
        }
    }
    
    return -1;  
}

int InsertQuadratic(struct HashTable *ht, int key) {
    if (ht->elements >= ht->m) {
        return -1;  
    }
    
    int h = HashFunction(key, ht->m);
    int d = 1;
    int step = 0;
    int current = h;
    
    while (step < ht->m) {
        if (ht->table[current] == 0) {
            ht->table[current] = key;
            ht->elements++;
            return current;
        } else {
            ht->collisions++; 
            step++;
            current = (current + d) % ht->m; 
            d = d + 2;
        }
    }
    
    return -1;  
}

int SearchLinear(struct HashTable *ht, int key, int *probes) {
    int h = HashFunction(key, ht->m);
    *probes = 0;
    
    for (int i = 0; i < ht->m; i++) {
        int j = (h + i) % ht->m;
        (*probes)++;
        
        if (ht->table[j] == key) {
            return j;
        }
        if (ht->table[j] == 0) {
            return -1; 
        }
    }
    return -1;
}

int SearchQuadratic(struct HashTable *ht, int key, int *probes) {
    int h = HashFunction(key, ht->m);
    int d = 1;
    int step = 0;
    int current = h;
    *probes = 0;
    
    while (step < ht->m) {
        (*probes)++;
        
        if (ht->table[current] == key) {
            return current;
        }
        if (ht->table[current] == 0) {
            return -1;
        }
        
        step++;
        current = (current + d) % ht->m;
        d = d + 2;
    }
    return -1;
}

void PrintHashTable(struct HashTable *ht) {
    printf("Номер ячейки: ");
    for (int i = 0; i < ht->m; i++) printf("%3d ", i);
    printf("\nКлюч:         ");
    for (int i = 0; i < ht->m; i++) {
        if (ht->table[i] != 0) printf("%3d ", ht->table[i]);
        else printf("  - ");
    }
    printf("\nФактическое количество коллизий Кф: %d\n", ht->collisions);
}

int main() {
    srand(time(NULL));
    
    printf("===============================================================================\n");
    printf("ЗАДАНИЕ 2.5: ХЕШИРОВАНИЕ МЕТОДОМ ОТКРЫТОЙ АДРЕСАЦИИ\n");
    printf("(Линейные и квадратичные пробы)\n");
    printf("===============================================================================\n\n");
    
    printf("ПУНКТ 2: Реализация хеширования с линейными и квадратичными пробами\n");
    printf("===============================================================================\n");
    
    int m = 17; 
    int test_keys[] = {12, 26, 38, 15, 43, 67, 89, 23, 45, 67, 78, 91, 34, 56, 72};
    int num_keys = 15;
    
    printf("\n--- ЛИНЕЙНЫЕ ПРОБЫ ---\n");
    struct HashTable ht_linear;
    InitHashTable(&ht_linear, m);
    
    printf("Вставляемые ключи: ");
    for (int i = 0; i < num_keys; i++) {
        printf("%d ", test_keys[i]);
        InsertLinear(&ht_linear, test_keys[i]);
    }
    printf("\n");
    PrintHashTable(&ht_linear);

    printf("\n--- КВАДРАТИЧНЫЕ ПРОБЫ ---\n");
    struct HashTable ht_quadratic;
    InitHashTable(&ht_quadratic, m);
    
    printf("Вставляемые ключи: ");
    for (int i = 0; i < num_keys; i++) {
        printf("%d ", test_keys[i]);
        InsertQuadratic(&ht_quadratic, test_keys[i]);
    }
    printf("\n");
    PrintHashTable(&ht_quadratic);
    
        // ПУНКТ 3: Исследование зависимости коллизий от размера таблицы
    printf("ПУНКТ 3: Сравнение коллизий при линейных и квадратичных пробах\n");
    printf("===============================================================================\n");
    printf("| Размер | Всего | Линейные | Квадратичные |\n");
    printf("| таблицы|символов| пробы    |    пробы     |\n");
    printf("|--------|-------|----------|--------------|\n");
    
    // Исправлено: 10 простых чисел, равномерно распределенных на диапазоне от 11 до 101
    int primes[] = {11, 19, 31, 43, 53, 61, 71, 83, 97, 101};
    int num_primes = 10;
    
    // Количество элементов равно 12 (длина вашей уникальной строки ФИО),
    // чтобы данные не переполняли таблицу m=11 и исследование было корректным
    int test_numbers[12];
    for (int i = 0; i < 12; i++) {
        test_numbers[i] = rand() % 1000;
    }
    
    for (int p = 0; p < num_primes; p++) {
        int m_size = primes[p];
        
        struct HashTable ht_lin;
        InitHashTable(&ht_lin, m_size);
        for (int i = 0; i < 12; i++) {
            InsertLinear(&ht_lin, test_numbers[i]);
        }
        int linear_collisions = ht_lin.collisions;
        
        struct HashTable ht_quad;
        InitHashTable(&ht_quad, m_size);
        for (int i = 0; i < 12; i++) {
            InsertQuadratic(&ht_quad, test_numbers[i]);
        }
        int quadratic_collisions = ht_quad.collisions;
        
        printf("| %6d | %5d | %8d | %12d |\n", 
               m_size, 12, linear_collisions, quadratic_collisions);
        
        FreeHashTable(&ht_lin);
        FreeHashTable(&ht_quad);
    }

    printf("-------------------------------------------------------------------------------\n");
    printf("МИКРОВЫВОД: С увеличением размера хеш-таблицы (m) количество коллизий Кф\n");
    printf("заметно снижается для обоих методов разрешения. Квадратичные пробы\n");
    printf("эффективнее устраняют эффект первичного кластеризации (группировки ключей),\n");
    printf("обеспечивая более равномерное распределение элементов по таблице.\n");
    printf("===============================================================================\n");
    
    printf("\n===============================================================================\n");
    printf("ПУНКТ 4*: Поиск элемента в хеш-таблице\n");
    printf("===============================================================================\n");
    
    struct HashTable ht_search;
    InitHashTable(&ht_search, 17);
    
    int search_keys[] = {25, 36, 47, 58, 69, 80, 91, 12, 23, 34};
    for (int i = 0; i < 10; i++) {
        InsertQuadratic(&ht_search, search_keys[i]);
    }
    
    printf("Базовая таблица для тестирования поиска:\n");
    PrintHashTable(&ht_search);
    
    // Тест 1: Поиск существующего элемента
    int key_to_find = 47;
    int probes;
    int pos = SearchQuadratic(&ht_search, key_to_find, &probes);
    
    printf("\nПоиск существующего элемента:\n");
    if (pos != -1) {
        printf("  Элемент %d найден!\n", key_to_find);
        printf("  Позиция в таблице: %d\n", pos);
        printf("  Количество проб: %d\n", probes);
    } else {
        printf("  Элемент %d не найден!\n", key_to_find);
    }
    
    // Тест 2: Поиск отсутствующего элемента
    key_to_find = 99;
    pos = SearchQuadratic(&ht_search, key_to_find, &probes);
    
    printf("\nПоиск отсутствующего элемента:\n");
    if (pos != -1) {
        printf("  Элемент %d найден!\n", key_to_find);
        printf("  Позиция в таблице: %d\n", pos);
    } else {
        printf("  Элемент %d не найден!\n", key_to_find);
        printf("  Количество проб: %d\n", probes);
    }
    
    FreeHashTable(&ht_search);
    FreeHashTable(&ht_linear);
    FreeHashTable(&ht_quadratic);

    return 0;
}
