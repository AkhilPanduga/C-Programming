#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  deck_t h = *hand;
  for (size_t i = 0; i < hand->n_cards; i++) {
    print_card(*(h.cards)[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  deck_t d_c = *d;
  card_t s;
  for (size_t i = 0; i < d->n_cards; i++) {
    s = *(d_c.cards)[i];
    if (s.value == c.value) {
      if (s.suit == c.suit) {
	return 1;
      }
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  deck_t d_c = *d;
  card_t s;
  for (size_t k = 0; k < d->n_cards; k++) {
    size_t j = k + (random()%(d->n_cards - k));
    s = *(d_c.cards)[k];
    *(d_c.cards)[k] = *(d_c.cards)[j];
    *(d_c.cards)[j] = s;
  }
}

void assert_full_deck(deck_t * d) {
  deck_t d_c = *d;
  card_t s, r, temp;
  for (size_t k = 0; k < (d->n_cards); k++) {
    temp = *(d_c.cards)[k];
    assert_card_valid(temp);
  }
  for (size_t i = 0; i < (d->n_cards) - 1; i++) {
    s = *(d_c.cards)[i];
    for (size_t j = i + 1; j < (d->n_cards); j++) {
    r = *(d_c.cards)[j];
    assert(((s.value != r.value) && (s.suit != r.suit)) || ((s.value == r.value) && (s.suit != r.suit)) || ((s.value != r.value) && (s.suit == r.suit)));
    }
  }
}

