#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void
copybytes(char *in_file, char *out_file, char *buffer, int read_b, int limit)
{
	int fd1, fd2;
	ssize_t bytes, total_bytes = 0;

	if (read_b < 0 || limit < -1) {
		fprintf(stderr,
			"The number of rolls has to be > 0 and the limit has to be >= -1\n");
		exit(EXIT_FAILURE);
	}

	if (strcmp(in_file, "-") == 0) {
		fd1 = STDIN_FILENO;
	} else {
		fd1 = open(in_file, O_RDONLY);
		if (fd1 < 0) {
			fprintf(stderr, "Can`t open the file\n");
			exit(EXIT_FAILURE);
		}
	}

	if (strcmp(out_file, "-") == 0) {
		fd2 = STDOUT_FILENO;
	} else {
		fd2 = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}

	while ((bytes = read(fd1, buffer, read_b)) > 0 && total_bytes != limit) {
		total_bytes += bytes;
		write(fd2, buffer, bytes);
	}
	close(fd1);
	close(fd2);
}

int
main(int argc, char *argv[])
{
	char *buffer;
	char *s, *s2;
	int read_b, buffer_size;

	switch (argc) {
	case 4:
		buffer_size = strtol(argv[3], &s, 10);

		if (strcmp("\0", s) != 0 || buffer_size < 0) {
			fprintf(stderr,
				"Can´t convert to positive int the buffer size\n");
			exit(EXIT_FAILURE);
		}

		buffer = (char *)malloc(buffer_size * sizeof(char));
		copybytes(argv[1], argv[2], buffer, buffer_size, -1);
		break;
	case 5:
		buffer_size = strtol(argv[3], &s, 10);
		read_b = strtol(argv[4], &s2, 10);

		if (strcmp("\0", s) != 0 || strcmp("\0", s2) != 0
		    || buffer_size < 0) {
			fprintf(stderr,
				"Can´t convert to positive int the buffer size or the read bytes\n");
			exit(EXIT_FAILURE);
		}

		buffer = (char *)malloc(buffer_size * sizeof(char));
		copybytes(argv[1], argv[2], buffer, read_b, read_b);
		break;
	default:
		fprintf(stderr,
			"Usage: copybytes [input_file || -] [output_file || -] [int_buffer] [int_bytes]\n");
		exit(EXIT_FAILURE);
		break;
	}

	free(buffer);
	exit(EXIT_SUCCESS);
}
