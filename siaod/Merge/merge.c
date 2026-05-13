#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct tLE {
    int Data;
    struct tLE *Next;
} tLE, *pLE;

typedef struct {
    pLE Head;
    pLE Tail;
} Queue;

int Cf = 0, Mf = 0;


void InitQueue(Queue *Q) {
    Q->Head = NULL;
    Q->Tail = NULL;
}

void MoveToQueue(pLE *List, Queue *Q) {
    if (*List == NULL) return;
    pLE temp = *List;
    *List = temp->Next;
    temp->Next = NULL;
    if (Q->Head == NULL) Q->Head = temp;
    else Q->Tail->Next = temp;
    Q->Tail = temp;
}

int GetListLength(pLE S) {
    int len = 0;
    while (S) { len++; S = S->Next; }
    return len;
}

int ControlSum(pLE S) {
    int sum = 0;
    while (S) { sum += S->Data; S = S->Next; }
    return sum;
}

int CountSeries(pLE S) {
    if (!S) return 0;
    int count = 1;
    while (S->Next) {
        if (S->Data > S->Next->Data) count++;
        S = S->Next;
    }
    return count;
}

void PrintList(pLE S, int limit) {
    int i = 0;
    while (S && i < limit) {
        printf("%d ", S->Data);
        S = S->Next; i++;
    }
    printf("\n");
}

// --- Алгоритмы ---
//расщепление
void Split(pLE S, pLE *a, pLE *b, int *n) {
    if (!S) { 
        *a = *b = NULL; 
        *n = 0; 
        return; 
    }
    *a = S; *b = S->Next; *n = 1;
    pLE k = *a, p = *b;
    while (p != NULL) {
        (*n)++;
        k->Next = p->Next;
        k = p;
        p = p->Next;
    }
    k->Next = NULL;
    Mf += *n; 
}
//сляние
void MergeSeries(pLE *a, int q, pLE *b, int r, Queue *C) {
    while (q != 0 && r != 0) {
        Cf++;
        if ((*a)->Data <= (*b)->Data){ 
            MoveToQueue(a, C); 
            q--; }
        else { 
            MoveToQueue(b, C); 
            r--; }
        Mf++;
    }
    while (q > 0){ 
        MoveToQueue(a, C);
        q--; 
        Mf++; 
    }
    while (r > 0){ 
        MoveToQueue(b, C); 
        r--; 
        Mf++; 
    }
}
//сортировка
pLE MergeSort(pLE S, int n) {
    int m, q, r, i, p = 1;
    pLE a, b;
    Queue c[2];
    Split(S, &a, &b, &m);
    while (p < n) {
        InitQueue(&c[0]);
        InitQueue(&c[1]);
        i = 0; m = n;
        while (m > 0) {
            if (m >= p) q = p; else q = m;
            m -= q;
            if (m >= p) r = p; else r = m;
            m -= r;
            MergeSeries(&a, q, &b, r, &c[i]);
            i = 1 - i;
        }
        a = c[0].Head; b = c[1].Head;
        p *= 2;
    }
    return c[0].Head;
}


int main() {
    srand(time(NULL));
    
    int n2 = 20;
    pLE S = NULL, tail = NULL;
    for(int i = 0; i < n2; i++) {
        pLE node = malloc(sizeof(tLE));
        node->Data = rand() % 100; node->Next = NULL;
        if(!S) S = node; else tail->Next = node;
        tail = node;
    }
    printf("Исходный список: "); PrintList(S, 20);
    printf("Длина: %d, Серий: %d, Контр.сумма: %d\n", GetListLength(S), CountSeries(S), ControlSum(S));

    pLE a, b; int count;
    Split(S, &a, &b, &count);
    printf("\nСписок A: "); PrintList(a, 10);
    printf("Длина A: %d, Серий: %d, Контр.сумма: %d\n", GetListLength(a), CountSeries(a), ControlSum(a));
    
    printf("\nСписок B: "); PrintList(b, 10);
    printf("Длина B: %d, Серий: %d, Контр.сумма: %d\n", GetListLength(b), CountSeries(b), ControlSum(b));

    // ТАБЛИЦА
    printf("N\tM+C теор.\tУбыв.\tСлуч.\tВозр.\n");
    printf("---------------------------------------------\n");
    
    int sizes[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) {
        int N = sizes[i];
        int teor = (int)(2 * N * (log2(N)/log2(2)) + N);
        printf("%d\t%d\t\t", N, teor);
        
        int modes[] = {2, 0, 1}; 
        for(int j = 0; j < 3; j++) {
            pLE list = NULL, t = NULL;
            for(int k = 0; k < N; k++) {
                pLE node = malloc(sizeof(tLE));
                if(modes[j] == 1) node->Data = k;
                else if(modes[j] == 2) node->Data = N - k;
                else node->Data = rand() % 1000;
                node->Next = NULL;
                if(!list) list = node; else t->Next = node;
                t = node;
            }
            Cf = 0; Mf = 0;
            list = MergeSort(list, N);
            printf("%d\t", Mf + Cf);
            
            while(list) { pLE tmp = list; list = list->Next; free(tmp); }
        }
        printf("\n");
    }
    
    return 0;
}
