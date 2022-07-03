#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler_signal() {
	printf("I'm signal\n");
	wait(NULL);
}

int main()
{
	int fd[2];
	int child_pid;
	char buff_read[30] = {0};
	
	signal(SIGCHLD, handler_signal);
	if (pipe(fd) == -1) {
		printf("pipe create failed\n");
		return 0;
	}
	
	child_pid = fork();
	if (child_pid == 0) {
		int byte_read = 0; 
		char buff_read[100] = {0};
		printf("I'm process child PID = %d\n", getpid());
		close(fd[1]);
		
		while (1) {
			byte_read = read(fd[0], buff_read, 100);
			if (byte_read == 0) {
				close(fd[0]);
				break;
			}
			printf("Data receive: %s and byte read = %d\n", buff_read, byte_read);
		}
		return 0;

	} else if (child_pid > 0) {
		int byte_write = 0;
		char buff_write[100] = {0};
		printf("I'm process parent: PID_parent = %d, PID_child = %d\n", getpid(), child_pid);
		close(fd[0]);

		byte_write = write(fd[1], "Hello ae wibu", strlen("Hello ae wibu"));
		printf("Byte write = %d\n", byte_write);
		close(fd[1]);
		while(1);	
	
	} else {
		printf("failded to create fork()\n");
	}
	
	return 0;
}
