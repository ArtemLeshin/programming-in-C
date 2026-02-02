#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO "fifo.1"
#define MAXBUFF 80
int main(void) {
    int fd;
    char buff[MAXBUFF] = {0}; 
    if ((fd = open(FIFO, O_RDWR)) < 0) {
        perror("Ошибка открытия FIFO");
        exit(1);
    }    
    write(fd, "Здравствуй, Мир!", 32);
    sleep(1); 
    int n = read(fd, buff, MAXBUFF);
    if (n > 0) {
        printf("Сервер ответил: %s\n", buff);
    }
    close(fd);
    return 0;
}
