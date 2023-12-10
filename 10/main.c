#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Lists
struct Node {
	struct Node *next;
	int value;
};

struct Node* append_list(struct Node *head, int value) {
	if (head == NULL) {
		head = malloc(sizeof(struct Node));
		head->next = NULL;
		head->value = value;
	} else {
		head->next = append_list(head->next, value);
	}
	return head;
}

void free_list(struct Node *head) {
	if (head->next != NULL) {
		free_list(head->next);
	}
	free(head);
}

#define for_each_node(list, item)								\
	for (struct Node *item = list; item; item = item->next)

enum Direction {
	NONE = 0,
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum Pipe {
	START          = 'S',
	NORTH_TO_SOUTH = '|',
	EAST_TO_WEST   = '-',
	NORTH_TO_EAST  = 'L',
	NORTH_TO_WEST  = 'J',
	EAST_TO_SOUTH  = 'F',
	WEST_TO_SOUTH  = '7',
	GROUND         = '.'
};

struct Coordinate {
	uint i; // y
	uint j; // x
};

enum Direction opposite_direction(enum Pipe pipe, enum Direction direction) {
	if (direction == NORTH) {
		if (pipe == NORTH_TO_SOUTH) {
			return SOUTH;
		}
		if (pipe == NORTH_TO_EAST) {
			return EAST;
		}
		if (pipe == NORTH_TO_WEST) {
			return WEST;
		}
	}
	if (direction == SOUTH) {
		if (pipe == NORTH_TO_SOUTH) {
			return NORTH;
		}
		if (pipe == EAST_TO_SOUTH) {
			return EAST;
		}
		if (pipe == WEST_TO_SOUTH) {
			return WEST;
		}
	}
	if (direction == EAST) {
		if (pipe == EAST_TO_WEST) {
			return WEST;
		}
		if (pipe == NORTH_TO_EAST) {
			return NORTH;
		}
		if (pipe == EAST_TO_SOUTH) {
			return SOUTH;
		}
	}
	if (direction == WEST) {
		if (pipe == EAST_TO_WEST) {
			return EAST;
		}
		if (pipe == NORTH_TO_WEST) {
			return WEST;
		}
		if (pipe == WEST_TO_SOUTH) {
			return SOUTH;
		}
	}
	return NONE;
}

enum Direction derive_direction(enum Pipe pipe, enum Direction start) {
	if (start == NORTH || start == NONE) {
		if (pipe == NORTH_TO_SOUTH) {
			return NORTH;
		}
		if (pipe == EAST_TO_SOUTH) {
			return EAST;
		}
		if (pipe == WEST_TO_SOUTH) {
			return WEST;
		}
	}
	if (start == EAST || start == NONE) {
		if (pipe == EAST_TO_WEST) {
			return EAST;
		}
		if (pipe == NORTH_TO_WEST) {
			return NORTH;
		}
		if (pipe == WEST_TO_SOUTH) {
			return SOUTH;
		}
	}
	if (start == WEST || start == NONE) {
		if (pipe == EAST_TO_WEST) {
			return WEST;
		}
		if (pipe == NORTH_TO_EAST) {
			return NORTH;
		}
		if (pipe == EAST_TO_SOUTH) {
			return SOUTH;
		}
	}
	if (start == SOUTH || start == NONE) {
		if (pipe == NORTH_TO_SOUTH) {
			return SOUTH;
		}
		if (pipe == NORTH_TO_EAST) {
			return EAST;
		}
		if (pipe == NORTH_TO_WEST) {
			return WEST;
		}
	}
	return NONE;
}

enum Pipe derive_pipe(uint north, uint south, uint east, uint west) {
	if (north && south) {
		return NORTH_TO_SOUTH;
	}
	if (east && west) {
		return EAST_TO_WEST;
	}
	if (north && east) {
		return NORTH_TO_EAST;
	}
	if (north && west) {
		return NORTH_TO_WEST;
	}
	if (east && south) {
		return EAST_TO_SOUTH;
	}
	if (west && south) {
		return WEST_TO_SOUTH;
	}
	return GROUND;
}

enum Pipe find_starting_tile(enum Pipe **map, uint i, uint j,
							 uint height, uint width) {
	uint north = 0;
	uint south = 0;
	uint east  = 0;
	uint west  = 0;
	enum Pipe tile;
	// Check north
	if (i > 0) {
		tile = map[i-1][j];
		if (tile == NORTH_TO_SOUTH ||
			tile == EAST_TO_SOUTH ||
			tile == WEST_TO_SOUTH) {
			north = 1;
		}
	}
	// Check east
	if (j < width-1) {
		tile = map[i][j+1];
		if (tile == EAST_TO_WEST ||
			tile == NORTH_TO_WEST ||
			tile == WEST_TO_SOUTH) {
			east = 1;
		}
	}
	// Check west
	if (j > 0) {
		tile = map[i][j-1];
		if (tile == EAST_TO_WEST ||
			tile == NORTH_TO_EAST ||
			tile == EAST_TO_SOUTH) {
			west = 1;
		}
	}
	// Check south
	if (i < height-1) {
		tile = map[i+1][j];
		if (tile == NORTH_TO_SOUTH ||
			tile == NORTH_TO_EAST ||
			tile == NORTH_TO_WEST) {
			south = 1;
		}
	}
	return derive_pipe(north, south, east, west);
}

void update_coord(struct Coordinate *coord, enum Direction current_direction) {
	if (current_direction == NORTH) {
		coord->i--;
	}
	if (current_direction == EAST) {
		coord->j++;
	}
	if (current_direction == WEST) {
		coord->j--;
	}
	if (current_direction == SOUTH) {
		coord->i++;
	}
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width  = strlen(data[0]);

	struct Coordinate start_coord;
	enum Pipe **map = malloc(height * sizeof(enum Pipe*));
	for (int i = 0; i < height; i++) {
		map[i] = malloc(width * sizeof(enum Pipe));
		for (int j = 0; j < width; j++) {
			switch(data[i][j]) {
			case START:
				start_coord.i = i;
				start_coord.j = j;
				map[i][j] = START;
				break;
			case NORTH_TO_SOUTH:
				map[i][j] = NORTH_TO_SOUTH;
				break;
			case EAST_TO_WEST:
				map[i][j] = EAST_TO_WEST;
				break;
			case NORTH_TO_EAST:
				map[i][j] = NORTH_TO_EAST;
				break;
			case NORTH_TO_WEST:
				map[i][j] = NORTH_TO_WEST;
				break;
			case EAST_TO_SOUTH:
				map[i][j] = EAST_TO_SOUTH;
				break;
			case WEST_TO_SOUTH:
				map[i][j] = WEST_TO_SOUTH;
				break;
			default:
				map[i][j] = GROUND;
				break;
			}
		}
	}

	enum Pipe current_tile = find_starting_tile(map, start_coord.i, start_coord.j,
												height, width);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < height; j++) {
			enum Pipe tile = map[i][j];
			if (tile == START) {
				tile = current_tile;
			}
			printf("%c", tile);
		}
		printf("\n");
	}
	printf("\n");

	struct Coordinate coordA = { start_coord.i, start_coord.j };
	struct Coordinate coordB = { start_coord.i, start_coord.j };
	enum Direction directionA = derive_direction(current_tile, NONE);
	enum Direction directionB = opposite_direction(current_tile, directionA);
	uint steps = 0;
	printf("DirectionA: %d; DirectionB: %d\n", directionA, directionB);
	do {
		update_coord(&coordA, directionA);
		directionA = derive_direction(map[coordA.i][coordA.j], directionA);

		update_coord(&coordB, directionB);
		directionB = derive_direction(map[coordB.i][coordB.j], directionB);

		steps++;

		//for(int i = 0; i < height; i++) {
		//	for(int j = 0; j < height; j++) {
		//		enum Pipe tile = map[i][j];
		//		if (coordA.i == i && coordA.j == j) {
		//			printf("A");
		//		} else if (coordB.i == i && coordB.j == j) {
		//			printf("B");
		//		} else {
		//			printf("%c", tile);
		//		}
		//	}
		//	printf("\n");
		//}
		//printf("\n");
	} while (coordA.i != coordB.i || coordA.j != coordB.j);

	for(int i = 0; i < height; i++) {
		for(int j = 0; j < height; j++) {
			enum Pipe tile = map[i][j];
			if (coordA.i == i && coordA.j == j) {
				printf("E");
			} else {
				printf("%c", tile);
			}
		}
		printf("\n");
	}
	printf("\n\n");

	printf("Steps: %u\n", steps);

	return 0;
}
