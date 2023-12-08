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


// Cards
#define CARDS_IN_HAND 5

enum Type {
	FIVE_OF_A_KIND = 0,
	FOUR_OF_A_KIND,
	FULL_HOUSE,
	THREE_OF_A_KIND,
	TWO_PAIR,
	ONE_PAIR,
	HIGH_CARD
};

struct Hand {
	char hand[CARDS_IN_HAND];
	uint bid;
	uint rank;
	enum Type type;
};

char strengths[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

int card_strength(char card) {
	for (int i = 0; sizeof(strengths); i++) {
		if (card == strengths[i]) {
			return i;
		}
	}
	return -1;
}

// 0 if the cards are the same
// Positive integer is cardA is stronger
// Negative integer is cardA is stronger
int strongest_card(char cardA, char cardB) {
	return card_strength(cardA) - card_strength(cardB);
}

int strongest_hand(char *handA, char *handB) {
	for (int i = 0; i < CARDS_IN_HAND; i++) {
		int strongest = strongest_card(handA[i], handB[i]);
		if (strongest != 0) {
			return strongest;
		}
	}
	return 0;
}

char n_of_a_kind(char *hand, uint n, char exclude) {
	for (int i = 0; i < CARDS_IN_HAND; i++) {
		uint of_a_kind = 1;
		char card = hand[i];
		if (exclude && card == exclude) {
			continue;
		}
		for (int j = i+1; j < CARDS_IN_HAND; j++) {
			if (card == hand[j]) {
				of_a_kind++;
			}
		}
		if (of_a_kind >= n) {
			return card;
		}
	}
	return 0;
}

char n_and_m_of_a_kind(char *hand, uint n, uint m) {
	char first_pair = n_of_a_kind(hand, n, 0);
	if (first_pair) {
		char second_pair = n_of_a_kind(hand, m, first_pair);
		return second_pair;
	}
	return first_pair;
}

#define five_of_a_kind(hand) n_of_a_kind(hand, 5, 0)
#define four_of_a_kind(hand) n_of_a_kind(hand, 4, 0)
#define full_house(hand) n_and_m_of_a_kind(hand, 3, 2)
#define three_of_a_kind(hand) n_of_a_kind(hand, 3, 0)
#define two_pair(hand) n_and_m_of_a_kind(hand, 2, 2)
#define one_pair(hand) n_of_a_kind(hand, 2, 0)

enum Type determine_type(char *hand) {
	if (five_of_a_kind(hand)) {
		return FIVE_OF_A_KIND;
	} else if (four_of_a_kind(hand)) {
		return FOUR_OF_A_KIND;
	} else if (full_house(hand)) {
		return FULL_HOUSE;
	} else if (three_of_a_kind(hand)) {
		return THREE_OF_A_KIND;
	} else if (two_pair(hand)) {
		return TWO_PAIR;
	} else if (one_pair(hand)) {
		return ONE_PAIR;
	}
	return HIGH_CARD;
}

char* type_to_string(enum Type type) {
	switch (type) {
	case FIVE_OF_A_KIND: return "Five of a kind";
	case FOUR_OF_A_KIND: return "Four of a kind";
	case FULL_HOUSE: return "Full house";
	case THREE_OF_A_KIND: return "Three of a kind";
	case TWO_PAIR: return "Two pair";
	case ONE_PAIR: return "One pair";
	case HIGH_CARD: return "High card";
	}
	return "Error";
}

void rank_hands(struct Hand **hands, struct Node *hands_of_type, uint current_rank) {
	for_each_node(hands_of_type, i) {
		uint rank = current_rank;
		for_each_node(hands_of_type, j) {
			if (i== j) {
				continue;
			}
			int strongest = strongest_hand(hands[i->value]->hand, hands[j->value]->hand);
			// hand[j->value] is stronger
			if (strongest <= 0) {
				rank--;
			}
		}
		hands[i->value]->rank = rank;
	}
}

// Main
int main() {
	const char **data  = input;
	uint height = sizeof(input)/sizeof(data[0]);

	struct Node *five_of_a_kind = NULL;
	struct Node *four_of_a_kind = NULL;
	struct Node *full_house = NULL;
	struct Node *three_of_a_kind = NULL;
	struct Node *two_pair = NULL;
	struct Node *one_pair = NULL;
	struct Node *high_card = NULL;

	uint num_five_of_a_kind = 0;
	uint num_four_of_a_kind = 0;
	uint num_full_house = 0;
	uint num_three_of_a_kind = 0;
	uint num_two_pair = 0;
	uint num_one_pair = 0;
	uint num_high_card = 0;

	struct Hand **hands = malloc(height*sizeof(struct Hand*));
	for(int i = 0; i < height; i++) {
		hands[i] = malloc(sizeof(struct Hand));

		for(int j = 0; j < CARDS_IN_HAND; j++) {
			hands[i]->hand[j] = data[i][j];
		}

		uint bid;
		sscanf(data[i], "%*s %u", &bid);
		hands[i]->bid = bid;

		hands[i]->type = determine_type(hands[i]->hand);
		hands[i]->rank = 0;

		switch (hands[i]->type) {
		case FIVE_OF_A_KIND:
			five_of_a_kind = append_list(five_of_a_kind, i);
			num_five_of_a_kind++;
			break;
		case FOUR_OF_A_KIND:
			four_of_a_kind = append_list(four_of_a_kind, i);
			num_four_of_a_kind++;
			break;
		case FULL_HOUSE:
			full_house = append_list(full_house, i);
			num_full_house++;
			break;
		case THREE_OF_A_KIND:
			three_of_a_kind = append_list(three_of_a_kind, i);
			num_three_of_a_kind++;
			break;
		case TWO_PAIR:
			two_pair = append_list(two_pair, i);
			num_two_pair++;
			break;
		case ONE_PAIR:
			one_pair = append_list(one_pair, i);
			num_one_pair++;
			break;
		case HIGH_CARD:
			high_card = append_list(high_card, i);
			num_high_card++;
			break;
		}
	}

	uint rank = height;
	rank_hands(hands, five_of_a_kind, rank);
	rank -= num_five_of_a_kind;
	rank_hands(hands, four_of_a_kind, rank);
	rank -= num_four_of_a_kind;
	rank_hands(hands, full_house, rank);
	rank -= num_full_house;
	rank_hands(hands, three_of_a_kind, rank);
	rank -= num_three_of_a_kind;
	rank_hands(hands, two_pair, rank);
	rank -= num_two_pair;
	rank_hands(hands, one_pair, rank);
	rank -= num_one_pair;
	rank_hands(hands, high_card, rank);
	rank -= num_high_card;

	unsigned long long total_winnings = 0;
	for(int i = 0; i < height; i++) {
		//printf("Hand %s has bid %u, type %s and rank %u!\n",
		//	   hands[i]->hand, hands[i]->bid,
		//	   type_to_string(hands[i]->type),
		//	   hands[i]->rank);
		printf("%u %s %u\n", hands[i]->rank, hands[i]->hand, hands[i]->bid);
		total_winnings += hands[i]->rank * hands[i]->bid;
	}

	printf("Total winnings: %llu\n", total_winnings);

	return 0;
}
