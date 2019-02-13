#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbg.h"
#include "deck_of_cards.h"

void print_hand(Card *hand, int card_num, const char *message);
int card_value(int card_number);
int hand_value(Card *hand, int card_num);
int hand_value_alt(int *hand_nums, int card_num);
void flushinput();
void prompt_user();

