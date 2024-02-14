#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void recursive_pipe(int depth, int *fds);

int main() {
    int fds[2];

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    recursive_pipe(5, fds);

    return 0;
}

void recursive_pipe(int depth, int *fds) {
    if (depth == 0) {
        // Base case: reached the maximum depth, read from the pipe
        int rr;
        read(fds[0], &rr, sizeof(int));
        printf("RR IS %i\n", rr);
        close(fds[0]);
        close(fds[1]);
        return;
    }

    pid_t pid;
    int new_fds[2];

    if (pipe(new_fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Child process
        close(fds[0]); // Close read end of the parent pipe
        close(new_fds[0]); // Close read end of the child pipe
        int lol = 100;
        write(new_fds[1], &lol, sizeof(int)); // Write data to child pipe
        close(new_fds[1]); // Close write end of the child pipe
        recursive_pipe(depth - 1, fds); // Recursively call with parent pipe
    } else { // Parent process
        close(new_fds[1]); // Close write end of the child pipe
        close(fds[1]); // Close write end of the parent pipe
        int x;
        read(new_fds[0], &x, sizeof(int)); // Read data from child pipe
        write(fds[1], &x, sizeof(int)); // Write data to parent pipe
        close(fds[0]); // Close read end of the parent pipe
        close(new_fds[0]); // Close read end of the child pipe
        wait(NULL); // Wait for child process to finish
    }
}
