#include <stdio.h>
#include <stdlib.h>

#define SECTOR_SIZE 512
#define SECTOR_WORDS (SECTOR_SIZE / sizeof(long))

int main(int argc, char *argv[])
{
	unsigned long sector[SECTOR_WORDS];
	unsigned long secnum, n;
	FILE *f;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s n outfile.img\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = atol(argv[1]);
	f = fopen(argv[2], "w");

	if (f == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	for (secnum = 0; secnum < n; secnum++) {
		for (int i = 0; i < SECTOR_WORDS; i++)
			sector[i] = (secnum << 6) | i;
		if (fwrite(sector, SECTOR_SIZE, 1, f) < 1) {
			perror("fwrite");
			exit(EXIT_FAILURE);
		}
	}

	fclose(f);

	return 0;
}
