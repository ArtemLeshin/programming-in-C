#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

unsigned long long Mf = 0;

void reset_counters() {
    Mf = 0;
}

void FreeList(Node* head) {
    Node* p = head;
    while (p) {
        Node* t = p;
        p = p->next;
        free(t);
    }
}

void PrintList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int CheckSum(Node* head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

int RunNumber(Node* head) {
    if (!head) return 0;
    if (!head->next) return 1;
    int series = 1;
    while (head->next) {
        if (head->next->data < head->data) series++;
        head = head->next;
    }
    return series;
}

Node* CreateListFromArray(int arr[], int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        Node* p = (Node*)malloc(sizeof(Node));
        p->data = arr[i];
        p->next = NULL;
        if (!head) head = p;
        else tail->next = p;
        tail = p;
    }
    return head;
}

int getByte(int x, int j) {
    return (x >> (j * 8)) & 0xFF;
}

Node* DigitalSort(Node* S, int L, int order) {
    for (int pos = 0; pos < L; pos++) {
        Queue Q[256];
        for (int i = 0; i < 256; i++) {
            Q[i].head = NULL;
            Q[i].tail = NULL;
        }
        Node* p = S;
        while (p) {
            int b = getByte(p->data, pos);
            Node* next = p->next;
            p->next = NULL;
            if (!Q[b].head) Q[b].head = p;
            else Q[b].tail->next = p;
            Q[b].tail = p;
            Mf++;
            p = next;
        }
        Node* newHead = NULL;
        Node* newTail = NULL;
        if (order == 1) {
            for (int i = 0; i < 256; i++) {
                if (Q[i].head) {
                    if (!newHead) {
                        newHead = Q[i].head;
                        newTail = Q[i].tail;
                    } else {
                        newTail->next = Q[i].head;
                        newTail = Q[i].tail;
                    }
                }
            }
        } else {
            for (int i = 255; i >= 0; i--) {
                if (Q[i].head) {
                    if (!newHead) {
                        newHead = Q[i].head;
                        newTail = Q[i].tail;
                    } else {
                        newTail->next = Q[i].head;
                        newTail = Q[i].tail;
                    }
                }
            }
        }
        S = newHead;
    }
    return S;
}

void Task2() {
    printf("\n========== ЗАДАНИЕ 2 ==========\n");
    int arr[] = {13, 3, 8, 2, 3, 15, 12, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node* S = CreateListFromArray(arr, n);

    printf("Исходный список: ");
    PrintList(S);
    printf("Контрольная сумма: %d ", CheckSum(S));
    printf("Число серий: %d\n\n", RunNumber(S));

    reset_counters();
    S = DigitalSort(S, 2, 1);

    printf("Отсортированный список: ");
    PrintList(S);
    printf("Контрольная сумма: %d ", CheckSum(S));
    printf("Число серий: %d\n", RunNumber(S));
    FreeList(S);
}

void Task3() {
    printf("\n========== ЗАДАНИЕ 3 ==========\n");

    int arr2[] = {255, 128, 0, 512, 256, 64, 192, 1024, 65535, 32768};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    Node* s2 = CreateListFromArray(arr2, n2);
    printf("Двухбайтовые (исходный): ");
    PrintList(s2);

    reset_counters();
    s2 = DigitalSort(s2, 2, 1);
    printf("Двухбайтовые (по возрастанию): ");
    PrintList(s2);
    FreeList(s2);
    s2 = CreateListFromArray(arr2, n2);
    reset_counters();
    s2 = DigitalSort(s2, 2, -1);
    printf("Двухбайтовые (по убыванию): ");
    PrintList(s2);
    FreeList(s2);
    printf("\n");

    int arr4[] = {65535, 32768, 0, 131072, 65536, 16384, 49152, 262144, 1000000, 500000};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);

    Node* s4 = CreateListFromArray(arr4, n4);
    printf("Четырёхбайтовые (исходный): ");
    PrintList(s4);

    reset_counters();
    s4 = DigitalSort(s4, 4, 1);
    printf("Четырёхбайтовые (по возрастанию): ");
    PrintList(s4);
    FreeList(s4);

    s4 = CreateListFromArray(arr4, n4);
    reset_counters();
    s4 = DigitalSort(s4, 4, -1);
    printf("Четырёхбайтовые (по убыванию): ");
    PrintList(s4);
    FreeList(s4);
}


void Task4() {
    printf("\n========== ЗАДАНИЕ 4 (Сравнение L=2 и L=4) ==========\n");
    int sizes[] = {100, 200, 300, 400, 500};
    int levels[] = {2, 4};

    for (int k = 0; k < 2; k++) {
        int L = levels[k];
        printf("\nТАБЛИЦА ДЛЯ L = %d (байт)\n", L);
        printf("==================================================================\n");
        printf("  N   |  Теоретич.  |  Убывающий  |  Возрастающий  |  Случайный\n");
        printf("------------------------------------------------------------------\n");

        for (int i = 0; i < 5; i++) {
            int n = sizes[i];
            int teor = n * L;

            int *arr_inc = malloc(n * sizeof(int));
            int *arr_dec = malloc(n * sizeof(int));
            int *arr_rand = malloc(n * sizeof(int));

            for (int j = 0; j < n; j++) arr_inc[j] = j + 1;
            for (int j = 0; j < n; j++) arr_dec[j] = n - j;
            for (int j = 0; j < n; j++) arr_rand[j] = rand();

            Node* s_inc = CreateListFromArray(arr_inc, n);
            Node* s_dec = CreateListFromArray(arr_dec, n);
            Node* s_rand = CreateListFromArray(arr_rand, n);

            reset_counters();
            Node* r_inc = DigitalSort(s_inc, L, 1);
            unsigned long long m_inc = Mf;

            reset_counters();
            Node* r_dec = DigitalSort(s_dec, L, 1);
            unsigned long long m_dec = Mf;

            reset_counters();
            Node* r_rand = DigitalSort(s_rand, L, 1);
            unsigned long long m_rand = Mf;

            printf(" %3d   |    %5d    |    %5llu    |     %5llu     |    %5llu\n",
                   n, teor, m_dec, m_inc, m_rand);

            FreeList(r_inc);
            FreeList(r_dec);
            FreeList(r_rand);
            free(arr_inc);
            free(arr_dec);
            free(arr_rand);
        }
        printf("==================================================================\n");
    }
}

int main() {
    srand(time(NULL));
    Task2();
    Task3();
    Task4();
    printf("\nВЫВОД:\n");
    printf("1. Сравнение таблиц показывает, что при увеличении L в 2 раза, трудоемкость M растет пропорционально.\n");
    printf("2. DigitalSort подтверждает линейную сложность O(L*n) и независимость от типа входных данных.\n");
    return 0;
}