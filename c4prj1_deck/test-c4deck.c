#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"

int main(int argc, char ** argv) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = malloc(sizeof(*(deck->cards)));
  for (unsigned i = 9; i < 14; i++) {
    card_t card = card_from_num(i);
    print_card(card);
    printf(" ");
    deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*(deck->cards)));
    deck->cards[deck->n_cards] = malloc(sizeof(*(deck->cards[deck->n_cards])));
    *(deck->cards[deck->n_cards]) = card;
    deck->cards[deck->n_cards]->value = card.value;
    deck->cards[deck->n_cards]->suit = card.suit;
    deck->n_cards++;
  }
  print_hand(deck);
  free_deck(deck);
  return EXIT_SUCCESS;
}
