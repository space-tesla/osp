#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char filename[] = "file_with_hole.txt";
    int file_size = 1024; // Size of the hole in bytes

    // Create a new file with write permissions
    fd = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Seek to a position beyond the end of the file (creating a hole)
    if (lseek(fd, file_size - 1, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Write something at the end of the file
    char data[] = "Hello, this is data at the end of the file.";
    ssize_t bytes_written = write(fd, data, sizeof(data) - 1);
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Close the file
    close(fd);
    printf("File with a hole created: %s\n", filename);

    return 0;
}
