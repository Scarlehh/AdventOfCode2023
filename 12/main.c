#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

#define TRACE 0

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

void *thread_matching_unknown_arrangements(void *vargp) {
	struct SearchSpace *search_space = (struct SearchSpace*) vargp;

	for (int i = search_space->i; i < search_space->range; i++) {
		search_space->matching += matching_unknown_arrangements(search_space->statuses[i],
																search_space->arrangements[i]);
		printf("%u/%u\n", i, search_space->range);
	}
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
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
		//unsigned long long ta = matching_unknown_arrangements(statuses[i], arrangements[i]);
		//printf("Arrangements %u\n\n", ta);
		//total_arrangements += ta;
	}
	printf("\n");

	uint threads = 4;
	pthread_t *thread_id = malloc(threads * sizeof(pthread_t));
	struct SearchSpace *search_space = malloc(threads * sizeof(struct SearchSpace*));
	for (int i = 0; i < threads; i++) {
		search_space[i].statuses = statuses;
		search_space[i].arrangements = arrangements;
		search_space[i].i = (height/threads) * i;
		search_space[i].range = (height/threads) * (i+1);
		if (i+1 == threads) {
			search_space[i].range = height;
		}
		search_space[i].matching = 0;
		printf("Thread %u %u\n", search_space[i].i, search_space[i].range);

		pthread_create(&thread_id[i], NULL, thread_matching_unknown_arrangements, (void *) &search_space[i]);
	}

	for (int i = 0; i < threads; i++) {
		pthread_join(thread_id[i], NULL);
		uint ta = search_space[i].matching;
		printf("Arrangements: %u\n", ta);
		total_arrangements += ta;
	}
	printf("Total arrangements: %u\n", total_arrangements);

	return 0;
}
