#include "data.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRACE 1

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

#define MAP_SIZE 1024

uint32_t hash(uint32_t a) {
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a % MAP_SIZE;
}

struct Map {
	struct Node *mappings[MAP_SIZE];
};

struct Map *init_map() {
	struct Map *map = malloc(sizeof(struct Map));
	for (int i = 0; i < MAP_SIZE; i++) {
		map->mappings[i] = NULL;
	}
	return map;
}

struct Node* add_map(struct Map *map, char **input) {
	uint key = hash(input);
	map->mappings[key] = append_list(map->mappings[key], input);
	if (TRACE) {
		printf("Adding %p to map\n", input);
	}
	return map->mappings[key];
}

char **get_map(struct Map *map, char **input) {
	uint key = hash(input);
	for_each_node(map->mappings[key], node) {
		if (node->input == input) {
			if (TRACE)
				printf("Looked up %p and found %p\n", input, node->output);
			return node->output;
		}
	}
	if (TRACE)
		printf("Looked up %p and missed\n", input);
	return NULL;
}

char **find_map(struct Map *map, char **input, uint height) {
	for (int i = 0; i < MAP_SIZE; i++) {
		for_each_node(map->mappings[i], node) {
			if (compare_platform(node->input, input, height)) {
				if (TRACE)
					printf("Found a match!\n");
				return node->input;
			}
		}
	}
	return NULL;
}

struct Node* update_map(struct Map *map, char **input, char **output) {
	uint key = hash(input);
	for_each_node(map->mappings[key], node) {
		if (node->input == input) {
			if (TRACE)
				printf("Adding %p to %p\n", input, output);
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

char** spin_platform(char **platform, uint height, uint width, struct Map *platforms) {
	char **platform_cache = get_map(platforms, platform);
	if (platform_cache != NULL) {
		return platform_cache;
	}

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
	platform_cache = find_map(platforms, platform, height);
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
	const char **data  = test_input;
	uint height = sizeof(test_input)/sizeof(data[0]);
	uint width = strlen(data[0]);
	unsigned long long cycles = 1000000000;

	char **platform = malloc(height * sizeof(char*));
	for (int i = 0; i < height; i++) {
		platform[i] = malloc(width);
		for (int j = 0; j < width; j++) {
			platform[i][j] = data[i][j];
		}
	}

	struct Map *platform_mappings = init_map();
	char **loop_beginning = NULL;
	uint loop_size = 0;
	uint loop_closed = 0;
	add_map(platform_mappings, platform);
	do {
		if (TRACE)
			print_pattern(platform, height);

		if (loop_closed && ((cycles % loop_size) == 0)) {
			break;
		}

		char **new_platform = spin_platform(platform, height, width, platform_mappings);
		if (get_map(platform_mappings, platform) == NULL) {
			update_map(platform_mappings, platform, new_platform);
			add_map(platform_mappings, new_platform);
		} else {
			// Try and close the loop lol
			if (loop_beginning == NULL) {
				loop_beginning = new_platform;
			} else {
				if (new_platform == loop_beginning) {
					loop_closed = 1;
					printf("Loop is %u\n", loop_size);
				} else if (!loop_closed) {
					loop_size++;
				}
			}
		}
		platform = new_platform;
		cycles--;

		if (TRACE)
			printf("Cycles %llu\n\n", cycles);
	} while(cycles > 0);

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
