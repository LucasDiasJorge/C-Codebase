#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void printFileTimes(const char *path) {
    struct stat fileStat;

    if (stat(path, &fileStat) < 0) {
        perror("stat");
        return;
    }

    // Convert and print the last modification time
    printf("Last modification time: %s", ctime(&fileStat.st_mtime));

    // Convert and print the last status change time
    printf("Last status change time: %s", ctime(&fileStat.st_ctime));

#if defined(__linux__) && defined(st_birthtim)
    printf("Creation time: %s", ctime(&fileStat.st_birthtim.tv_sec));
#else
    printf("Creation time not supported on this system.\n");
#endif
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_file>\n", argv[0]);
        return 1;
    }

    printFileTimes(argv[1]);

    return 0;
}
