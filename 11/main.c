#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Galaxy {
	uint i;
	uint j;
};

// Lists
struct Node {
	struct Node *next;
	uint value;
	union {
		uint range;
		struct Galaxy galaxy;
	};
};

struct Node* append_list(struct Node *head, uint value, uint range) {
	if (head == NULL) {
		head = malloc(sizeof(struct Node));
		head->next = NULL;
		head->value = value;
		head->range = range;
	} else {
		head->next = append_list(head->next, value, range);
	}
	return head;
}

struct Node* append_galaxy(struct Node *galaxy, uint index, uint i, uint j) {
	if (galaxy == NULL) {
		galaxy = malloc(sizeof(struct Node));
		galaxy->next = NULL;
		galaxy->value = index;
		galaxy->galaxy.i = i;
		galaxy->galaxy.j = j;
	} else {
		galaxy->next = append_galaxy(galaxy->next, index, i, j);
	}
	return galaxy;
}

void free_list(struct Node *head) {
	if (head->next != NULL) {
		free_list(head->next);
	}
	free(head);
}

#define for_each_node(list, item)								\
	for (struct Node *item = list; item; item = item->next)

// Space
#define EMPTY_SPACE '.'
#define GALAXY      '#'

uint distance(uint x, uint y) {
	if (x > y) {
		return x-y;
	}
	return y-x;
}

uint shortest_path(struct Node *galaxies, struct Node *current_galaxy, uint *visited) {
	uint shortest_length = -1;
	visited[current_galaxy->value-1] = 1;
	for_each_node(galaxies, galaxy_pair) {
		if (visited[galaxy_pair->value-1]) {
			continue;
		}

		uint path = 0;
		path += distance(current_galaxy->galaxy.i,
						 galaxy_pair->galaxy.i);
		path += distance(current_galaxy->galaxy.j,
						 galaxy_pair->galaxy.j);

		printf("Steps between galaxies %u and %u is %u\n",
			   current_galaxy->value, galaxy_pair->value,
			   path);

		path += shortest_path(galaxies, galaxy_pair, visited);
		if (path < shortest_length) {
			shortest_length = path;
		}
	}
	visited[current_galaxy->value-1] = 0;
	printf("Shortest path is %u\n", shortest_length);
	return shortest_length;
}

uint sum_of_paths(struct Node *galaxies, struct Node *current_galaxy, uint *visited) {
	uint path = 0;
	for_each_node(galaxies, galaxy_pair) {
		if (visited[galaxy_pair->value-1]) {
			continue;
		}

		path += distance(current_galaxy->galaxy.i,
						 galaxy_pair->galaxy.i);
		path += distance(current_galaxy->galaxy.j,
						 galaxy_pair->galaxy.j);

		printf("Steps between galaxies %u and %u is %u\n",
			   current_galaxy->value, galaxy_pair->value,
			   path);
	}
	return path;
}

// Main
int main() {
	const char **data  = test_input;
	uint height = sizeof(test_input)/sizeof(data[0]);
	uint width  = strlen(data[0]);
	printf("height %d width %d\n", height, width);
	uint expansion_multiplier = 1;

	// Get galaxies
	struct Node *galaxies = NULL;
	uint number_galaxies = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (data[i][j] == GALAXY) {
				galaxies = append_galaxy(galaxies, ++number_galaxies, i, j);
			}
		}
	}

	// Figure out which rows and columns to expand
	struct Node *rows_to_expand = NULL;
	struct Node *columns_to_expand = NULL;
	uint expanded_height = height;
	uint expanded_width = width;
	for (int i = 0; i < height; i++) {
		uint expand = 1;
		for_each_node(galaxies, galaxy) {
			if (galaxy->galaxy.i == i) {
				expand = 0;
			}
		}
		if (expand) {
			expanded_height += expansion_multiplier;
			rows_to_expand = append_list(rows_to_expand, i, expansion_multiplier);
		}
	}
	for (int j = 0; j < width; j++) {
		uint expand = 1;
		for_each_node(galaxies, galaxy) {
			if (galaxy->galaxy.j == j) {
				expand = 0;
			}
		}
		if (expand) {
			expanded_width += expansion_multiplier;
			columns_to_expand = append_list(columns_to_expand, j, expansion_multiplier);
		}
	}

	printf("Expand to %u x %u\n", expanded_height, expanded_width);

	// Populate the expanded space map
	char **expanded_map = malloc(expanded_height * sizeof(char*));
	struct Node *current_row = rows_to_expand;
	struct Node *current_col = columns_to_expand;
	struct Node *current_galaxy = galaxies;
	for (int i = 0, expanded_i = 0; i < height; i++, expanded_i++) {
		expanded_map[expanded_i] = malloc(expanded_width * sizeof(char));

		for (int j = 0, expanded_j = 0; j < width; j++, expanded_j++) {
			expanded_map[expanded_i][expanded_j] = data[i][j];
			if (current_col && current_col->value == j) {
				j--;
				current_col->range--;
				if (current_col->range == 0) {
					current_col->range = expansion_multiplier;
					current_col = current_col->next;
				}
			}

			// Adjust galaxy position due to expansion
			if (current_galaxy &&
				i == current_galaxy->galaxy.i &&
				j == current_galaxy->galaxy.j) {
				current_galaxy->galaxy.i = expanded_i;
				current_galaxy->galaxy.j = expanded_j;
				expanded_map[expanded_i][expanded_j] = current_galaxy->value + '0';
				current_galaxy = current_galaxy->next;
			}
		}

		current_col = columns_to_expand;
		if (current_row && current_row->value == i) {
			i--;
			current_row->range--;
			if (current_row->range == 0) {
				current_row->range = expansion_multiplier;
				current_row = current_row->next;
			}
		}
	}
	free_list(rows_to_expand);
	free_list(columns_to_expand);

	// Print expanded map
	for (int i = 0; i < expanded_height; i++) {
		printf("%s\n", expanded_map[i]);
	}

	uint *galaxies_visited = calloc(number_galaxies, sizeof(uint));
	//uint path = shortest_path(galaxies, galaxies, galaxies_visited);
	uint path = 0;
	for_each_node(galaxies, galaxy) {
		galaxies_visited[galaxy->value-1] = 1;
		path += sum_of_paths(galaxies, galaxy, galaxies_visited);
	}

	printf("Shortest Path is %u\n", path);

	return 0;
}
