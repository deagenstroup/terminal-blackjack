CFLAGS=-g -Wall

all: blackjack

blackjack: deck_of_cards.o

clean:
	rm -f blackjack
