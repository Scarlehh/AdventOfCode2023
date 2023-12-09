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

unsigned long long steps_to_end(struct Element **network, struct Node *directions,
								uint *start_element, uint *start_direction) {
	unsigned long long steps = 0;
	struct Node *start_directions = directions;
	for (int i = 0; i < (*start_direction); i++) {
		start_directions = start_directions->next;
	}
	while (1) {
		for_each_node(start_directions, dir) {
			uint current_element = *start_element;
			*start_element = get_next_element_index(network, current_element, dir->value);
			(*start_direction)++;

			//printf("%s -> %s (%u)\n", network[current_element]->element,
			//	   network[(*start_element)]->element, steps);

			steps++;
			if (network[(*start_element)]->element[ELEMENT_STRING-1] == 'Z') {
				return steps;
			}
		}
		*start_direction = 0;
		start_directions = directions;
	}
	return -1;
}

// Maths lol
unsigned long long gcd(unsigned long long valA, unsigned long long valB) {
	for (unsigned long long i=2; i <= valA && i <= valB; i++) {
        if ((valA % i == 0) && (valB % i == 0)) {
			return i;
		}
    }
	return 1;
}

unsigned long long lcm(unsigned long long valA, unsigned long long valB) {
	return (valA * valB)/gcd(valA, valB);
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);

	// Get the directions first
	struct Node *directions = NULL;
	for (int i = 0; data[0][i] != '\0'; i++) {
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
	for (int i = 0; i < network_length; i++) {
		const char *line_data = data[i+2];

		network[i] = malloc(sizeof(struct Element));
		for (int j = 0; j < ELEMENT_STRING; j++) {
			network[i]->element[j] = line_data[j];
		}
		if(line_data[ELEMENT_STRING-1] == 'A') {
			number_current_elements++;
		}
	}

	// Get the left/right mappings
	uint *current_elements = malloc(number_current_elements * sizeof(uint));
	for (int i = 0, j = 0; i < network_length; i++) {
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

	for (int i = 0; i < network_length; i++) {
		uint left = network[i]->left;
		uint right = network[i]->right;
		printf("%s: (%s, %s)\n", network[i]->element,
			   network[left]->element, network[right]->element);
	}

	uint found_end = 0;
	// Don't actually need z->z because a->z is the same as z->z.
	//
	// This solution really isn't generic enough to handle this. There can be many
	// loops of z->z that differ within a set, and different starting points for each
	// loop depending on the directions. The maths for this input is also much
	// more complicated than a simple LCM formula. I did start trying to do this,
	// hence the ability to input a starting point for the network and directions,
	// but realised at this point the loops were the same length.
	unsigned long long *a_to_z_steps = malloc(number_current_elements * sizeof(unsigned long long));
	//unsigned long long *z_to_z_steps = malloc(number_current_elements * sizeof(unsigned long long));
	for (int i = 0; i < number_current_elements; i++) {
		uint current_direction = 0;
		a_to_z_steps[i] = steps_to_end(network, directions,
									   &(current_elements[i]), &current_direction);
		//z_to_z_steps[i] = steps_to_end(network, directions,
		//							   &(current_elements[i]), &current_direction);
		//printf("%llu %llu\n", a_to_z_steps[i], z_to_z_steps[i]);
	}

	// Get lowest common multiple of all the loops
	unsigned long long steps = a_to_z_steps[0];
	for (int i = 1; i < number_current_elements; i++) {
		steps = lcm(steps, a_to_z_steps[i]);
	}

	printf("\nNumber steps: %llu\n", steps);
	return 0;
}
