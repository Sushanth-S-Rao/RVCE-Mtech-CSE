#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *read_file(void *arg) {
    char *filename = (char *)arg;
    FILE *file = fopen(filename, "r");
    char buffer[100];

    fgets(buffer, sizeof(buffer), file);
    printf("~~ Thread Reading: %s", buffer);

    fclose(file);
    pthread_exit(NULL);
}

void *write_file(void *arg) {
    char *filename = (char *)arg;
    FILE *file = fopen(filename, "a");
    char buffer[100];
    
    printf("Enter text to write: ");
    fgets(buffer, sizeof(buffer), stdin);
    fprintf(file, "Thread Writing: %s", buffer);
    
    fclose(file);
    pthread_exit(NULL);
}

int main() {
	int i;
    pthread_t p, q, t;
    char *read_filename = "input.txt";
    char *write_filename = "output.txt";

    pthread_create(&p, NULL, read_file, (void *)read_filename);
    pthread_create(&q, NULL, write_file, (void *)write_filename);
    pthread_create(&t, NULL, write_file, (void *)write_filename);

    pthread_join(p, NULL);
    pthread_join(q, NULL);
    pthread_join(t, NULL);

    return 0;
}

