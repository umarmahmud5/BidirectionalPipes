#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(void){
	int fd[2];
	int fd1[2];
	pid_t childpid;
	char string[] = "Hello I am Parent, How are you?\n";
	char string1[] = "I am child and I am fine, thankyou.\n";
	char readbuffer[80];
	char readbuffer1[80];
	int result = pipe(fd);
	int result1 = pipe(fd1);
	if(result<0 && result1<0){
		printf("Error Creating Pipes\n");
		return 1;
	}
	childpid = fork();
	if(childpid == -1){
		printf("Error in creating child\n");
		return 1;
	}
	if(childpid == 0){
		close(fd[0]);	//send string through output side of pipe
		printf("Child writing in pipe\n");
		write(fd[1], string, sizeof(string));
		close(fd[1]);
		printf("child reading from pipe\n");
		read(fd1[0], readbuffer1, sizeof(readbuffer1)); //Child reads pipe
		printf("Received String from parent : %s", readbuffer1);
		return 0;
	}
	else{
		close(fd[1]);
		usleep(3000);
		printf("Parent reading from pipe\n");
		read(fd[0], readbuffer, sizeof(readbuffer)); //Parent reads pipe
		printf("Received String from child: %s", readbuffer);
		close(fd1[0]);	//send string through output side of pipe
		printf("Parent writing in pipe\n");
		write(fd1[1], string1, sizeof(string1));
	}
	return 0;
}
