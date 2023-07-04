#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	/* Check the argument number */
	if (argc < 3) {
		printf("usage: ./kvclient <fifo name> <get or set> <key> <value>\n");
		exit(-1);
	}

	int fifo_fd, fifo_read_fd;
	char* other_fifo = "output_fifo";
	char *server_fifo = argv[1];
	char *action = argv[2];
	char *key = argv[3];
	char *value;
	char command[100];
	char buffer[BUFSIZ];
	int n, i;
	char *token;
	memset(buffer, 0, sizeof(buffer));

	/* Check if a get or set depending on number of args */
	if (argc == 5) {
		value = argv[4];
	}


	/* Reset the command array */
	command[0] = '\0';

	/* Get arguments and put into string */
	for(i = 2; i < argc; i++){
		strcat(command, argv[i]);
		strcat(command, " ");
	}

	/* Null terminate */
	int length = strlen(command);
	command[length] = '\0';


	/* Open server and print open */
	fifo_fd = open(server_fifo, O_WRONLY);
	fifo_read_fd = open(other_fifo, O_RDONLY);
	usleep(100);

	if (fifo_read_fd == -1 || fifo_fd == -1){
		perror("open failure");
		exit(EXIT_FAILURE);
	}

	/* Send over files */
	if(write(fifo_fd, command, strlen(command)) == -1){
		perror("write failed");
		close(fifo_fd);
		exit(1);
	}

	/* Check if get */
	token = strtok(command, " ");

	/* If get wait for response, else close */
	if (strcmp(token, "get") == 0){

		/* Read the response from the server */
		ssize_t num_bytes = read(fifo_read_fd, buffer, sizeof(buffer));
		if (num_bytes == -1){
			perror("Error reading from FIFO");
			exit(EXIT_FAILURE);
		}

		/* Null terminate buffer */
		buffer[num_bytes] = '\0';

		/* Print value */
		printf("%s", buffer);

	}
	/* Close servers */
	close(fifo_fd);
	close(fifo_read_fd);
	fflush(stdout);
	return 0;
}





