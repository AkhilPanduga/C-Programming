#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "future.h"
#include "deck.h"
#include "cards.h"
#include "input.h"

deck_t * getHand(const char * str, future_cards_t * fc) {
  deck_t * deck = malloc(sizeof(*deck));
  deck->cards = NULL;
  deck->n_cards = 0;
  int i = 0;
  char * nline = "\n";
  while(1) {
    if (*(str + i) == '?') {
      int n = 1;
      while(isdigit(*(str + i + n)))
	n++;
      char str_n[n];
      for (int j = 0; j < n - 1; j++)
	str_n[j] = *(str + i + j + 1);
      str_n[n-1] = '\0';
      size_t idx = (size_t)atoi(str_n);
      card_t * ptr = add_empty_card(deck);
      add_future_card(fc, idx, ptr);
      i = i + n;
    }
    else if (isalnum(*(str + i))) {
      card_t card = card_from_letters(*(str + i), *(str + i + 1));
      add_card_to(deck, card);
      i = i + 2;
    }
    else if (strcmp((str + i), nline) == 0)
      break;
    else i++;
  }
  if (deck->n_cards < 5)
    return NULL;
  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  deck_t ** deck_ts = NULL;
  char * lines = NULL;
  size_t s = 0;
  int i = 0;
  while (getline(&lines, &s, f) > 0) {
    *n_hands++;
    deck_ts = realloc(deck_ts, (*n_hands) * sizeof(**deck_ts));
    deck_t * deck = getHand(lines, fc);
    deck_ts[i] = deck;
    free(lines);
    lines = NULL;
    i++;
  }
  free(lines);
  return deck_ts;
}
