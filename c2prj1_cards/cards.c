#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert((c.value >= 2) && (c.value <= VALUE_ACE));
  assert((c.suit >= SPADES) && (c.suit <= CLUBS));
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  default: return "NOTHING";
  }
}

char value_letter(card_t c) {
  char x = '0';
  if((c.value >= 2) && (c.value <= 9))
    x = '0' + c.value;
  if(c.value == 10)
    x = '0';
  if(c.value == VALUE_JACK)
    x = 'J';
  if(c.value == VALUE_QUEEN)
    x = 'Q';
  if(c.value == VALUE_KING)
    x = 'K';
  if(c.value == VALUE_ACE)
    x = 'A';
  return x;
}


char suit_letter(card_t c) {
  char x = '0';
  if(c.suit == SPADES)
    x = 's';
  if(c.suit == HEARTS)
    x = 'h';
  if(c.suit == DIAMONDS)
    x = 'd';
  if(c.suit == CLUBS)
    x = 'c';
  return x;
}

void print_card(card_t c) {
  char x = value_letter(c);
  char y = suit_letter(c);
  printf("%c%c", x, y);
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  unsigned x = 0;
  unsigned y = 0;
  if((((int)value_let) >= 50) && (((int)value_let) <= 57))
    x = (int)value_let - 48;
  if(((int)value_let) == 48)
    x = 10;
  if(((int)value_let) == 74)
    x = 11;
  if(((int)value_let) == 81)
    x = 12;
  if(((int)value_let) == 75)
    x = 13;
  if(((int)value_let) == 65)
    x = 14;
  if(((int)suit_let) == 115)
    y = 0;
  if(((int)suit_let) == 104)
    y = 1;
  if(((int)suit_let) == 100)
    y = 2;
  if(((int)suit_let) == 99)
    y = 3;
  temp.value = x;
  temp.suit = y;
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  temp.value = c%13 + 2;
  temp.suit = c/13;
  assert_card_valid(temp);
  return temp;
}
