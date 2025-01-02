#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
	pid_t pid;

	// Create a new process
	pid = fork();

    	if (pid < 0) { // Error in fork
            perror("fork failed");
	    exit(EXIT_FAILURE);
    	}
    	else if (pid == 0) { // Child process
      	    printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
	    // Terminate child process
	    return 0;
    	}
    	else { // Parent process
	    printf("Parent Process: PID = %d, Created Child PID = %d\n", getpid(), pid);
	    // Wait for child process to finish
	    wait(NULL);
    	}
    }

    return 0;
}
