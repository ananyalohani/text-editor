#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define WHITE  "\u001b[0m"
#define GREEN "\u001b[32;1m"
#define RED "\u001b[31;1m"
#define BLUE "\u001b[34;1m"


void edit_file(char *filename);

int main(int argc, char const *argv[])
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
        // printf("c1\n");
        if (ch != '1' && ch != '2')
        {
            fprintf(stderr, "%sInvalid choice. Try again.%s\n", RED, WHITE);
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
            fprintf(stderr, "%sAdvisory lock warning: The file is already locked.\n", RED);
        }
    }
    else
    {
        fprintf(stdout, "%sFile lock acquired successfully.%s\n", GREEN);
    }
    char buffer[4096];
    while (fgets(buffer, 4096, fptr))
    {
        fputs(buffer, stdout);
    }

    fprintf(stdout, "%sEnter text to append to file, below this line.%s\n", BLUE, WHITE);
    fflush(stdin);
    fgets(buffer, 4096, stdin);
    fseek(fptr, 0, SEEK_END);
    fputs(buffer, fptr);
    fclose(fptr);
}