#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mount.h>

int main() {
    char *source = "/dev/sda1";  // Assuming this is the device file for your USB drive
    char *target = "/mnt/usb";    // Mount point for the USB drive
    char *filesystem = "vfat";    // Filesystem type of the USB drive (e.g., vfat, ext4)

    // Attempt to unmount the USB drive if it's already mounted
    if (umount(target) != 0) {
        perror("umount");
        // You may choose to exit here, or proceed if unmounting failed
    } else {
        printf("USB drive unmounted successfully.\n");
    }

    return 0;
}
