#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

const char* get_filename_ext(const char* filename) {
    const char *dot = strchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot;
}

int main(int argc, char *argv[]) {

    printf("this operation rename all files and folders in current directory\n");
    printf("example: \033[38;5;10mfile.txt\033[0m rename to \033[38;5;10m0000.txt\033[0m\n");
    printf("example: \033[38;5;10mmain.c\033[0m rename to \033[38;5;10m0001.c\033[0m\n");

    printf("continue operation (y/n): ");

    char c = getchar();

    if(c != 'y') {
        printf("exit\n");
        exit(0);
    }

    struct dirent *de;

    DIR *dr = opendir(".");

    if (dr == NULL)  {
        printf("Could not open current directory");
        return 0;
    }

    struct stat st;
    if (stat("./.tmp/", &st) == -1) {
        mkdir("./.tmp/", 0700);
    }

    int count = 0;
    int step = 1;

    while((de = readdir(dr)) != NULL) {

        if(de->d_name[0] == '.') continue;
        stat(de->d_name, &st);
        if(!S_ISDIR(st.st_mode)) { // if item is not dir

            char new_name[1024];
            sprintf(new_name, "./.tmp/%08d%s", count, get_filename_ext(de->d_name));
            rename(de->d_name, new_name);

            count += step;
        }

    }

    closedir(dr);


    dr = opendir("./.tmp/");

    if (stat("./.tmp/", &st) == -1) {
        exit(2);
    }

    chdir("./.tmp/");

    while((de = readdir(dr)) != NULL) {

        if(de->d_name[0] == '.') continue;

        char new_name[1024];
        sprintf(new_name, "../%s", de->d_name);

        rename(de->d_name, new_name);
    }

    closedir(dr);

    chdir("..");

    remove("./.tmp/");


    return 0;
}
