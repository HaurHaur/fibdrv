#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"

int main()
{
    char buf[1];
    char write_buf[] = "testing writing";
    int offset = 100;
    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        printf("F(%d) = %ld \n", i, read(fd, buf, 1));
        printf("F(%d) cost %ld ns \n", i,
               write(fd, write_buf, strlen(write_buf)));
    }
}