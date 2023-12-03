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

const int colour_total[] = {
	12,
	13,
	14
};

// Return true if the number of blocks exceeds the total for that colour
uint check_blocks(uint number, char token, enum Colour colour) {
	if ((token == colour_mapping[colour]) && (number > colour_total[colour])) {
		return 1;
	}
	return 0;
}

int main() {
	uint total_red = 12;
	uint total_green = 13;
	uint total_blue = 14;

	uint total_possible = 0;

	for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		printf("\n%s\n", data[i]);
		uint line_len = strlen(data[i]);
		int possible = 1;

		// Format is "<number> <colour>," or "<number> <colour;"
		for(char *line_data = strstr(data[i], ":")+1;
			line_data != NULL && possible;
			line_data = strstr(line_data, " ")) {

			int j = 0;
			int number_blocks = 0;
			line_data++;

			//printf("%s\n", line_data);
			while ('0' <= line_data[j] && line_data[j] <= '9') {
				number_blocks = (number_blocks * 10) + (line_data[j]-'0');
				j++;
			}
			// Skip over the space
			j++;

			if (check_blocks(number_blocks, line_data[j], RED)) {
				possible = 0;
				printf("Number blocks to make this impossible for RED: %d\n", number_blocks);
			}
			else if (check_blocks(number_blocks, line_data[j], GREEN)) {
				printf("Number blocks to make this impossible for GREEN: %d\n", number_blocks);
				possible = 0;
			}
			else if (check_blocks(number_blocks, line_data[j], BLUE)) {
				printf("Number blocks to make this impossible for BLUE: %d\n", number_blocks);
				possible = 0;
			}

			line_data += j;
		}

		if (possible) {
			printf("Adding game %d\n", i+1);
			total_possible += i+1;
		}
	}

	printf("Total: %d\n", total_possible);

	return 0;
}
