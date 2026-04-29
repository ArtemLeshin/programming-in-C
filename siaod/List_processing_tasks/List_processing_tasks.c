#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

typedef struct tLE {
    struct tLE *Next; 
    int Data;
} tLE, *pLE;

typedef struct {
    pLE Head;
    pLE *Tail; 
} Queue;

void Push(pLE *Head, int value) {
    pLE p = (pLE)malloc(sizeof(tLE));
    p->Data = value;
    p->Next = *Head;
    *Head = p;
}

void FillStackAsc(pLE *Head, int n) {
    for (int i = n; i >= 1; i--) Push(Head, i);
}

void FillStackDesc(pLE *Head, int n) {
    for (int i = 1; i <= n; i++) Push(Head, i);
}

void FillStackRand(pLE *Head, int n) {
    for (int i = 0; i < n; i++) Push(Head, rand() % 100);
}

void InitQueue(Queue *Q) {
    Q->Head = NULL;
    Q->Tail = &(Q->Head);
}

void Enqueue(Queue *Q, int value) {
    pLE p = (pLE)malloc(sizeof(tLE));
    p->Data = value;
    p->Next = NULL;
    *(Q->Tail) = p;
    Q->Tail = &(p->Next);
}

void FillQueueAsc(Queue *Q, int n) {
    for (int i = 1; i <= n; i++) Enqueue(Q, i);
}

void FillQueueDesc(Queue *Q, int n) {
    for (int i = n; i >= 1; i--) Enqueue(Q, i);
}

void FillQueueRand(Queue *Q, int n) {
    for (int i = 0; i < n; i++) Enqueue(Q, rand() % 100);
}

void PrintList(pLE Head) {
    pLE p = Head;
    while (p != NULL) {
        printf("%d ", p->Data);
        p = p->Next;
    }
    printf("\n");
}

int Checksum(pLE Head) {
    int sum = 0;
    for (pLE p = Head; p != NULL; p = p->Next) sum += p->Data;
    return sum;
}

int CountSeries(pLE Head) {
    if (Head == NULL) return 0;
    int series = 1;
    for (pLE p = Head; p->Next != NULL; p = p->Next) {
        if (p->Data > p->Next->Data) series++;
    }
    return series;
}

int RecursiveCountSeriesReverse(pLE p, int *count) {
    if (p->Next == NULL) {
        *count = 1;
        return p->Data;
    }
    int next_val = RecursiveCountSeriesReverse(p->Next, count);
    if (next_val > p->Data) (*count)++;
    return p->Data;
}

void DeleteList(pLE *Head) {
    while (*Head != NULL) {
        pLE p = *Head;
        *Head = (*Head)->Next;
        free(p);
    }
}

void RecursivePrintDirect(pLE p) {
    if (p != NULL) {
        printf("%d ", p->Data);
        RecursivePrintDirect(p->Next);
    }
}

void RecursivePrintReverse(pLE p) {
    if (p != NULL) {
        RecursivePrintReverse(p->Next);
        printf("%d ", p->Data);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    
    pLE MyStack = NULL;
    Queue MyQueue;

    printf(" РАБОТА СО СТЕКОМ\n");
    printf("1. Убывающий:   "); FillStackDesc(&MyStack, 10);
    PrintList(MyStack);
    printf("   Сумма: %d, Серий: %d\n", Checksum(MyStack), CountSeries(MyStack));
    DeleteList(&MyStack);

    printf("2. Возрастающий: "); FillStackAsc(&MyStack, 10);
    PrintList(MyStack);
    printf("   Сумма: %d, Серий: %d\n", Checksum(MyStack), CountSeries(MyStack));
    DeleteList(&MyStack);

    printf("3. Случайный:    "); FillStackRand(&MyStack, 10);
    PrintList(MyStack);
    printf("   Сумма: %d, Серий: %d\n", Checksum(MyStack), CountSeries(MyStack));
    
    printf("4. Рекурсивная печать (случайный):\n");
    printf("   Прямая:   "); RecursivePrintDirect(MyStack);
    printf("\n   Сумма: %d, Серий: %d", Checksum(MyStack), CountSeries(MyStack));
    printf("\n   Обратная: "); RecursivePrintReverse(MyStack);
    int rev_ser_s = 0;
    if (MyStack) RecursiveCountSeriesReverse(MyStack, &rev_ser_s);
    printf("\n   Сумма: %d, Серий: %d\n\n", Checksum(MyStack), rev_ser_s);

    printf(" РАБОТА С ОЧЕРЕДЬЮ \n");
    InitQueue(&MyQueue);
    printf("1. Убывающая:    "); FillQueueDesc(&MyQueue, 10);
    PrintList(MyQueue.Head);
    printf("   Сумма: %d, Серий: %d\n", Checksum(MyQueue.Head), CountSeries(MyQueue.Head));
    DeleteList(&(MyQueue.Head));

    InitQueue(&MyQueue);
    printf("2. Возрастающая: "); FillQueueAsc(&MyQueue, 10);
    PrintList(MyQueue.Head);
    printf("   Сумма: %d, Серий: %d\n", Checksum(MyQueue.Head), CountSeries(MyQueue.Head));
    DeleteList(&(MyQueue.Head));

    InitQueue(&MyQueue);
    printf("3. Случайная:    "); FillQueueRand(&MyQueue, 10);
    PrintList(MyQueue.Head);
    printf("   Сумма: %d, Серий: %d\n", Checksum(MyQueue.Head), CountSeries(MyQueue.Head));

    printf("4. Рекурсивная печать (случайная):\n");
    printf("   Прямая:   "); RecursivePrintDirect(MyQueue.Head);
    printf("\n   Сумма: %d, Серий: %d", Checksum(MyQueue.Head), CountSeries(MyQueue.Head));
    printf("\n   Обратная: "); RecursivePrintReverse(MyQueue.Head);
    int rev_ser_q = 0;
    if (MyQueue.Head) RecursiveCountSeriesReverse(MyQueue.Head, &rev_ser_q);
    printf("\n   Сумма: %d, Серий: %d\n\n", Checksum(MyQueue.Head), rev_ser_q);

    DeleteList(&MyStack);
    DeleteList(&(MyQueue.Head));
        
    return 0;
}
