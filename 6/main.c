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

struct Node* get_data(const char *data) {
	struct Node *nodes = NULL;
	for (char *line_data = strstr(data, ":")+1;
		 line_data != NULL;
		 line_data = strstr(line_data, " ")) {
		line_data++;

		if (isdigit(line_data[0])) {
			uint number;
			sscanf(line_data, "%u", &number);
			nodes = append_list(nodes, number);
		}
	}
	return nodes;
}

int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);

	struct Node *times = get_data(data[0]);
	struct Node *distances = get_data(data[1]);

	printf("Times\tDistances\n");
	for_each_node_set(times, time, distances, distance) {
		printf("%u\t%u\n", time->value, distance->value);
	}
	printf("\n\n");

	struct Node *possibilities = NULL;
	for_each_node_set(times, time, distances, distance) {
		uint possible = 0;
		for (uint speed = 0; speed < time->value; speed++) {
			uint time_left = time->value - speed;
			uint distance_travelled = speed * time_left;

			if (distance_travelled > distance->value) {
				printf("Possible by holding for %u ms\n", speed);
				possible++;
			}
		}
		printf("%u possibilities with time %u and record %u\n\n",
			   possible, time->value, distance->value);
		possibilities = append_list(possibilities, possible);
	}

	uint margin = 1;
	for_each_node(possibilities, possibility) {
		margin *= possibility->value;
	}
	printf("Margin: %u\n", margin);

	return 0;
}
