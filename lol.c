#include <unistd.h>
#include <stdio.h>
int main() {
    const char *filename = "op.txt";

    // Check if the file exists
    if (access(filename, F_OK) == 0) {
        printf("%s exists\n", filename);
    } else {
        printf("%s does not exist\n", filename);
    }

    return 0;
}
