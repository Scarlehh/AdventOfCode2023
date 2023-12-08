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

#define for_each_node(list, item)								\
	for (struct Node *item = list; item; item = item->next)

#define for_each_node_set(list1, item1, list2, item2)			 \
	for (struct Node *item1 = list1, *item2 = list2;			 \
		 item1 && item2;										 \
		 item1 = item1->next, item2 = item2->next)

unsigned long get_data(const char *data) {
	unsigned long d=0;
	for (char *line_data = strstr(data, ":")+1;
		 line_data[0] != '\0';
		 line_data++) {

		if (isdigit(line_data[0])) {
			d *= 10;
			d += line_data[0]-'0';
		}
	}
	return d;
}

int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);

	unsigned long time = get_data(data[0]);
	unsigned long distance = get_data(data[1]);

	printf("Time %u\nDistance %lu\n", time, distance);
	printf("\n\n");

	uint possible = 0;
	for (uint speed = 0; speed < time; speed++) {
		unsigned long time_left = time - speed;
		unsigned long distance_travelled = speed * time_left;

		if (distance_travelled > distance) {
			//printf("Possible by holding for %u ms\n", speed);
			possible++;
		}
	}

	uint margin = possible;
	printf("Margin: %u\n", margin);

	return 0;
}
