#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

	int fd1[2], fd2[2], status;
	pipe(fd1);
	pipe(fd2);
	
	pid_t pid1 = fork();
	
	if (!pid1) { 
        dup2(fd1[1], 1);
        
        close(fd1[0]);
        close(fd1[1]);
		close(fd2[0]);
        close(fd2[1]);
        
        char* command[5] = {"awk", "-f", "command.awk", "log.txt", 0};
        execvp(command[0], command);
        
        exit(EXIT_FAILURE);
    } else if (pid1 == -1) {
        fprintf(stderr, "Can't fork, exiting...\n");
        exit(EXIT_FAILURE);
    }
	
	pid_t pid2 = fork();
	
	if (!pid2) {
        dup2(fd1[0], 0);
        
        close(fd1[0]);
        close(fd1[1]);
		
		dup2(fd2[1],1);
		
		close(fd2[0]);
        close(fd2[1]);
        
        char* command[3] = {"sort", "-nrk3", 0};
        execvp(command[0], command);
        
        exit(EXIT_FAILURE);
    } else if (pid2 == -1) {
        fprintf(stderr, "Can't fork, exiting...\n");
        exit(EXIT_FAILURE);
    }
	
	pid_t pid3 = fork();
	
	if(!pid3) {
		close(fd1[0]);
        close(fd1[1]);
		dup2(fd2[0],0);
		close(fd2[0]);
        close(fd2[1]);
		
		char* command[2] = {"head", 0};
		execvp(command[0], command);
		
		exit(EXIT_FAILURE);
	} else if (pid3 == -1) {
		fprintf(stderr, "Can't fork, exiting...\n");
		exit(EXIT_FAILURE);
	}
    
    close(fd1[0]);
    close(fd1[1]);
	
	close(fd2[0]);
	close(fd2[1]);
	
	waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
	waitpid(pid3, &status, 0);
	
	exit(status);
	
	return 0;
}