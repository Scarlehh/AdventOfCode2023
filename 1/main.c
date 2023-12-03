#include "data.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *number_mapping[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine"
};

const char *number_mapping_reverse[] = {
	"orez",
	"eno",
	"owt",
	"eerht",
	"ruof",
	"evif",
	"xis",
	"neves",
	"thgie",
	"enin"
};

uint numstr(const char* str, const char **needles) {
	uint pos = -1;
	uint val = -1;

	// Look for ASCII 0-9
	for (int i = 0; str[i] != '\0' && pos == -1; i++) {
		uint number = str[i] - '0';

		if (0 <= number && number <= 9) {
			pos = i;
			val = number;
		}
	}

	// Look for mappings between numbers, i.e. "zero" -> 0
	for (int i = 0; i < 10; i++) {
		char *result = strstr(str, needles[i]);
		uint result_pos = result ? result - str : -1;

		if (result_pos != -1) {
			if (result_pos < pos) {
				pos = result_pos;
				val = i;
			}
		}
	}

	return val;
}

int main() {
	int total = 0;
	for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
		// Look for first number
		uint first_val = numstr(data[i], number_mapping);

		uint data_len = strlen(data[i]);
		char *data_reverse = malloc(data_len+1);
		for (int j = 0; j < data_len; j++) {
			data_reverse[j] = data[i][data_len-j-1];
		}
		data_reverse[data_len] = '\0';

		// Look for last number
		uint last_val = numstr(data_reverse, number_mapping_reverse);

		total += (first_val * 10) + last_val;

		//printf("%s %s %d %d\n", data[i], data_reverse, first_val, last_val);

		free(data_reverse);
	}

	printf("Total: %d\n", total);
	return 0;
}
