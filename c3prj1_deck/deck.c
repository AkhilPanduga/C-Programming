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

void add_card_to(deck_t * deck, card_t c) {
  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*(deck->cards)));
  deck->cards[deck->n_cards] = malloc(sizeof(*(deck->cards[deck->n_cards])));
  *(deck->cards[deck->n_cards]) = c;
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck) {
  card_t card;
  card.value = 0;
  card.suit = NUM_SUITS;
  add_card_to(deck, card);
  return deck->cards[(deck->n_cards) - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * r_d = malloc(sizeof(*r_d));
  card_t card;
  r_d->n_cards = 0;
  r_d->cards = malloc(sizeof(*(r_d->cards)));
  for (unsigned i = 0; i < 52; i++) {
    card = card_from_num(i);
    if (deck_contains(excluded_cards, card) == 0)
      add_card_to(r_d, card);
  }
  return r_d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = malloc(sizeof(*(deck->cards)));
  for (size_t i = 0; i < n_hands; i++) {
    for (size_t j = 0; j < hands[i]->n_cards; j++)
      add_card_to(deck, *(hands[i]->cards[j]));
  }
  deck = make_deck_exclude(deck);
  return deck;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++)
    free(deck->cards[i]);
  free(deck->cards);
  free(deck);
}
