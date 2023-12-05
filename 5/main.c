#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Node {
	struct Node *next;
	uint value;
	uint mapping;
	uint update;
};

struct Node* append_list(struct Node *head, int value) {
	if (head == NULL) {
		head = malloc(sizeof(struct Node));
		head->next = NULL;
		head->value = value;
		// Set default map to self
		head->mapping = value;
		head->update = 1;
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

int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
	struct Node *seeds;
	// Get seeds
	for (char *line_data = strstr(data[0], ":");
		 line_data != NULL;
		 line_data = strstr(line_data, " ")) {
		line_data++;

		if (isdigit(line_data[0])) {
			int number;
			sscanf(line_data, "%d", &number);
			seeds = append_list(seeds, number);
		}
	}

	printf("Seeds: ");
	for_each_node(seeds, seed) {
		printf("%d ", seed->value);
	}
	printf("\n");

	// Start from first map
	struct Node *current_map;
	for (int i = 2; i < height; i++) {
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
				if (source <= seed->mapping && seed->mapping < source+range) {
					seed->mapping = destination + (seed->mapping - source);
					seed->update = 0;
					//printf("Seed %d gets mapping to %d\n", seed->value, seed->mapping);
				}
			}
		} else {
			// Finished mapping, set ready to update
			for_each_node(seeds, seed) {
				seed->update = 1;
			}
			i++;
		}
	}

	uint lowest_destination = -1;
	for_each_node(seeds, seed) {
		if (seed->mapping < lowest_destination) {
			lowest_destination = seed->mapping;
		}
	}
	printf("Lowest destination: %d\n", lowest_destination);

	return 0;
}
