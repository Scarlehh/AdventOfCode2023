#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRACE 0

// Lists
struct Node {
	struct Node *next;
	int value;
	int output;
};

struct Node* append_list(struct Node *head, int value) {
	if (head == NULL) {
		head = malloc(sizeof(struct Node));
		head->next = NULL;
		head->value = value;
		head->output = 0;
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

#define MAP_SIZE 1024

uint hash(char *str, uint meta) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	hash = (hash << 4) + meta;

    return hash % MAP_SIZE;
}

uint str_meta_enc(char *str, uint meta) {
	uint enc = 0;
	char c;
	while (c = *str++) {
		if (c == OPERATIONAL) {
			enc |= 0x1;
		} else if (c == DAMAGED) {
			enc |= 0x2;
		} else if (c == UNKNOWN) {
			enc |= 0x3;
		}
		enc << 2;
	}
	enc = (enc << 4) + meta;
	return enc;
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

struct Node* add_map(struct Map *map, char **input, uint meta) {
	uint key = hash(input, meta);
	uint enc = str_meta_enc(input, meta);
	map->mappings[key] = append_list(map->mappings[key], enc);
	if (TRACE) {
		printf("Adding %s %u to map\n", input, meta);
	}
	return map->mappings[key];
}

char **get_map(struct Map *map, char **input, uint meta) {
	uint key = hash(input, meta);
	uint enc = str_meta_enc(input, meta);
	for_each_node(map->mappings[key], node) {
		if (node->value == enc) {
			if (TRACE)
				printf("Looked up %p and found %p\n", input, node->output);
			return node->output;
		}
	}
	if (TRACE)
		printf("Looked up %p and missed\n", input);
	return NULL;
}

struct Node* update_map(struct Map *map, char **input, uint meta, uint output) {
	uint key = hash(input, meta);
	uint enc = str_meta_enc(input, meta);
	for_each_node(map->mappings[key], node) {
		if (node->value == enc) {
			if (TRACE)
				printf("Adding result %u to %s %u\n", output, input, meta);
			node->output = output;
			return node;
		}
	}
}

uint consecutively_damaged(char *statuses, uint damaged_amount, uint ignore_unknown) {
	uint consecutive = 0;
	for (int i = 0; statuses[i] && i < damaged_amount; i++) {
		if (ignore_unknown && statuses[i] == DAMAGED) {
			consecutive++;
		} else if (!ignore_unknown && statuses[i] != OPERATIONAL) {
			consecutive++;
		}
	}
	if (consecutive == damaged_amount) {
		return 1;
	}
	return 0;
}

int matching_arrangement(char *statuses, struct Node *arrangement) {
	if (consecutively_damaged(statuses, arrangement->value, 0)) {
		if (statuses[arrangement->value] == DAMAGED) {
			if (TRACE)
				printf("Match not found -- after %u is damaged %s\n", arrangement->value, statuses);
			return -1;
		}
		if (TRACE)
			printf("Match found\n");
		return 1;
	}
	if (TRACE)
		printf("Match not found -- next consecutive damage is not %u\n", arrangement->value);
	return 0;
}

unsigned long long matching_unknown_arrangements(char *statuses, struct Node *arrangements) {
	unsigned long long matching = 0;

	for (int i = 0; statuses[i]; i++) {
		if (!arrangements) {
			if (consecutively_damaged(statuses+i, 1, 1)) {
				if (TRACE)
					printf("Match not found -- consecutive after arrangements are processed\n");
				return matching;
			}
		}
		else if (statuses[i] == DAMAGED) {
			if (matching_arrangement(statuses+i, arrangements) == 1) {
				i += arrangements->value;
				arrangements = arrangements->next;
			} else {
				return matching;
			}
		} else if (statuses[i] == UNKNOWN) {
			statuses[i] = DAMAGED;
			if (matching_arrangement(statuses+i, arrangements) == 1) {
				uint jump = arrangements->value+1;
				matching += matching_unknown_arrangements(statuses+i+jump,
														  arrangements->next);
			}

			statuses[i] = OPERATIONAL;
			matching += matching_unknown_arrangements(statuses+i+1, arrangements);

			statuses[i] = UNKNOWN;
			break;
		}
	}
	if (arrangements) {
		if (TRACE)
			printf("Match not found -- arrangements left\n");
		return matching;
	}

	return 1;
}

struct SearchSpace {
	char **statuses;
	struct Node **arrangements;
	uint i;
	uint range;
	uint matching;
};

// Main
int main() {
	const char **data  = test0_input;
	uint height = sizeof(test0_input)/sizeof(data[0]);
	uint replacements = 5;

	char **statuses = malloc(height * sizeof(char*));
	struct Node **arrangements = malloc(height * sizeof(struct Node*));
	for (int i = 0; i < height; i++) {
		uint width  = strlen(data[i]);
		const char *line_data = data[i];
		char *arrangements_data = strstr(line_data, " ")+1;
		uint number_springs = arrangements_data - line_data - 1;
		uint unfolded_length = (number_springs * replacements) + replacements;

		statuses[i] = malloc(unfolded_length * sizeof(char));

		for (int r = 0; r < replacements; r++) {
			for (int j = 0; j < number_springs; j++) {
				statuses[i][(r*(number_springs+1))+j] = line_data[j];
			}
			statuses[i][(r*(number_springs+1)+number_springs)] = UNKNOWN;
		}
		statuses[i][unfolded_length-1] = '\0';

		arrangements[i] = NULL;
		for (int r = 0; r < replacements; r++) {
			for (const char *line_data = strstr(data[i], " ");
				 line_data != NULL;
				 line_data = strstr(line_data, ",")) {
				line_data++;

				if (isdigit(line_data[0])) {
					uint arrangement;
					sscanf(line_data, "%u", &arrangement);
					arrangements[i] = append_list(arrangements[i], arrangement);
				}
			}
		}
	}

	unsigned long long total_arrangements = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; statuses[i][j]; j++) {
			printf("%c", statuses[i][j]);
		}
		printf(" ");
		for_each_node(arrangements[i], a) {
			printf("%u ", a->value);
		}
		printf("\n");
		unsigned long long ta = matching_unknown_arrangements(statuses[i], arrangements[i]);
		printf("Arrangements %u\n\n", ta);
		total_arrangements += ta;
	}
	printf("\n");

	printf("Total arrangements: %u\n", total_arrangements);

	return 0;
}
