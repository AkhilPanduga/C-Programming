#include <stdio.h>
#include <stdlib.h>
#include "future.h"
#include "eval.h"
#include "deck.h"
#include "cards.h"
#include "input.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid no. of inputs!");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Cannot open file: %s", argv[1]);
    return EXIT_FAILURE;
  }
  size_t nHands = 0;
  future_cards_t fc;
  fc.decks = malloc(sizeof(*fc.decks));
  fc.n_decks = 0;
  deck_t ** deck_ts = read_input(f, &nHands, &fc);
  printf("No. of Hands = %zu\n", nHands);

  printf("Unknown Hands:\n");
  for (int i = 0; i < nHands; i++) {
    print_hand(deck_ts[i]);
    printf("\n");
  }

  deck_t * d_shuffle = malloc(sizeof(*d_shuffle));
  d_shuffle->cards = NULL;
  d_shuffle->n_cards = 0;
  for (int j = 0; j < 2; j++) {
    card_t card = card_from_num(j);
    add_card_to(d_shuffle, card);
  }

  printf("Shuffled Hands:\n");
  print_hand(d_shuffle);
  printf("\n");

  future_cards_from_deck(d_shuffle, &fc);

  printf("Known Hands:\n");
  for (int k = 0; k < fc.n_decks; k++) {
    print_hand(&fc.decks[k]);
    printf("\n");
  }

  for (int l = 0; l < nHands; l++)
    free_deck(deck_ts[l]);
  free(deck_ts);
  for (int m = 0; m < fc.n_decks; m++) {
    if (fc.decks[m].n_cards > 0)
      free_deck(&fc.decks[m]);
  }
  free(fc.decks);

  return EXIT_SUCCESS;
}
