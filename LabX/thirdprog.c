#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal handler for SIGUSR1 in child process
void sigusr1_handler(int sig) {
    printf("Child received SIGUSR1 (signal %d).\n", sig);
    exit(0);
}

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) { // Error
        perror("fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) { // Child process
        // Register SIGUSR1 handler
        if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR) {
	    perror("signal error");
	    exit(EXIT_FAILURE);
	}

	printf("Child process PID = %d. Waiting for SIGUSR1...\n", getpid());

	// Infinite loop
        while (1) {
            pause(); // Wait for a signal
        }
    }
    else { // Parent process
        printf("Parent process PID = %d, Child PID = %d\n", getpid(), pid);

        // Sleep for 3 seconds before sending SIGUSR1
        sleep(3);

        printf("Parent sending SIGUSR1 to child process.\n");

        // Send SIGUSR1 signal to the child process
        if (kill(pid, SIGUSR1) == -1) {
	    perror("kill error");
	    exit(EXIT_FAILURE);
	}

        // Wait for the child process to terminate
        wait(NULL);
        printf("Child process terminated.\n");
    }

    return 0;
}
