#include "cards.h"

int main(void) {
  card_t a = card_from_num(38);
  print_card(a);
  char c = 'A';
  char d = 's';
  card_t b = card_from_letters(c, d);
  print_card(b);
}
