#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRACE 1

#define BOULDER 'O'
#define ROCK    '#'
#define GROUND  '.'

int find_lowest_point(char **platform, int i, int j) {
	while (i >= 0 && platform[i][j] == GROUND) {
		i--;
	}
	return i+1;
}

void print_pattern(char **data, uint height) {
	for (int i = 0; i < height; i++) {
		printf("%s\n", data[i]);
	}
	printf("\n");
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width = strlen(data[0]);

	char **platform = malloc(height * sizeof(char*));
	for (int i = 0; i < height; i++) {
		platform[i] = malloc(width);
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			platform[i][j] = data[i][j];
			if (data[i][j] == BOULDER) {
				platform[i][j] = GROUND;
				platform[find_lowest_point(platform, i, j)][j] = BOULDER;
			}
		}
	}

	if (TRACE)
		print_pattern(platform, height);

	uint load = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (platform[i][j] == BOULDER) {
				load += height-i;
			}
		}
	}
	printf("Total load: %u\n", load);
}
