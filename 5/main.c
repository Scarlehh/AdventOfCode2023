#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Node {
	struct Node *next;
	uint value;
	uint mapping;
	uint range;
	uint update;
};

struct Node* append_list(struct Node *head, uint value, uint map, uint range) {
	if (head == NULL) {
		head = malloc(sizeof(struct Node));
		head->next = NULL;
		head->value = value;
		head->range = range;
		head->mapping = map;
		// Set default map to self
		head->update = 1;
	} else {
		head->next = append_list(head->next, value, map, range);
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

void split_seeds(struct Node *seeds, struct Node *seed, uint new_range) {
	printf("splitting %u-%u (%u-%u) into ",
		   seed->value, seed->value + seed->range,
		   seed->mapping, seed->mapping + seed->range);

	append_list(seeds,
				seed->value + new_range,
				seed->mapping + new_range,
				seed->range - new_range);

	uint old_range = seed->range;
	seed->range = new_range;

	printf("%u-%u (%u-%u) and %u-%u (%u-%u)\n",
		   seed->value, seed->value + seed->range,
		   seed->mapping, seed->mapping + seed->range,
		   seed->value + seed->range, seed->value + old_range,
		   seed->mapping + seed->range, seed->mapping + old_range);
}

int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
	struct Node *seeds = NULL;
	// Get seeds
	for (char *line_data = strstr(data[0], ":")+1;
		 line_data != NULL;
		 line_data = strstr(line_data, " ")) {
		line_data++;

		if (isdigit(line_data[0])) {
			uint number;
			uint range;
			sscanf(line_data, "%u %u", &number, &range);
			seeds = append_list(seeds, number, number, range);
		}

		// Skip an entry
		line_data = strstr(line_data, " ");
		if (!line_data) {
			break;
		} else {
			line_data++;
		}
	}

	printf("Initial seeds: ");
	for_each_node(seeds, seed) {
		printf("%u-%u; ", seed->value, seed->value+seed->range);
	}
	printf("\n");

	// Start from first map
	struct Node *mappings = NULL;
	for (int i = 2; i < height; i++) {
		const char *line_data = data[i];

		// Processing a map
		if (isdigit(line_data[0])) {
			uint destination;
			uint source;
			uint range;

			sscanf(line_data, "%d %d %d", &destination, &source, &range);
			mappings = append_list(mappings, source, destination, range);
		} else {
			// Split out any seeds ranges that overflow from themappings
			for_each_node(mappings, map) {
				for_each_node(seeds, seed) {
					// Start of seed range is within the mapping
					if ((map->value <= seed->mapping) &&
						(seed->mapping < map->value + map->range)) {
						// End of the seed ranges is larger than the mapping range
						if (seed->mapping + seed->range > map->value + map->range) {
							split_seeds(seeds, seed, map->value + map->range - seed->mapping);
						}
					}
					// Start of the seed ranges isn't within the mapping range
					if ((seed->mapping < map->value) &&
						(map->value < seed->mapping + seed->range)) {
						split_seeds(seeds, seed, map->value - seed->mapping);
					}
				}
			}


			// Process the mappings
			for_each_node(mappings, map) {
				for_each_node(seeds, seed) {
					if (!seed->update) {
						continue;
					}
					// If the seed is within the mapping then update the destination.
					// No need to check the upper bound because we already split the
					// seeds previously.
					if ((map->value <= seed->mapping) &&
						(seed->mapping < map->value + map->range)) {
						uint old_mapping = seed->mapping;
						seed->mapping = map->mapping + (seed->mapping - map->value);
						seed->update = 0;
						printf("Seed %u (%u) gets mapped to %u from %u (%u)\n",
							   seed->value, old_mapping, seed->mapping, map->value, map->mapping);
					}
				}
			}
			printf("\n");

			for_each_node(seeds, seed) {
				seed->update = 1;
			}

			i++;

			if (mappings) {
				free_list(mappings);
				mappings = NULL;
			}
		}
	}

	uint lowest_destination = -1;
	for_each_node(seeds, seed) {
		printf("Seed: %u-%u (%u-%u)\n",
			   seed->value, seed->value+seed->range,
			   seed->mapping, seed->mapping+seed->range);
		if (seed->mapping < lowest_destination) {
			lowest_destination = seed->mapping;
		}
	}
	printf("\nLowest destination: %u\n", lowest_destination);

	free_list(seeds);

	return 0;
}
