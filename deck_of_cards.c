#include "deck_of_cards.h"

Card *sorted_deck()
{
	Card *deck = malloc(sizeof(Card)*52);
	int i = 0;
	while(i < 13) {
		deck[i].suit = HEARTS;
		deck[i].number = i+1;
		i++;
	}
	while(i < 26) {
		deck[i].suit = SPADES;
		deck[i].number = (i-13)+1;		
		i++;
	}
	while(i < 39) {
		deck[i].suit = DIAMONDS;
		deck[i].number = (i-26)+1;
		i++;
	}
	while(i < 52) {
		deck[i].suit = CLUBS;
		deck[i].number = (i-39)+1;
		i++;
	}
	return deck;
}

Card *shuffle_deck(Card *in_deck)
{
	srand(time(NULL));
	Card *s_deck = malloc(sizeof(Card)*52);
	int i, x = 0;
	for(i = 0; i < 52; i++) {
		Card rand_card = remove_rand_card(in_deck);
		s_deck[x] = rand_card;
		x++;
	}
	free(in_deck);
	return s_deck;
}

Card *shuffled_deck()
{
	Card *deck = sorted_deck();
	deck = shuffle_deck(deck);
	return deck;
}

Card remove_rand_card(Card *in_deck)
{
	if(num_cards(in_deck) == 0)
		return (Card){.number = 0, .suit = 0};
	
	Card return_card;
	Card *pt;
	int u = rand() % 52;
	pt = (in_deck+u);
	
	while(is_card_null(pt) == 1) {
		pt++;
		u++;
		if(u > 51) {
			pt = in_deck;
			u = 0;
		}
	}
	return_card = *pt;
	memset((in_deck+u), '\0', sizeof(Card));
	return return_card;
}

int num_cards(Card *deck)
{
	int i, cards = 0;
	for(i = 0; i < 52; i++) {
		if(is_card_null(deck+i) == 0)
			cards++;
	}
	return cards;
}

int is_card_null(Card *card)
{
	if(card->number == 0)
		return 1;
	else
		return 0;
}

void deck_print(Card *card)
{
	int i;
	for(i = 0; i < 52; i++) {
		printf("%d: %s\n", i, card_string(card+i));
	}
}

char *card_string(Card *card)
{
	char *str;
	str = malloc(sizeof(char)*50);
	check(str != NULL, "Error getting card string");

	if(is_card_null(card)) {
		strcpy(str, "NULL");
		goto end;
	}
	
	if(card->number == 11) {
		strcpy(str, "Jack");
	} else if(card->number == 12) {
		strcpy(str, "Queen");
	} else if(card->number == 13) {
		strcpy(str, "King");
	} else if(card->number == 1) {
		strcpy(str, "Ace");
	} else {
		sprintf(str, "%d", card->number);
	}
	
	strcat(str, " of ");

	if(card->suit == HEARTS) {
		strcat(str, "Hearts");
	} else if(card->suit == SPADES) {
		strcat(str, "Spades");
	} else if(card->suit == DIAMONDS) {
		strcat(str, "Diamonds");
	} else if(card->suit == CLUBS) {
		strcat(str, "Clubs");
	}
	
	end:
	return str;

error:
	return NULL;
}

