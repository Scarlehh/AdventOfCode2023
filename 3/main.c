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
	if (isdigit(value)) {
		return 1;
	}

	return 0;
}

enum Direction check_include_number(char **data, int height, int width, int i, int j, enum Direction dir) {
	//printf("Checking: %d %d %d %d\n", height, width, i, j);
	struct coordinate coords;
	get_coordinates(dir, &coords);
	if (check_adjacent_number(data, height, width, i+coords.i, j+coords.j)) {
		return i;
	}
	return INVALID;
}

uint parse_number(char **data, int height, int width, int i, int j, int *dir) {
	struct coordinate coords;
	get_coordinates(*dir, &coords);
	i += coords.i;
	j += coords.j;

	if (i < 0 || height <= i) {
		return 0;
	}
	if (j < 0 || width <= j) {
		return 0;
	}

	uint number = data[i][j] - '0';

	// Go left
	int idx = j-1;
	uint multiplier = 10;
	while (idx >= 0 && isdigit(data[i][idx])) {
		number += (data[i][idx] - '0') * multiplier;
		idx--;
		multiplier *= 10;
	}

	// Go right
	idx = j+1;
	while (idx < width && isdigit(data[i][idx])) {
		number = (number * 10) + (data[i][idx] - '0');
		idx++;

		// Basically a hack cus my solution doesn't handle multiple adjacent axis
		if (*dir == TOP_LEFT || *dir == TOP || *dir == BOTTOM_LEFT || *dir == BOTTOM) {
			*dir+=2;
		}
	}

	return number;
}

int main() {
	char **data = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width = strlen(data[0]);

	uint total_part_numbers = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			char value = data[i][j];

			if (value == '*') {
				uint gear_ratio = 0;
				uint include = 0;

				for (int d = TOP_LEFT; d <= BOTTOM_RIGHT; d++) {
					if (check_include_number(data, height, width, i, j, d) != INVALID) {
						uint number = parse_number(data, height, width, i, j, &d);
						//printf("Parsed %d\n", number);
						if (!include) {
							gear_ratio = number;
						} else {
							gear_ratio *= number;
						}
						include++;
					}
				}

				if (include > 1) {
					//printf("Including %d\n", gear_ratio);
					total_part_numbers += gear_ratio;
				}
			}
		}
	}

	printf("Total: %d\n", total_part_numbers);

	return 0;
}
