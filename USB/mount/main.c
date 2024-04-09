#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>

int main() {
    char *source = "/dev/sda1";  // Assuming this is the device file for your USB drive, use lsblk
    char *target = "/mnt/usb";    // Mount point for the USB drive
    char *filesystem = "vfat";    // Filesystem type of the USB drive (e.g., vfat, ext4)

    // Create the mount point directory if it does not exist
    if (access(target, F_OK) != 0) {
        if (mkdir(target, 0777) != 0) {
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
    }

    // Attempt to mount the USB drive
    if (mount(source, target, filesystem, MS_MGC_VAL, NULL) == 0) {
        printf("USB drive mounted successfully.\n");
    } else {
        perror("mount");
        exit(EXIT_FAILURE);
    }

    return 0;
}
