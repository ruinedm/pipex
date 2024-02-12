#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    char buffer[100];
    pipe(pipefd); // Create a pipe

    // Fork a child process
    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        close(pipefd[1]); // Close write end of the pipe in the child
        read(pipefd[0], buffer, sizeof(buffer)); // Read data from the pipe
        printf("Child process received: %s\n", buffer);
    } else {
        // Parent process
        close(pipefd[0]); // Close read end of the pipe in the parent
        write(pipefd[1], "Hello from parent!", 18); // Write data to the pipe
    }

    return 0;
}
