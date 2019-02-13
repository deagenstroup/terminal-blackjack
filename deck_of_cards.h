#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbg.h"

typedef enum Suit { HEARTS, SPADES, DIAMONDS, CLUBS } Suit;

//number values 11, 12, and 13 correspond
//to jack, queen, and king respectively
typedef struct Card {
	Suit suit;
	int number;
} Card;

Card *sorted_deck();
Card *shuffle_deck(Card *in_deck);
Card *shuffled_deck();
Card remove_rand_card(Card *in_deck);
int num_cards(Card *deck);
int is_card_null(Card *card);
void deck_print(Card *card);
char *card_string(Card *card);

