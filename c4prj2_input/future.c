#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "future.h"
#include "deck.h"
#include "cards.h"

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (fc->n_decks <= index) {
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(*(fc->decks)));
    for (size_t i = fc->n_decks; i <= index; i++) {
      fc->decks[i].cards = NULL;
      fc->decks[i].n_cards = 0;
    }
    fc->n_decks = index + 1;
  }
  fc->decks[index].n_cards++;
  fc->decks[index].cards = realloc(fc->decks[index].cards, (fc->decks[index].n_cards + 1) * sizeof(*(fc->decks[index].cards[fc->decks[index].n_cards - 1])));
  fc->decks[index].cards[fc->decks[index].n_cards - 1] = ptr;
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  size_t n = 0;
  size_t n_fc = 0;
  if (deck == NULL)
    return;
  if (fc->decks == NULL)
    return;
  if (deck->n_cards == 0)
    return;
  if (fc->n_decks == 0)
    return;
  for (size_t i = 0; i < fc->n_decks; i++) {
    if (fc->decks[i].n_cards > 0)
      n_fc++;
  }
  if (n_fc > deck->n_cards)
    return;
  for (size_t j = 0; j < fc->n_decks; j++) {
    if (fc->decks[j].n_cards > 0) {
      for (size_t k = 0; k < fc->decks[j].n_cards; j++)
	*(fc->decks[j].cards[k]) = *(deck->cards[n]);
    }
    n++;
  }
}
