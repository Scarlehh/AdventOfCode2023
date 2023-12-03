#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum Direction {
	INVALID=0,
	TOP_LEFT,
	TOP,
	TOP_RIGHT,
	LEFT,
	RIGHT,
	BOTTOM_LEFT,
	BOTTOM,
	BOTTOM_RIGHT
};

struct coordinate {
	int i;
	int j;
};

void get_coordinates(enum Direction dir, struct coordinate *coords) {
	switch (dir) {
	case TOP_LEFT:
		coords->i = -1;
		coords->j = -1;
		break;
	case TOP:
		coords->i = -1;
		coords->j = 0;
		break;
	case TOP_RIGHT:
		coords->i = -1;
		coords->j = 1;
		break;
	case LEFT:
		coords->i = 0;
		coords->j = -1;
		break;
	case RIGHT:
		coords->i = 0;
		coords->j = 1;
		break;
	case BOTTOM_LEFT:
		coords->i = 1;
		coords->j = -1;
		break;
	case BOTTOM:
		coords->i = 1;
		coords->j = 0;
		break;
	case BOTTOM_RIGHT:
		coords->i = 1;
		coords->j = +1;
		break;
	}
}

uint check_adjacent_number(char **data, int height, int width, int i, int j) {
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

enum Direction check_include_number(char **data, int height, int width, int i, int j) {
	//printf("Checking: %d %d %d %d\n", height, width, i, j);
	for (int d = TOP_LEFT; d <= BOTTOM_RIGHT; d++) {
		struct coordinate coords;
		get_coordinates(d, &coords);
		if (check_adjacent_number(data, height, width, i+coords.i, j+coords.j)) {
			return i;
		}
	}
	return INVALID;
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
						enum Direction dir = check_include_number(data, height, width, i, j);
						if (dir != INVALID) {
							include = 1;
						}
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
