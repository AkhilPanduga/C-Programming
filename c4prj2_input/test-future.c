#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "future.h"
#include "deck.h"
#include "cards.h"

int main(int argc, char ** argv) {
  future_cards_t fc;
  fc.n_decks = 0;
  fc.decks = malloc(sizeof(*fc.decks));
  fc.decks->cards = NULL;
  fc.decks->n_cards = 0;
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  deck_t * d_shuffle = malloc(sizeof(*d_shuffle));
  d_shuffle->cards = NULL;
  d_shuffle->n_cards = 0;
  for (unsigned i = 0; i < 2; i++) {
    card_t card = card_from_num(i);
    add_card_to(d_shuffle, card);
  }
  for (size_t j = 0; j < 2; j++) {
    card_t * ptr = add_empty_card(deck);
    add_future_card(&fc, j, ptr);
  }
  
  printf("Unknown Future Cards\n");
  for (int k = 0; k < fc.n_decks; k++)
    print_hand(&fc.decks[k]);

  printf("\n");
  printf("Shuffled Cards\n");

  print_hand(d_shuffle);

  future_cards_from_deck(d_shuffle, &fc);

  printf("\n");
  printf("Future Cards\n");
  for (int l = 0; l < fc.n_decks; l++) {
    print_hand(&fc.decks[l]);
  }
  printf("\n");
  
  free_deck(deck);
  free_deck(d_shuffle);
  return EXIT_SUCCESS;
}
