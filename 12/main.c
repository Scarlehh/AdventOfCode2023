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

enum Status {
	OPERATIONAL = '.',
	DAMAGED     = '#',
	UNKNOWN      = '?'
};

uint consecutively_damaged(char *statuses, uint damaged_amount) {
	uint consecutive = 0;
	for (int i = 0; statuses[i] && i < damaged_amount; i++) {
		if (statuses[i] != OPERATIONAL) {
			consecutive++;
		}
	}
	if (consecutive == damaged_amount) {
		return 1;
	}
	return 0;
}

uint matching_arrangements(char *statuses, struct Node *arrangements) {
	int i;
	for (i = 0; statuses[i] && arrangements; i++) {
		if (statuses[i] != DAMAGED) {
			continue;
		}
		if (consecutively_damaged(statuses+i, arrangements->value)) {
			printf("Position %d is damaged %u times\n", i, arrangements->value);
			i += arrangements->value;
			arrangements = arrangements->next;
			if (statuses[i] == DAMAGED) {
				printf("Match not found -- next is damaged\n");
				return 0;
			}
		} else {
			printf("Match not found -- next consecutive damage is not %u\n", arrangements->value);
			return 0;
		}
	}
	// Check we've used all the nodes, and there are no mode possible matches
	if (!arrangements && (!statuses[i] || !consecutively_damaged(statuses+i, 1))) {
		printf("Match found\n");
		return 1;
	}
	printf("Match not found -- arrangements left\n");
	return 0;
}

void populate_unknowns(char *statuses, uint start) {
	uint unknowns;
	for (int i = start; statuses[i]; i++) {
		if (statuses[i] == UNKNOWN) {
			unknowns++;

			statuses[i] = DAMAGED;
			populate_unknowns(statuses, i);

			statuses[i] = OPERATIONAL;
			populate_unknowns(statuses, i);

			statuses[i] = UNKNOWN;
		}
	}
	if (!unknowns) {
		printf("%s\n", statuses);
	}
}

// Main
int main() {
	const char **data  = bad_input;
	uint height = sizeof(bad_input)/sizeof(data[0]);

	char **statuses = malloc(height * sizeof(char*));
	struct Node **arrangements = malloc(height * sizeof(struct Node*));
	for (int i = 0; i < height; i++) {
		uint width  = strlen(data[i]);
		const char *line_data = data[i];
		char *arrangements_data = strstr(line_data, " ")+1;
		uint number_springs = arrangements_data - line_data;

		statuses[i] = malloc(number_springs * sizeof(char));

		for (int j = 0; j < number_springs; j++) {
			statuses[i][j] = line_data[j];
		}
		statuses[i][number_springs-1] = '\0';

		for (const char *line_data = arrangements_data;
			 line_data - 1 != NULL;
			 line_data = strstr(line_data, ",")+1) {

			if (isdigit(line_data[0])) {
				uint arrangement;
				sscanf(line_data, "%u", &arrangement);
				arrangements[i] = append_list(arrangements[i], arrangement);
			}
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; statuses[i][j]; j++) {
			printf("%c", statuses[i][j]);
		}
		printf(" ");
		for_each_node(arrangements[i], a) {
			printf("%u ", a->value);
		}
		printf("\n");
		populate_unknowns(statuses[i], 0);

		matching_arrangements(statuses[i], arrangements[i]);

		printf("\n\n");
	}

	return 0;
}
