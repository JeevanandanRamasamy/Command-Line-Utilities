#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void print(DIR* dir, char* path, int pathSize, char* indent, int indentSize) {
    struct dirent* dp;
    char** list = (char**) malloc(100 * sizeof(char*));
    int c = 0;
    while ((dp = readdir(dir))) {
        if (strncmp(dp->d_name, ".", 1)) {
            list[c] = dp->d_name;
            ++c;
        }
    }
    list = (char**) realloc(list, c * sizeof(char*));
    for (int i = 1; i < c; ++i) {
        char key[100];
        strcpy(key, list[i]);
        int j = i - 1;
        while (j >= 0 && strcasecmp(list[j], key) > 0) {
            strcpy(list[j + 1], list[j]);
            j = j - 1;
        }
        strcpy(list[j + 1], key);
    }
    for (int i = 0; i < c; ++i) {
        struct stat buffer;
        char* newPath = malloc((pathSize + 100)*sizeof(char));
        strcpy(newPath, path);
        strcat(newPath, "/");
        strcat(newPath, list[i]);
        printf("%s%s\n", indent, list[i]);
        if (!stat(newPath, &buffer) && S_ISDIR(buffer.st_mode)) {
            char* newIndent = malloc((indentSize + 2)*sizeof(char));
            strcpy(newIndent, "  ");
            strcat(newIndent, indent);
            print(opendir(newPath), newPath, pathSize + 100, newIndent, indentSize + 2);
            free(newIndent);
        }
        free(newPath);
    }
    free(list);
    closedir(dir);
}

int main(int argc, char** argv) {
    DIR* dir;
    if (!(dir = opendir("."))) {
        perror("Cannot open directory");
        exit(1);
    }
    printf(".\n");
    print(dir, ".", 2, "- ", 3);
    return EXIT_SUCCESS;
}