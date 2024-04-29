#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int copyFile(const char *srcPath, const char *destPath) {
    int srcFd, destFd, bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    srcFd = open(srcPath, O_RDONLY);
    if (srcFd == -1) {
        perror("Failed to open source file");
        return -1;
    }

    destFd = open(destPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd == -1) {
        perror("Failed to open destination file");
        close(srcFd);
        return -1;
    }

    while ((bytesRead = read(srcFd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(destFd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Write error");
            close(srcFd);
            close(destFd);
            return -1;
        }
    }

    close(srcFd);
    close(destFd);

    if (bytesRead == -1) {
        perror("Read error");
        return -1;
    }

    return 0;
}

int main() {
    const char *sourceDir = "/opt";
    const char *destinationDir = "/mnt/pendrive"; // Substitua pelo caminho do seu pendrive montado

    DIR *dir;
    struct dirent *entry;

    dir = opendir(sourceDir);
    if (dir == NULL) {
        perror("Failed to open source directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char srcPath[PATH_MAX];
            char destPath[PATH_MAX];

            snprintf(srcPath, sizeof(srcPath), "%s/%s", sourceDir, entry->d_name);
            snprintf(destPath, sizeof(destPath), "%s/%s", destinationDir, entry->d_name);

            if (copyFile(srcPath, destPath) != 0) {
                fprintf(stderr, "Failed to copy file: %s\n", entry->d_name);
            } else {
                printf("File copied successfully: %s\n", entry->d_name);
            }
        }
    }

    closedir(dir);

    return 0;
}
