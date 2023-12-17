#include "data.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRACE 1

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

#define ASH '.'
#define ROCK '#'

uint _find_vertical_reflections(const char **field, uint height, uint width, uint j, uint d) {
	for (int i = 0; i < height; i++) {
		if (field[i][j] != field[i][j+d]) {
			return 0;
		}
	}
	if (j == 0 || j+d == width-1) {
		return 1;
	}
	return _find_vertical_reflections(field, height, width, j-1, d+2);
}

uint _find_horizontal_reflections(const char **field, uint height, uint width, uint i, uint d) {
	for (int j = 0; j < width; j++) {
		if (field[i][j] != field[i+d][j]) {
			return 0;
		}
	}
	if (i == 0 || i+d == height-1) {
		return -1;
	}
	return _find_horizontal_reflections(field, height, width, i-1, d+2);
}

uint find_vertical_reflections(const char **field, uint height, uint width) {
	for (int j = 0; j < width-1; j++) {
		if (_find_vertical_reflections(field, height, width, j, 1)) {
			if (TRACE)
				printf("Found vertical reflection at columns %u %u\n", j, j+1);
			return j+1;
		}
	}
	return 0;
}

uint find_horizontal_reflections(const char **field, uint height, uint width) {
	for (int i = 0; i < height-1; i++) {
		if (_find_horizontal_reflections(field, height, width, i, 1)) {
			if (TRACE)
				printf("Found horizontal reflection at rows %u %u\n", i, i+1);
			return 100*(i+1);
		}
	}
	return 0;
}

void print_pattern(const char **field, uint height) {
	for (int i = 0; i < height; i++) {
		printf("%s\n", field[i]);
	}
	printf("\n");
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);
	uint width = 0;

	uint sum = 0;
	for (int i = 0, start = 0; i < height; i++) {
		if (data[i+1] == NULL || data[i+1][0] == '\0') {
			uint ret;
			width  = strlen(data[i]);
			if (TRACE)
				print_pattern(data+start, i-start+1);
			if (ret = find_vertical_reflections(data+start, i-start+1, width)) {
				sum += ret;
				if (TRACE)
					printf("Sum is %u\n\n", ret);
			}
			if (ret = find_horizontal_reflections(data+start, i-start+1, width)) {
				sum += ret;
				if (TRACE)
					printf("Sum is %u\n\n", ret);
			}
			start = i+2;
		}
	}
	printf("Total sum is %u\n", sum);
}
