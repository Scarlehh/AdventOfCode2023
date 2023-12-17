#include "data.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRACE 1
#define CYCLES 1000000000

uint compare_platform(char **platformA, char** platformB, uint height) {
	for (int i = 0; i < height; i++) {
		if (strcmp(platformA[i], platformB[i]) != 0) {
			return 0;
		}
	}
	return 1;
}

struct Node {
	struct Node *next;
	char **input;
	char **output;
};

struct Node* append_list(struct Node *head, char **input) {
	if (head == NULL) {
		head = malloc(sizeof(struct Node));
		head->next = NULL;
		head->input = input;
		head->output = NULL;
	} else {
		head->next = append_list(head->next, input);
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

void add_map(struct Node *map, char **input) {
	append_list(map, input);
	if (TRACE) {
		printf("Adding input %p to map\n", input);
	}
}

char **get_map(struct Node *map, char **input) {
	for_each_node(map, node) {
		if (node->input == input) {
			if (TRACE)
				printf("Looked up input %p and found output %p\n", input, node->output);
			return node->output;
		}
	}
	if (TRACE)
		printf("Looked up %p and missed\n", input);
	return NULL;
}

char **find_map(struct Node *map, char **input, uint height) {
	for_each_node(map, node) {
		if (compare_platform(node->input, input, height)) {
			return node->input;
		}
	}
	return NULL;
}

struct Node* update_map(struct Node *map, char **input, char **output) {
	for_each_node(map, node) {
		if (node->input == input) {
			if (TRACE)
				printf("Adding to input %p the output %p\n", input, output);
			node->output = output;
			return node;
		}
	}
}

#define BOULDER 'O'
#define ROCK    '#'
#define GROUND  '.'

enum Direction {
	NORTH = 0,
	WEST,
	SOUTH,
	EAST,
};

char** copy_platform(char **platform, uint height, uint width) {
	char **platform_copy = malloc(height * sizeof(char*));
	for (int i = 0; i < height; i++) {
		platform_copy[i] = malloc(width);
		strcpy(platform_copy[i], platform[i]);
	}
	return platform_copy;
}

void free_platform(char **platform, uint height) {
	for (int i = 0; i < height; i++) {
		free(platform[i]);
	}
	free(platform);
}

void move_boulder(char **platform, int i, int j, int height, int width, enum Direction direction) {
	if (platform[i][j] == BOULDER) {
		platform[i][j] = GROUND;
		while (0 <= i && i < height && 0 <= j && j < width && platform[i][j] == GROUND) {
			switch (direction) {
			case NORTH:
				i--;
				break;
			case WEST:
				j--;
				break;
			case SOUTH:
				i++;
				break;
			case EAST:
				j++;
				break;
			}
		}
		switch (direction) {
		case NORTH:
			platform[i+1][j] = BOULDER;
			break;
		case WEST:
			platform[i][j+1] = BOULDER;
			break;
		case SOUTH:
			platform[i-1][j] = BOULDER;
			break;
		case EAST:
			platform[i][j-1] = BOULDER;
			break;
		}
	}
}

char** spin_platform(char **platform, uint height, uint width, struct Node *platforms) {
	if (TRACE)
		printf("No cached result\n");
	platform = copy_platform(platform, height, width);

	for (enum Direction d = NORTH; d <= WEST; d++) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				move_boulder(platform, i, j, height, width, d);
			}
		}
	}
	for (enum Direction d = SOUTH; d <= EAST; d++) {
		for (int i = height-1; i >= 0; i--) {
			for (int j = width-1; j >= 0; j--) {
				move_boulder(platform, i, j, height, width, d);
			}
		}
	}

	// Close the loop of mappings - everything should cache hit after this
	char **platform_cache = find_map(platforms, platform, height);
	if (platform_cache != NULL) {
		free_platform(platform, height);
		return platform_cache;
	}
	return platform;
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
	unsigned long long cycles = 0;

	char **platform = malloc(height * sizeof(char*));
	for (int i = 0; i < height; i++) {
		platform[i] = malloc(width);
		for (int j = 0; j < width; j++) {
			platform[i][j] = data[i][j];
		}
	}

	struct Node *platform_mappings = append_list(NULL, platform);
	char **loop_beginning = NULL;
	uint loop_size = 1;
	do {
		cycles++;
		if (TRACE)
			print_pattern(platform, height);
		if (TRACE)
			printf("Cycle %llu\n", cycles);

		// Check if we have a cache of the map
		char **new_platform = get_map(platform_mappings, platform);
		if (new_platform == NULL) {
			// Do a manual spin and update our mappings
			new_platform = spin_platform(platform, height, width, platform_mappings);
			update_map(platform_mappings, platform, new_platform);
			add_map(platform_mappings, new_platform);
		} else {
			// Try and close the loop lol
			if (loop_beginning == NULL) {
				loop_beginning = new_platform;
			} else {
				if (new_platform == loop_beginning) {
					if (TRACE)
						printf("Loop is %u\n", loop_size);
					// Big skip and then just finish normally
					cycles += ((CYCLES-cycles) / loop_size) * (loop_size);
				} else {
					loop_size++;
				}
			}
		}
		if (TRACE)
			printf("\n");
		platform = new_platform;
	} while(cycles < CYCLES);

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
