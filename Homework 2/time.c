/**
 * Records the amount of time to run a command.
 * Uses shared memory. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    const char *name = "v1";
    const int SIZE = 24;
    struct timeval start;
    struct timeval end;
    pid_t pid;
    int shm_fd;
    char *ptr;
    if (argc == 1)
        return 0;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("shared memory creation failed\n");
        return  -1;
    }
    ftruncate(shm_fd, SIZE);
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("memory map failed\n");
        return -1;    
    }
    pid = fork();
    if (pid == 0)
    {
        // child
        if (gettimeofday(&start, NULL) != 0)
            return 0;
        // [FILL UP] write the starting time to shared memory
        printf("Child writing %ld seconds, %ld microsenconds\n\n", start.tv_sec, start.tv_usec);
	ptr += sprintf(ptr, "%ld.%ld\n", start.tv_sec, start.tv_usec);
    
        // [FILL UP] now execute the command
        execvp(argv[1], &argv[1]);

        fprintf(stderr, "Error");
    }
    else { 
    //parent
        wait(NULL);
    
        if (gettimeofday(&end, NULL) != 0)
            return -1;
        printf("\nParent ending time = %ld sec, %ld microsec\n",end.tv_sec, 
end.tv_usec);
        
        // [FILL UP] read the starting time from shared memory
        long start_seconds = 0;
	long start_useconds = 0;
	sscanf(ptr, "%ld.%ld", &start_seconds, &start_useconds);

        // [FILL UP] now determine elapsed time
	int seconds = (end.tv_sec - start_seconds);
	int useconds = (end.tv_usec, - start_useconds);
	printf("\nElapsed time = %d.%d\n", seconds, useconds);

        shm_unlink(name);
    }
    return 0;
}

