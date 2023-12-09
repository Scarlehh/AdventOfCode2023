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

// Network
enum Direction {
	LEFT = 0,
	RIGHT
};

#define ELEMENT_STRING 3

struct Element {
	char element[ELEMENT_STRING];
	uint left;
	uint right;
};

uint element_to_index(struct Element **network, uint length, const char *element) {
	for (int i = 0; i < length; i++) {
		if (strncmp(network[i]->element, element, ELEMENT_STRING) == 0) {
			return i;
		}
	}
	return -1;
}

uint get_next_element_index(struct Element **network, uint index,
							enum Direction direction) {
	if (direction == LEFT) {
		return network[index]->left;
	}
	return network[index]->right;
}

int main() {
	const char **data  = test1_input;
	uint height = sizeof(test1_input)/sizeof(data[0]);

	// Get the directions first
	struct Node *directions = NULL;
	for(int i = 0; data[0][i] != '\0'; i++) {
		if (data[0][i] == 'L') {
			directions = append_list(directions, LEFT);
		} else {
			directions = append_list(directions, RIGHT);
		}
	}

	for_each_node(directions, dir) {
		if (dir->value == LEFT) {
			printf("L");
		} else {
			printf("R");
		}
	}
	printf("\n\n");

	// Get the initial network map
	uint network_length = height-2;
	struct Element **network = malloc(network_length * sizeof(struct Element*));
	uint number_current_elements = 0;
	for(int i = 0; i < network_length; i++) {
		const char *line_data = data[i+2];

		network[i] = malloc(sizeof(struct Element));
		for(int j = 0; j < ELEMENT_STRING; j++) {
			network[i]->element[j] = line_data[j];
		}
		if(line_data[ELEMENT_STRING-1] == 'A') {
			number_current_elements++;
		}
	}

	// Get the left/right mappings
	uint *current_elements = malloc(number_current_elements * sizeof(uint));
	for(int i = 0, j = 0; i < network_length; i++) {
		const char *line_data = data[i+2];
		uint left = element_to_index(network, network_length, line_data + 7);
		uint right = element_to_index(network, network_length, line_data + 12);

		network[i]->left = left;
		network[i]->right = right;

		if(line_data[ELEMENT_STRING-1] == 'A') {
			current_elements[j] = i;
			j++;
		}
	}

	for(int i = 0; i < network_length; i++) {
		uint left = network[i]->left;
		uint right = network[i]->right;
		printf("%s: (%s, %s)\n", network[i]->element,
			   network[left]->element, network[right]->element);
	}
	printf("\n\n");

	uint found_end = 0;
	unsigned long long steps = 0;
	while (!found_end) {
		for_each_node(directions, dir) {
			for(int i = 0; i < number_current_elements; i++) {
				uint current_element = current_elements[i];
				current_elements[i] = get_next_element_index(network,
															 current_element,
															 dir->value);

				printf("%s -> %s (%u)\n", network[current_element]->element,
					   network[current_elements[i]]->element, steps);

				if (network[current_elements[i]]->element[ELEMENT_STRING-1] == 'Z') {
					found_end++;
				}
			}
			printf("\n");
			steps++;
			if ((steps & 0xFFFFFFFF) == 0xFFFFFFFF) {
				printf("%llu\n", steps);
			}
			if (found_end == number_current_elements) {
				break;
			} else {
				found_end = 0;
			}
		}
	}

	printf("\nNumber steps: %llu\n", steps);
	return 0;
}
