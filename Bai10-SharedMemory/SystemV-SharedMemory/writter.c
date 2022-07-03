#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 35

int main()
{	
	int shmid;
	char *shmaddr;
	char string_hello[50] = "Hello ae wibu";
	
	shmid = shmget(KEY, 1024, 0666 | IPC_CREAT);
	if (shmid == -1) {
		printf("failed to create ID of Shared Memory\n");
		return 0;
	}
	
	shmaddr = (char *)shmat(shmid, NULL, 0);
	strcpy(shmaddr, string_hello);
	int return_detach = shmdt(shmaddr);
        if (return_detach == -1) {
                printf("failed to detach\n");
        }

	return 0;
}
