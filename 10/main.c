#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Stack
struct Node {
	struct Node *previous;
	int i;
	int j;
};

struct Node* push(struct Node *previous, int i, int j) {
	struct Node *stack = malloc(sizeof(struct Node));
	stack->previous = previous;
	stack->i = i;
	stack->j = j;
	return stack;
}

struct Node *pop(struct Node *stack) {
	struct Node *previous = stack->previous;
	free(stack);
	return previous;
}

void free_stack(struct Node *stack) {
	if (stack->previous != NULL) {
		free_stack(stack->previous);
	}
	pop(stack);
}

// Map structures
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
	GROUND         = '.',
	JUNK           = '#'
};

struct Coordinate {
	uint i; // y
	uint j; // x
};

// Direction functionality
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

// Pipe/tile functionality
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

// Coord helper
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
	printf("height %d width %d\n", height, width);

	struct Coordinate start_coord;
	enum Pipe **map  = malloc(height * sizeof(enum Pipe*));
	enum Pipe **path = malloc(height * sizeof(enum Pipe*));

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
			path[i] = malloc(width * sizeof(enum Pipe));
			path[i][j] = map[i][j];
		}
	}

	enum Pipe current_tile = find_starting_tile(map, start_coord.i, start_coord.j,
												height, width);
	map[start_coord.i][start_coord.j] = current_tile;

	// Print starting map
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			enum Pipe tile = map[i][j];
			if (tile == START) {
				tile = current_tile;
			}
			printf("%c", tile);
		}
		printf("\n");
	}
	printf("\n");

	// Find the path
	struct Coordinate coord = { start_coord.i, start_coord.j };
	enum Direction direction = derive_direction(current_tile, NONE);
	do {
		update_coord(&coord, direction);
		direction = derive_direction(map[coord.i][coord.j], direction);

		path[coord.i][coord.j] = START;
	} while (coord.i != start_coord.i || coord.j != start_coord.j);

	// Process the map to convert junk pipes to ground
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if (path[i][j] != START) {
				if (map[i][j] != GROUND) {
					map[i][j] = GROUND;
				}
			}
		}
		free(path[i]);
	}
	free(path);

	// Expand the map
	int expanded_map_height = (height*2)-1;
	int expanded_map_width = (width*2)-1;
	enum Pipe **expanded_map = malloc(expanded_map_height * sizeof(enum Pipe*));
	for (int i = 0, map_i = 0; i < height; i++, map_i += 2) {
		expanded_map[map_i] = malloc(expanded_map_width * sizeof(enum Pipe));
		expanded_map[map_i+1] = malloc(expanded_map_width * sizeof(enum Pipe));

		for (int j = 0, map_j = 0; j < width; j++, map_j += 2) {
			enum Pipe tile = map[i][j];

			expanded_map[map_i][map_j] = map[i][j];
			if (tile == GROUND ||
				tile == NORTH_TO_WEST) {
				expanded_map[map_i+1][map_j] = GROUND;
				expanded_map[map_i][map_j+1] = GROUND;
				expanded_map[map_i+1][map_j+1] = GROUND;
			}
			if (tile == NORTH_TO_SOUTH ||
				tile == WEST_TO_SOUTH) {
				expanded_map[map_i+1][map_j] = NORTH_TO_SOUTH;
				expanded_map[map_i][map_j+1] = GROUND;
				expanded_map[map_i+1][map_j+1] = GROUND;
			}
			if (tile == EAST_TO_WEST ||
				tile == NORTH_TO_EAST) {
				expanded_map[map_i+1][map_j] = GROUND;
				expanded_map[map_i][map_j+1] = EAST_TO_WEST;
				expanded_map[map_i+1][map_j+1] = GROUND;
			}
			if (tile == EAST_TO_SOUTH) {
				expanded_map[map_i+1][map_j] = NORTH_TO_SOUTH;
				expanded_map[map_i][map_j+1] = EAST_TO_WEST;
				expanded_map[map_i+1][map_j+1] = GROUND;
			}
		}
		expanded_map[map_i][(width*2)-1] = '\0';
		expanded_map[map_i+1][(width*2)-1] = '\0';
	}

	struct Node *adjacent = push(NULL, 0, 0);
	// Get initial edge points to fill
	for (int i = 1; i < expanded_map_height; i++) {
		if (expanded_map[i][0] == GROUND) {
			adjacent = push(adjacent, i, 0);
		}
		if (expanded_map[i][expanded_map_width-1] == GROUND) {
			adjacent = push(adjacent, i, expanded_map_width-1);
		}
	}
	for (int j = 1; j < expanded_map_width; j++) {
		if (expanded_map[0][j] == GROUND) {
			adjacent = push(adjacent, 0, j);
		}
		if (expanded_map[expanded_map_height-1][j] == GROUND) {
			adjacent = push(adjacent, expanded_map_height-1, j);
		}
	}
	// Flood fill
	while (adjacent) {
		int i = adjacent->i;
		int j = adjacent->j;

		expanded_map[i][j] = JUNK;
		adjacent = pop(adjacent);

		// Check east
		if (j+1 < expanded_map_width && expanded_map[i][j+1] == GROUND) {
			adjacent = push(adjacent, i, j+1);
		}
		// Check south
		if (i+1 < expanded_map_height && expanded_map[i+1][j] == GROUND) {
			adjacent = push(adjacent, i+1, j);
		}
		// Check south-east
		if (i+1 < expanded_map_height && j+1 < expanded_map_width &&
			expanded_map[i+1][j+1] == GROUND) {
			adjacent = push(adjacent, i+1, j+1);
		}

		// Check west
		if (j-1 >= 0 && expanded_map[i][j-1] == GROUND) {
			adjacent = push(adjacent, i, j-1);
		}
		// Check north
		if (i-1 >= 0 && expanded_map[i-1][j] == GROUND) {
			adjacent = push(adjacent, i-1, j);
		}
	}

	uint enclosed_ground = 0;
	for(int i = 0; i < expanded_map_height; i+=2) {
		for(int j = 0; j < expanded_map_width; j+=2) {
			enum Pipe tile = expanded_map[i][j];
			if (tile == GROUND) {
				enclosed_ground++;
			}
			printf("%c", tile);
		}
		printf("\n");
	}
	printf("\n\nEnclosed ground: %u\n", enclosed_ground);

	return 0;
}
