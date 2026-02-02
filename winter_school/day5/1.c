#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process(char s[]) {
    int src = 0;        
    int dst = 0;
    int found_a = 0;     
    int stop = 0;

    while (s[src] != '\0' && !stop) {
        if (!found_a) {
            if (s[src] == 'a') {
                found_a = 1;
                s[dst] = s[src];
                dst++;
            }
        } else {
            if (s[src] == 'k') {
                stop = 1;
            } else {
                s[dst] = s[src];
                dst++;
            }
        }
        src++;
    }
    if (!found_a) {
        s[0] = '\0';
    } else {
        s[dst] = '\0';
    }
}
int main() {
    char buf[100];
    FILE *f_in = fopen("1.txt", "r");
    if (!f_in) {
        perror("Ошибка открытия 1.txt");
        return 1;
    }
    if (fgets(buf, 100, f_in) == NULL) {
        buf[0] = '\0';
    }
    fclose(f_in);
    process(buf);
    FILE *f_out = fopen("2.txt", "w");
    if (f_out) {
        fprintf(f_out, "%s", buf);
        fclose(f_out);
    }
    return 0;
}