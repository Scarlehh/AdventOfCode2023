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

uint history_difference(struct Node *report) {
	struct Node *differences = NULL;

	int difference = report->value;
	uint all_zero = 1;
	for_each_node(report->next, history) {
		if (difference) {
			all_zero = 0;
		}

		difference = history->value - difference;

		differences = append_list(differences, difference);
		difference = history->value;
	}

	int next = 0;
	if (!all_zero) {
		next = history_difference(differences);
		next += difference;
	}

	if (differences) {
		free_list(differences);
	}

	return next;
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);

	int *predictions = malloc(height * sizeof(uint));

	// Get the directions first
	struct Node *report = NULL;
	for (int i = 0; i < height; i++) {
		for (const char *line_data = data[i];
			 line_data - 1 != NULL;
			 line_data = strstr(line_data, " ")+1) {

			if (isdigit(line_data[0]) || line_data[0] == '-') {
				int reading;
				sscanf(line_data, "%u", &reading);
				report = append_list(report, reading);
			}
		}

		predictions[i] = history_difference(report);
		free_list(report);
		report = NULL;
	}

	int predictions_sum = 0;
	for(int i = 0; i < height; i++) {
		predictions_sum += predictions[i];
	}
	free(report);
	printf("Sum of predictions is %u\n", predictions_sum);

	return 0;
}
