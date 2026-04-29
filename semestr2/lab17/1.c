#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // для функции sleep, если захотите замедлить вывод

// Функция, которую будет выполнять дочерний поток
void* thread_func(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Дочерний поток: строка %d\n", i);
    }
    return NULL;
}

int main() {
    pthread_t thread; // Идентификатор потока

    // Создаем поток с атрибутами по умолчанию (NULL)
    if (pthread_create(&thread, NULL, thread_func, NULL) != 0) {
        perror("Ошибка при создании потока");
        return 1;
    }

    // Родительский поток выполняет свой цикл
    for (int i = 1; i <= 5; i++) {
        printf("Родительский поток: строка %d\n", i);
    }

    // Ожидаем завершения дочернего потока, чтобы программа не закрылась раньше времени
    pthread_join(thread, NULL);

    return 0;
}
