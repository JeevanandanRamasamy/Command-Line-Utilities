#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void findFiles(DIR* dir, char* pattern, char* path) {
    struct dirent* dp;
    while ((dp = readdir(dir))) {
        if (strncmp(dp->d_name, ".", 1)) {
            struct stat buffer;
            char* newPath = malloc(sizeof(path) + sizeof(dp->d_name));
            strcpy(newPath, path);
            strcat(newPath, "/");
            strcat(newPath, dp->d_name);
            if (!stat(newPath, &buffer) && S_ISDIR(buffer.st_mode))
                findFiles(opendir(newPath), pattern, newPath);
            if (strstr(dp->d_name, pattern))
                printf("%s/%s\n", path, dp->d_name);
            free(newPath);
        }
    }
    closedir(dir);
}

int main(int argc, char** argv) {
    DIR* dir;
    char* pattern = (argv[1]) ? argv[1] : "";
    if (!(dir = opendir("."))) {
        perror("Cannot open directory");
        exit(1);
    }
    findFiles(dir, pattern, ".");
    return EXIT_SUCCESS;
}