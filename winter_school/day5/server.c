#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIFO "fifo.1"
#define MAXBUFF 80

int main(void) {
    int fd, n;
    char buff[MAXBUFF] = {0};
    mknod(FIFO, S_IFIFO | 0666, 0);
    if ((fd = open(FIFO, O_RDWR)) < 0) {
        perror("Невозможно открыть FIFO");
        exit(1);
    }
    n = read(fd, buff, MAXBUFF);
    if (n > 0) {
        printf("Клиент прислал: %s\n", buff);
        write(fd, "Сообщение получено!", 38);
    }
    close(fd); 
    unlink(FIFO);
    return 0;
}
