#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void) {
	pid_t pid;
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Error\n");
		return -1;
	}
	else if (pid ==0) {//Child
		return 0;
	}
	else {//Parent
		sleep(10);
		printf("Parent exiting");
		return 0;
	}
}

