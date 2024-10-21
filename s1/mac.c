#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Open the file for writing, creating it if it doesn't exist
    fd = open("file_with_hole.txt", O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Seek to a position 100 bytes before the end of the file, creating a hole
    if (lseek(fd, 100, SEEK_END) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Write some data at the end of the file
    if (write(fd, "This is the end data", 18) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    printf("File with hole created successfully.\n");
    return 0;
}
