//9. Write a C program that takes one or more file/directory names as command line input and reports following info,
// A) File Type    B) Number Of Links   C) Time of last Acces   D) Read,write and execute permission

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void printInformation(char *filename) {
    struct stat f;
    stat(filename, &f);
    
    // A) File Type
    if (S_ISREG(f.st_mode))         printf("File Type: Regular File \n");
    else if (S_ISDIR(f.st_mode))    printf("File Type: Directory \n");
    else if (S_ISBLK(f.st_mode))    printf("File Type: Symbolic Link \n");
    else                            printf("File Type: Other \n");

    // B) Number Of Links
    printf("Number Of Links: %ld\n", (long)f.st_nlink);

    // C) Time of Last Access
    struct tm *access_time = localtime(&f.st_atime);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", access_time);
    printf("Time of Last Access: %s\n", buf);

    // D) Permissions
    printf("Permissions (Owner/Group/Others): ");
    printf((f.st_mode & S_IRUSR) ? "r" : "-");
    printf((f.st_mode & S_IWUSR) ? "w" : "-");
    printf((f.st_mode & S_IXUSR) ? "x" : "-");
    printf("/");
    printf((f.st_mode & S_IRGRP) ? "r" : "-");
    printf((f.st_mode & S_IWGRP) ? "w" : "-");
    printf((f.st_mode & S_IXGRP) ? "x" : "-");
    printf("/");
    printf((f.st_mode & S_IROTH) ? "r" : "-");
    printf((f.st_mode & S_IWOTH) ? "w" : "-");
    printf((f.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        printf("Information for: %s\n", argv[i]);
        printInformation(argv[i]);
        printf("\n");
    }

    return 0;
}