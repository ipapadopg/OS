#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Open the file in appending mode
    FILE *fp = fopen("output_pids.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) { // Error
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // Child process
        // Write the child PID to the file
        fprintf(fp, "Child PID = %d\n", getpid());
        // Close the file
	if (fclose(fp) != 0) {
	    perror("Error closing file");
	    return EXIT_FAILURE;
	}
    }
    else { // Parent process
        // Wait for the child process to finish
        wait(NULL);

        // Write the parent PID to the file
        fprintf(fp, "Parent PID = %d\n", getpid());
	// Close the file
	if (fclose(fp) != 0) {
            perror("Error closing file");
            return EXIT_FAILURE;
        }
    }

    printf("Data written to output_pids.txt successfully.\n");
    return EXIT_SUCCESS;
}
