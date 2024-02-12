#include "pipex.h"

int main() {
    int fd = open("op.txt", O_RDWR, 0777);
    dup2(fd, 1);
    close(fd);
    write(1, "LOL NIGGER", 2);
    return 0;
}
