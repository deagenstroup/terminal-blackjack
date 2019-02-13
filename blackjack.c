#include "blackjack.h"

int chip_count;
Card *deck;

int main(int argc, char *argv[])
{
	if(argc == 2)
		chip_count = atoi(argv[1]);
	else
		chip_count = 1000;
	
	while(1) {
		deck = shuffled_deck();
		printf("The dealer shuffles the cards\nChip count: %d\n", chip_count);

		//place a bet
		unsigned int bet;
		printf("Place bet: ");
		while(scanf("%u", &bet) <= 0) {
			flushinput();
			printf("Incorrect input, try again: ");
		}
		flushinput();
		printf("You typed: %u\n", bet);
		printf("\n");
		
		//get cards and give dealer cards
		int card_num = 2;
		int dealer_card_num = 2;
		Card *player_hand = malloc(sizeof(Card)*2);
		Card *dealer_hand = malloc(sizeof(Card)*2);
		player_hand[0] = remove_rand_card(deck);
		player_hand[1] = remove_rand_card(deck);
		dealer_hand[0] = remove_rand_card(deck);
		dealer_hand[1] = remove_rand_card(deck);
		
		int hv;
		print_hand(player_hand, card_num, "Your hand:");
		hv = hand_value(player_hand, card_num);
		char *str = card_string(dealer_hand);
		printf("The dealer's up card is %s\n", str);
		
		//loop of decisions (hit or not)
		while(1) {
			char response[4];
			printf("Would you like to hit or stay? ");
			input:
			scanf("%s", response);
			flushinput();
			if(strcmp(response, "stay") == 0) {
				break;
			} else if(strcmp(response, "hit") == 0) {
				player_hand = realloc(player_hand, sizeof(Card)*(++card_num));
				player_hand[card_num-1] = remove_rand_card(deck);
			} else {
				printf("not valid response, please try again: ");
				goto input;
			}
			printf("\n");

			print_hand(player_hand, card_num, "Your hand:");
			hv = hand_value(player_hand, card_num);
			char *str = card_string(dealer_hand);
			if(hv < 22) {
				printf("The dealer's up card is %s\n", str);
			} else {
				printf("You bust\n");
				goto lose;
			}
		};

		printf("\n");
		print_hand(dealer_hand, dealer_card_num, "Dealer's hand:");
		prompt_user();
		int dealer_hv;
		while(1) {
			dealer_hv = hand_value(dealer_hand, dealer_card_num);
			if(dealer_hv > 21) {
				printf("The dealer busts\n");
				goto win;
			} else if(dealer_hv >= 17) {
				printf("The dealer stays\n");
				break;
			}
			printf("The dealer hits");
			dealer_hand = realloc(dealer_hand, sizeof(Card)*(++dealer_card_num));
			dealer_hand[dealer_card_num-1] = remove_rand_card(deck);
			print_hand(dealer_hand, dealer_card_num, "\nDealer's hand:");
			prompt_user();
		}
		prompt_user();
		printf("\n");
		if(hv <= dealer_hv) {
			lose:
			printf("You lose the hand and lose %d chips\n", bet);
			chip_count -= bet;
		} else {
			win:
			printf("You win the hand and get %d chips\n", bet);
			chip_count += bet;
		}
		prompt_user();
		free(deck);
	}
}

void prompt_user() 
{
	printf("*press enter to continue*\n");
	char c;
	scanf("%c", &c);
}

void print_hand(Card *hand, int card_num, const char *message)
{
	printf("%s\n", message);
	int i;
	for(i = 0; i < card_num; i++) {
		printf(" %s\n", card_string(hand+i));
	}
}

int hand_value(Card *hand, int card_num)
{
	int ace_11 = 0, i;
	for(i = 0; i < card_num; i++) {
		if((hand+i)->number == 1) {
			ace_11++;
		}
	}
	
	int x;
	loop:
	x = ace_11;
	int hand_values[card_num];
	for(i = 0; i < card_num; i++) {
		if((hand+i)->number == 1 && x > 0) {
			hand_values[i] = 11;
			x--;
		} else if ((hand+i)->number == 1) {
			hand_values[i] = 1;
		} else {
			hand_values[i] = card_value((hand+i)->number);
		}
	}

	int result = hand_value_alt(hand_values, card_num);
	if(result > 21 && ace_11 <= 0) {
		return result;
	} else if(result > 21) {
		ace_11--;
		goto loop;
	} else {
		return result;
	}
}
int hand_value_alt(int *hand_nums, int card_num)
{
	int i, sum = 0;
	for(i = 0; i < card_num; i++) {
		sum += *(hand_nums+i);
	}
	return sum;
}

int card_value(int card_number)
{
	if(card_number < 11)
		return card_number;
	else
		return 10;
}

void flushinput() {
	char c;
	while((c = getchar()) != '\n' && c != EOF){}
}

