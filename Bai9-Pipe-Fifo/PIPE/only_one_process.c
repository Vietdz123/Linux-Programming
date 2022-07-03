#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd[2];
	char buff_read[30] = {0};
	if (pipe(fd) == -1) {
		printf("pipe create failed\n");
		return 0;
	}
	
	write(fd[1], "Hello ae wibu", strlen("Hello ae wibu"));
	read(fd[0], buff_read, 20);
	printf("Data receive: %s\n", buff_read);

	return 0;
}
