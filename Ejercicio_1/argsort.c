#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void
argsort(int len, char *list[])
{
	char *copy_str;
	int i, j, selected;

	for (i = 0; i < len; i++) {
		selected = i;
		copy_str = list[i];
		for (j = i; j < len; j++) {
			if (strcmp(list[j], list[selected]) < 0) {
				selected = j;
			}
		}
		list[i] = list[selected];
		list[selected] = copy_str;
	}
}

void
printargs(int len, char *list[], char *opt)
{
	int i;
	char *dir[] = { "forward", "backward" };

	if (opt == NULL || strcmp(opt, dir[0]) == 0) {
		for (i = 0; i < len; ++i) {
			printf("%d: %s\n", i, list[i]);
		}
	} else if (strcmp(opt, dir[1]) == 0) {
		for (i = (len - 1); i >= 0; --i) {
			printf("%d: %s\n", (len - 1) - i, list[i]);
		}
	} else {
		fprintf(stderr, "Err:Incorrect environment variable\n");
	}
}

int
main(int argc, char *argv[])
{
	int i;
	char *enviro;

	char **copy_arr = malloc((argc - 1) * sizeof(char *));

	for (i = 1; i < argc; ++i) {
		copy_arr[i - 1] = argv[i];
	}

	enviro = getenv("DIRECTION");
	argsort((argc - 1), copy_arr);
	printargs((argc - 1), copy_arr, enviro);

	exit(EXIT_SUCCESS);
}
