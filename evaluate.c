#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define FIB_DEV "/dev/fibonacci"

int main()
{
    long long sz, ut;
    // cppcheck-suppress variableScope
    char buf[1];
    char write_buf[] = "testing writing";
    int offset = 100;
    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }
    struct timespec tv1, tv2;
    FILE *out;
    out = fopen("output.txt", "w");
    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        clock_gettime(CLOCK_REALTIME, &tv1);
        sz = read(fd, buf, 1);
        clock_gettime(CLOCK_REALTIME, &tv2);
        printf("F(%d) = %lld \n", i, sz);
        sz = write(fd, write_buf, strlen(write_buf));
        ut = (tv2.tv_nsec) - (tv1.tv_nsec) - sz;
        printf("F(%d) cost %lld ns in kernel\n", i, sz);
        printf("F(%d) cost %lld ns in kernel to user\n", i, ut);
        printf("F(%d) cost %lld ns in user\n", i, sz + ut);
        fprintf(out, "%d %lld %lld %lld\n", i, sz, ut, sz + ut);
    }
}