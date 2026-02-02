#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

int main(int argc, char **argv) {
    int c;
    while ((c = getopt(argc, argv, "pesh")) != -1) {
        switch (c) {
            case 'p':
                printf("PPID: %d\n", getppid());
                printf("PID:  %d\n", getpid());
                printf("UID:  %d\n", getuid());
                printf("EUID: %d\n", geteuid());
                printf("GID:  %d\n", getgid());
                printf("EGID: %d\n", getegid());
                break;
            case 'e':  
                for (int i = 0; i < 10; i++) {
                    printf("%s\n", environ[i]);
                }
                break;
            case 's':  
                if (optind + 1 < argc) {
                    int a = atoi(argv[optind]);
                    int b = atoi(argv[optind + 1]);
                    printf("Сумма: %d\n", a + b);
                    optind += 2; 
                } else {
                    printf("Нужно два числа после -s\n");
                }
                break;
            case 'h': 
                printf("Использование: %s [опции]\n", argv[0]);
                printf("  -p  Показать информацию о процессе\n");
                printf("  -e  Показать переменные окружения\n");
                printf("  -s  Посчитать сумму двух чисел\n");
                printf("  -h  Справка\n");
                break;  
            case '?': 
                printf("Неизвестная опция\n");
                break;
        }
    }
    return 0;
}