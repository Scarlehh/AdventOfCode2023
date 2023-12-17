#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRACE 0

#define ASH '.'
#define ROCK '#'

#define is_not_smudged(smudge) (smudge->i == -1 && smudge->j == -1)
#define is_smudged(smudge) !is_not_smudged(smudge)
#define is_smudged_at(smudge, _i, _j) (smudge->i == _i && smudge->j == _j)
#define create_smudge(smudge, _i, _j)						\
	do {													\
		smudge->i = _i;										\
		smudge->j = _j;										\
		if (TRACE) {										\
			if (is_smudged(smudge)) {						\
				printf("Create smudge at %u %u\n", _i, _j);	\
			} else {										\
				printf("Removing smudge\n");				\
			}												\
		}													\
	} while (0)
#define remove_smudge(smudge) create_smudge(smudge, -1, -1)

struct Smudge {
	int i;
	int j;
};

uint check_fields(char fieldA, char fieldB, uint i, uint j, uint d_i, uint d_j,
				  struct Smudge *smudge) {
	if (is_smudged_at(smudge, i, j)) {
		fieldA = fieldA == ASH ? ROCK : ASH;
	}
	if (is_smudged_at(smudge, i+d_i, j+d_j)) {
		fieldB = fieldA == ASH ? ROCK : ASH;
	}
	if (fieldA != fieldB) {
		if (is_not_smudged(smudge)) {
			create_smudge(smudge, i, j);
		} else {
			return 0;
		}
	}
	return 1;
}

uint _find_vertical_reflections(const char **field, uint height, uint width,
								uint j, uint d, struct Smudge *smudge) {
	for (int i = 0; i < height; i++) {
		if (check_fields(field[i][j], field[i][j+d], i, j, 0, d, smudge) == 0) {
			return 0;
		}
	}
	if (j == 0 || j+d == width-1) {
		return 1;
	}
	return _find_vertical_reflections(field, height, width, j-1, d+2, smudge);
}

uint _find_horizontal_reflections(const char **field, uint height, uint width,
								  uint i, uint d, struct Smudge *smudge) {
	for (int j = 0; j < width; j++) {
		if (check_fields(field[i][j], field[i+d][j], i, j, d, 0, smudge) == 0) {
			return 0;
		}
	}
	if (i == 0 || i+d == height-1) {
		return -1;
	}
	return _find_horizontal_reflections(field, height, width, i-1, d+2, smudge);
}

uint find_vertical_reflections(const char **field, uint height, uint width,
							   struct Smudge *smudge) {
	for (int j = 0; j < width-1; j++) {
		if (_find_vertical_reflections(field, height, width, j, 1, smudge) &&
			is_smudged(smudge)) {
			if (TRACE)
				printf("Found vertical reflection at columns %u %u\n", j, j+1);
			return j+1;
		}
		remove_smudge(smudge);
	}

	return 0;
}

uint find_horizontal_reflections(const char **field, uint height, uint width,
								 struct Smudge *smudge) {
	for (int i = 0; i < height-1; i++) {
		if (_find_horizontal_reflections(field, height, width, i, 1, smudge) &&
			is_smudged(smudge)) {
			if (TRACE)
				printf("Found horizontal reflection at rows %u %u\n", i, i+1);
			return 100*(i+1);
		}
		remove_smudge(smudge);
	}

	return 0;
}

void print_pattern(const char **field, uint height) {
	for (int i = 0; i < height; i++) {
		printf("%s\n", field[i]);
	}
	printf("\n");
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width = 0;

	uint sum = 0;
	struct Smudge *smudge = malloc(sizeof(struct Smudge));
	for (int i = 0, start = 0; i < height; i++) {
		if (data[i+1] == NULL || data[i+1][0] == '\0') {
			uint ret;

			width  = strlen(data[i]);
			remove_smudge(smudge);

			if (TRACE)
				print_pattern(data+start, i-start+1);
			do {
				if (ret = find_vertical_reflections(data+start, i-start+1, width,
													smudge)) {
					sum += ret;
				}
				else if (ret = find_horizontal_reflections(data+start, i-start+1, width,
														   smudge)) {
					sum += ret;
				}
			} while (is_not_smudged(smudge));

			start = i+2;
		}
	}
	printf("Total sum is %u\n", sum);
}
