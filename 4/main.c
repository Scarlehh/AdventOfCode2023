#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int main() {
	const char **data = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width = strlen(data[0]);

	uint total = 0;

	for (int i = 0; i < height; i++) {
		struct Node *winning_numbers;
		struct Node *owned_numbers;
		struct Node *populating_list = NULL;

		for (char *line_data = strstr(data[i], ":");
			line_data != NULL;
			line_data = strstr(line_data, " ")) {
			line_data++;

			if (isdigit(line_data[0])) {
				int number;
				sscanf(line_data, "%d", &number);
				populating_list = append_list(populating_list, number);
			}
			if (line_data[0] == '|') {
				winning_numbers = populating_list;
				populating_list = NULL;
			}
		}
		owned_numbers = populating_list;

		uint winnings_total = 0;
		for (struct Node *owned = owned_numbers; owned; owned = owned->next) {
			for (struct Node *win = winning_numbers; win; win = win->next) {
				if (owned->value == win->value) {
					winnings_total = winnings_total ? winnings_total*2 : 1;
				}
			}
		}
		total += winnings_total;
	}
	printf("Total: %d\n", total);

	return 0;
}
