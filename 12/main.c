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
	UNKOWN      = '?'
};

// Main
int main() {
	const char **data  = test_input;
	uint height = sizeof(test_input)/sizeof(data[0]);

	enum Status **statuses = malloc(height * sizeof(enum Status*));
	struct Node **arrangements = malloc(height * sizeof(struct Node*));
	for (int i = 0; i < height; i++) {
		uint width  = strlen(data[i]);
		const char *line_data = data[i];
		char *arrangements_data = strstr(line_data, " ")+1;
		uint number_springs = arrangements_data - line_data;

		statuses[i] = malloc(number_springs * sizeof(enum Status));

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
	}

	return 0;
}
