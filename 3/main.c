#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

uint check_adjacent_symbol(char **data, int height, int width, int i, int j) {
	//printf("    %d %d\n", i, j);
	if (i < 0 || height <= i) {
		return 0;
	}
	if (j < 0 || width <= j) {
		return 0;
	}

	char value = data[i][j];
	if (!isalnum(value) && value != '.') {
		return 1;
	}

	return 0;
}

uint check_include_number(char **data, int height, int width, int i, int j) {
	//printf("Checking: %d %d %d %d\n", height, width, i, j);
	if (check_adjacent_symbol(data, height, width, i-1, j-1)) return 1;
	if (check_adjacent_symbol(data, height, width, i-1, j)) return 1;
	if (check_adjacent_symbol(data, height, width, i-1, j+1)) return 1;
	if (check_adjacent_symbol(data, height, width, i, j-1)) return 1;
	if (check_adjacent_symbol(data, height, width, i, j)) return 1;
	if (check_adjacent_symbol(data, height, width, i, j+1)) return 1;
	if (check_adjacent_symbol(data, height, width, i+1, j-1)) return 1;
	if (check_adjacent_symbol(data, height, width, i+1, j)) return 1;
	if (check_adjacent_symbol(data, height, width, i+1, j+1)) return 1;
	return 0;
}

int main() {
	char **data = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width = strlen(data[0]);

	uint total_part_numbers = 0;

	for (int i = 0; i < height; i++) {
		printf("\n%s\n", data[i]);

		for (int j = 0; j < width; j++) {
			char value = data[i][j];

			if (isdigit(value)) {
				uint number = 0;
				uint include = 0;

				while (isdigit(value)) {
					number = (number*10) + (value-'0');
					// If we have already included this number, don't check again
					if (!include) {
						include = check_include_number(data, height, width, i, j);
					}
					j++;
					value = data[i][j];
				}

				if (include) {
					printf("Including %d\n", number);
					total_part_numbers += number;
				}
			}
		}
	}

	printf("Total: %d\n", total_part_numbers);

	return 0;
}
