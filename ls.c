#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_perms(mode_t perms) {
    printf((S_ISDIR(perms)) ? "d" : "-");
    printf((perms & S_IRUSR) ? "r" : "-");
    printf((perms & S_IWUSR) ? "w" : "-");
    printf((perms & S_IXUSR) ? "x" : "-");
    printf((perms & S_IRGRP) ? "r" : "-");
    printf((perms & S_IWGRP) ? "w" : "-");
    printf((perms & S_IXGRP) ? "x" : "-");
    printf((perms & S_IROTH) ? "r" : "-");
    printf((perms & S_IWOTH) ? "w" : "-");
    printf((perms & S_IXOTH) ? "x" : "-");
}

int main(int argc, char** argv) {
    DIR* dir;
    struct dirent* dp;
    char** list = (char**) malloc(100 * sizeof(char*));
    int c = 0;
    if (!(dir = opendir("."))) {
        perror("Cannot open directory");
        exit(1);
    }
    while ((dp = readdir(dir))) {
        if (strncmp(dp->d_name, ".", 1)) {
            list[c] = (char*) malloc(100 * sizeof(char));
            sprintf(list[c], "%s", dp->d_name);
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
    if (argv[1] && !strcmp(argv[1], "-l")) {
        for (int i = 0; i < c; ++i) {
            struct stat buffer;
            if (!stat(list[i], &buffer)) {
                char date[7];
                print_perms(buffer.st_mode);
                strftime(date, 6, "%b %d", gmtime(&(buffer.st_ctime)));
                printf(" %s %s %ld %s %s\n", getpwuid(buffer.st_uid)->pw_name, getgrgid(buffer.st_gid)->gr_name,
                       buffer.st_size, date, list[i]);
            }
            free(list[i]);
        }
    }
    else {
        for (int i = 0; i < c; ++i) {
            printf("%s\n", list[i]);
            free(list[i]);
        }
    }
    free(list);
    closedir(dir);
    return EXIT_SUCCESS;
}