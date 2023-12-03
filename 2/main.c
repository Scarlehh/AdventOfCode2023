#include "data.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Colour {
	RED,
	GREEN,
	BLUE
};

const char colour_mapping[] = {
	'r',
	'g',
	'b'
};

// Return true if the number of blocks exceeds the total for that colour
uint check_blocks(uint number, char token, enum Colour colour, uint *colour_totals) {
	if ((token == colour_mapping[colour]) && (number > colour_totals[colour])) {
		return 1;
	}
	return 0;
}

int main() {
	uint total_cube_power = 0;

	for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		uint line_len = strlen(data[i]);
		uint colour_minimum[] = {0, 0, 0};

		// Format is "<number> <colour>, " or "<number> <colour>; " so just
		// strstr to the next space until there is no more data
		for(char *line_data = strstr(data[i], ":")+1;
			line_data != NULL;
			line_data = strstr(line_data, " ")) {

			int j = 0;
			int number_blocks = 0;
			line_data++;

			// Parse the number
			while ('0' <= line_data[j] && line_data[j] <= '9') {
				number_blocks = (number_blocks * 10) + (line_data[j]-'0');
				j++;
			}
			// Skip over the space
			j++;

			if (check_blocks(number_blocks, line_data[j], RED, colour_minimum)) {
				colour_minimum[RED] = number_blocks;
			}
			if (check_blocks(number_blocks, line_data[j], GREEN, colour_minimum)) {
				colour_minimum[GREEN] = number_blocks;
			}
			if (check_blocks(number_blocks, line_data[j], BLUE, colour_minimum)) {
				colour_minimum[BLUE] = number_blocks;
			}

			line_data += j;
		}

		total_cube_power += (colour_minimum[RED]*colour_minimum[GREEN]*colour_minimum[BLUE]);
	}

	printf("Total: %d\n", total_cube_power);

	return 0;
}
