#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Структура элемента списка
struct tLE {
    struct tLE *next;
    int data;
};

// Структура хеш-таблицы (массив списков)
struct HashTable {
    struct tLE **buckets; 
    int m;                
    int total_elements;   
};

// Добавление элемента в начало списка
void Push(struct tLE **head, int value) {
    struct tLE *p = (struct tLE*)malloc(sizeof(struct tLE));
    p->data = value;
    p->next = *head;
    *head = p;
}

// Добавление элемента в конец списка
void Append(struct tLE **head, int value) {
    struct tLE *p = (struct tLE*)malloc(sizeof(struct tLE));
    p->data = value;
    p->next = NULL;
    
    if (*head == NULL) {
        *head = p;
        return;
    }
    
    struct tLE *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = p;
}

void PrintList(struct tLE *head) {
    struct tLE *p = head;
    if (p == NULL) {
        printf("NULL");
        return;
    }
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL");
}

void DeleteList(struct tLE *head) {
    struct tLE *p = head;
    while (p != NULL) {
        struct tLE *next = p->next;
        free(p);
        p = next;
    }
}

int HashFunction(int key, int m) {
    return key % m;
}

// Подсчет фактического количества коллизий:
int CountCollisions(struct HashTable *ht) {
    int occupied_buckets = 0;
    for (int i = 0; i < ht->m; i++) {
        if (ht->buckets[i] != NULL) {
            occupied_buckets++;
        }
    }
    return ht->total_elements - occupied_buckets;
}

void InitHashTable(struct HashTable *ht, int m) {
    ht->m = m;
    ht->total_elements = 0;
    ht->buckets = (struct tLE**)malloc(m * sizeof(struct tLE*));
    for (int i = 0; i < m; i++) {
        ht->buckets[i] = NULL;
    }
}

void FreeHashTable(struct HashTable *ht) {
    for (int i = 0; i < ht->m; i++) {
        DeleteList(ht->buckets[i]);
    }
    free(ht->buckets);
    ht->buckets = NULL;
}

void Insert(struct HashTable *ht, int key) {
    int index = HashFunction(key, ht->m);
    Append(&ht->buckets[index], key);
    ht->total_elements++;
}

int Search(struct HashTable *ht, int key, int *pos) {
    int index = HashFunction(key, ht->m);
    struct tLE *p = ht->buckets[index];
    *pos = 0;
    
    while (p != NULL) {
        if (p->data == key) {
            return index;  
        }
        p = p->next;
        (*pos)++;
    }
    return -1;  
}

void PrintHashTable(struct HashTable *ht) {
    printf("\nХеш-таблица (размер m = %d):\n", ht->m);
    printf("============================================================\n");
    for (int i = 0; i < ht->m; i++) {
        printf("Список %2d: ", i);
        PrintList(ht->buckets[i]);
        printf("\n");
    }
    printf("============================================================\n");
    printf("Фактическое количество коллизий Кф: %d\n", CountCollisions(ht));
    printf("Всего элементов: %d\n", ht->total_elements);
}


int main() {
    srand(time(NULL));
    
    printf("===============================================================================\n");
    printf("ЗАДАНИЕ 2.4: ХЕШИРОВАНИЕ МЕТОДОМ ПРЯМОГО СВЯЗЫВАНИЯ\n");
    printf("===============================================================================\n\n");
    
    // ПУНКТ 2: Построение базовой хеш-таблицы
    int m_opt = 5;
    printf("ПУНКТ 2: Построение базовой таблицы для m = %d\n", m_opt);
    printf("===============================================================================\n");
    struct HashTable main_ht;
    InitHashTable(&main_ht, m_opt);
    
    // Фиксируем исходный набор из 12 тестовых чисел (имитация 12 символов ФИО)
    int base_numbers[12];
    for (int i = 0; i < 12; i++) {
        base_numbers[i] = rand() % 100;
        Insert(&main_ht, base_numbers[i]);
    }
    PrintHashTable(&main_ht);
    printf("===============================================================================\n\n");
    
    // ПУНКТ 3: Исследование зависимости коллизий от размера таблицы
    printf("ПУНКТ 3: Исследование зависимости коллизий от размера таблицы\n");
    printf("===============================================================================\n");
    printf("| Размер | Всего | Коллизий |\n");
    printf("| таблицы|символов|          |\n");
    printf("|--------|-------|----------|\n");
    
    // 10 простых чисел, равномерно распределенных на диапазоне от 11 до 101
    int primes[] = {11, 19, 31, 43, 53, 61, 71, 83, 97, 101};
    int num_primes = 10;
    
    int test_numbers[50];
    for (int i = 0; i < 50; i++) {
        test_numbers[i] = rand() % 1000;
    }
    
    for (int p = 0; p < num_primes; p++) {
        int m = primes[p];
        struct HashTable test_ht;
        InitHashTable(&test_ht, m);
        
        for (int i = 0; i < 50; i++) {
            Insert(&test_ht, test_numbers[i]);
        }
        
        printf("| %6d | %5d | %8d |\n", 
               m, test_ht.total_elements, CountCollisions(&test_ht));
        
        FreeHashTable(&test_ht);
    }
    printf("---------------------------------------------\n");
    printf("С увеличением размера");
    printf("хеш-таблицы (m) количество фактических коллизий (Кф) стремится к нулю.\n");
    printf("===============================================================================\n");
    
    // ПУНКТ 4*: Поиск элементов в хеш-таблице
    printf("\n===============================================================================\n");
    printf("ПУНКТ 4*: Поиск элементов в хеш-таблице\n");
    printf("===============================================================================\n");
    
    // Тест 1: Поиск гарантированно существующего элемента (берем первый из вставленных)
    int search_key1 = base_numbers[0];
    int pos1;
    int bucket1 = Search(&main_ht, search_key1, &pos1);
    
    printf("Поиск существующего элемента:\n");
    if (bucket1 != -1) {
        printf("  Элемент %d успешно найден!\n", search_key1);
        printf("  Номер списка (bucket): %d\n", bucket1);
        printf("  Позиция в списке: %d\n\n", pos1 + 1);
    } else {
        printf("  Элемент %d не найден!\n\n", search_key1);
    }
    
    // Тест 2: Поиск отсутствующего элемента
    int search_key2 = 999; // Число вне диапазона генерации базовых данных
    int pos2;
    int bucket2 = Search(&main_ht, search_key2, &pos2);
    
    printf("Поиск отсутствующего элемента:\n");
    if (bucket2 != -1) {
        printf("  Элемент %d успешно найден!\n", search_key2);
        printf("  Номер списка (bucket): %d\n", bucket2);
        printf("  Позиция в списке: %d\n", pos2 + 1);
    } else {
        printf("  Элемент %d не найден в хеш-таблице.\n", search_key2);
    }
    
    FreeHashTable(&main_ht);
    
    return 0;
}