#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define WHITE       "\033[0m"
#define BLUE        "\033[34;1m"
#define GREEN       "\033[32;1m"
#define RED         "\033[31;1m"
#define MAX_SIZE    4096

void edit_file(char *filename);
void print_file_content(FILE *fptr);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "%sEnter the file to be opened as an argument.\n", RED);
        return 1;
    }
    char *filename = argv[1];

    printf("%sSelect the operation:\n", BLUE);
    printf("1. Edit the file\n");
    printf("2. Exit%s\n", WHITE);
    int ch = '1';
    while (1)
    {
        scanf("%c", &ch);
        if (ch != '1' && ch != '2')
        {
            if(ch != '\n')
            {
                fprintf(stderr, "%sInvalid choice. Try again.%s\n", RED, WHITE);
            }
        }
        else break;
    }
    
    if (ch == '1')
    {
        edit_file(filename);
    }
    else if (ch == '2')
    {
        exit(0);
    }

    return 0;
}

void edit_file(char *filename)
{
    FILE *fptr = fopen(filename, "a+");
    int fd = fileno(fptr);
    int res = flock(fd, LOCK_EX | LOCK_NB);
    if (res == -1)
    {
        if (errno == EWOULDBLOCK)
        {
            fprintf(stderr, "%sAdvisory lock warning: The file is already locked.%s\n", RED, WHITE);
        }
    }
    else
    {
        fprintf(stdout, "%sFile lock acquired successfully.%s\n", GREEN, WHITE);
    }

    fprintf(stdout, "%sContents of the file:\n%s", BLUE, WHITE);
    print_file_content(fptr);

    fprintf(stdout, "%s\nEnter text to append to file, below this line and press ctrl+D to save:%s\n", BLUE, WHITE);

    char buffer[MAX_SIZE];
    char newbuf[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, stdin))
    {
        strcat(newbuf, buffer);
    }

    int len = strlen(newbuf);
    if (newbuf[len - 1] == '\n') newbuf[len - 1] = '\0';

    fseek(fptr, 0, SEEK_END);
    fputs(newbuf, fptr);

    fprintf(stdout, "%sText written to file successfully.%s\n", GREEN, WHITE);
    fclose(fptr);
}

void print_file_content(FILE *fptr)
{
    char buffer[MAX_SIZE];
    while (fgets(buffer, MAX_SIZE, fptr))
    {
        fputs(buffer, stdout);
    }
}