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

	uint correct_seed = 15880236;

	printf("Initial seeds: ");
	for_each_node(seeds, seed) {
		printf("%u-%u; ", seed->value, seed->value+seed->range);
	}
	printf("\n\n");

	// Start from first map
	uint number_passes = 0;
	uint updates = 1;
	uint map_start = 2;
	for (int i = map_start; i < height; i++) {
		const char *line_data = data[i];

		// Processing a map
		if (isdigit(line_data[0])) {
			uint destination;
			uint source;
			uint range;

			sscanf(line_data, "%d %d %d", &destination, &source, &range);

			for_each_node(seeds, seed) {
				if (!seed->update) {
					continue;
				}
				if (source <= seed->mapping && seed->mapping < source + range) {
					if (number_passes == 0) {
						// Split out any mappings
						if ((seed->mapping + seed->range) > source + range) {
							printf("%u-%u > %u-%u so ",
								   seed->mapping, seed->mapping + seed->range,
								   source, source + range);
							uint new_range = (seed->mapping + seed->range) - (source + range);
							split_seeds(seeds, seed, seed->range - new_range);
							updates++;
						}
					}
					// Update on the second pass
					else if (number_passes == 1) {
						uint old_mapping = seed->mapping;
						seed->mapping = destination + (seed->mapping - source);
						seed->update = 0;
						printf("Seed %u (%u) gets mapping to %u\n", seed->value, old_mapping, seed->mapping);
					}
				}
				if (number_passes == 0) {
					if (seed->mapping < source && seed->mapping + seed->range > source) {
						split_seeds(seeds, seed, source - seed->mapping);
						updates++;
					}
				}
			}
		} else {
			if (number_passes == 0) {
				// Once we stop splitting out seed ranges, process the mappings
				if (updates == 0) {
					number_passes++;
				}
				updates = 0;
				i = map_start;
			} else if (number_passes == 1) {
				// Finished mapping, set ready to update
				for_each_node(seeds, seed) {
					seed->update = 1;
				}
				i++;
				number_passes = 0;
				map_start = i;

				printf("Seeds: ");
				for_each_node(seeds, seed) {
					printf("%u-%u (%u-%u); ",
						   seed->value, seed->value+seed->range,
						   seed->mapping, seed->mapping+seed->range);
				}
				printf("\n\n");
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

	return 0;
}
