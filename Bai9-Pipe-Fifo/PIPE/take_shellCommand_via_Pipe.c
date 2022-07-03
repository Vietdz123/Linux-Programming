#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	//if (argc < 2) {
		//printf("Enter command\n");
		//return 0;
	//}

	FILE *file_connected_pipe;
	char buffer[1024];
	int count = 0;

	printf("Starting system call ...\n");
	file_connected_pipe = popen("lsblk", "r");
	
	if (file_connected_pipe == NULL) {
		printf("failed to open file pipe\n");
		return 0;
	}	
	
	while (fgets(buffer, 1024, file_connected_pipe) != NULL) {
		if (count == 0) {
			printf("Data recieve from command through pipe is:\n%s", buffer);
			count++;
		} else {
			printf("%s", buffer);
		}
	}
	pclose(file_connected_pipe);

	return 0;
}	

