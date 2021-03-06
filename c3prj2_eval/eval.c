
#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  if ((**(cp1)).value > (**(cp2)).value)
    return -1;
  if ((**(cp1)).value == (**(cp2)).value) {
    if ((**(cp1)).suit == (**(cp2)).suit)
      return 0;
    else {
      if ((**(cp1)).suit == CLUBS && (**(cp2)).suit != CLUBS)
	return -1;
      if ((**(cp1)).suit == DIAMONDS && (**(cp2)).suit != DIAMONDS) {
	if ((**(cp2)).suit != CLUBS)
	  return -1;
	else return 1;
      }
      if ((**(cp1)).suit == HEARTS && (**(cp2)).suit != HEARTS) {
	if ((**(cp2)).suit != SPADES)
	  return 1;
	else return -1;
      }
      else return 1;
    }
  }
  else return 1;
}

suit_t flush_suit(deck_t * hand) {
  size_t count = 1;
  deck_t h_c = *hand;
  card_t s, r;
  for (size_t i = 0; i < (hand->n_cards) - 1; i++) {
    s = *(h_c.cards)[i];
    for (size_t j = i + 1; j < (hand->n_cards); j++) {
      r = *(h_c.cards)[j];
      if (s.suit == r.suit)
	count++;
    }
    if (count >= 5)
      return s.suit;
    count = 1;
  }
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned max = arr[0];
  for (size_t i = 1; i < n; i++) {
    if (arr[i] > max)
      max = arr[i];
  }
  return max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i = 0; i < n; i++) {
    if (match_counts[i] == n_of_akind)
      return i;
  }
  return 0;
}
ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  deck_t h_c = *hand;
  card_t s, r;
  for (size_t i = 0; i < (hand->n_cards); i++) {
    s = *(h_c.cards)[i];
    r = *(h_c.cards)[match_idx];
    if (match_counts[i] > 1) {
      if(s.value != r.value)
	return i;
    }
  }
  return -1;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  size_t count = 0;
  int diff = 1;
  card_t s, r, temp;
  deck_t h_c = *hand;
  size_t idx = index;
  for (size_t i = idx + 1; i < (hand->n_cards); i++) {
    s = *(h_c.cards)[i];
    r = *(h_c.cards)[idx];
    if (fs != NUM_SUITS) {
      if (r.suit == fs) {
	if ((r.value - s.value) < 2) {
	  if (s.suit == fs) {
	    if ((r.value - s.value) == 0)
	      idx = i;
	    if ((r.value - s.value) == 1) {
	      idx = i;
	      count++;
	      if (count == n-1)
		return 1;
	    }
	  }
	  else {
	    for (size_t j = i + 1; j < (hand->n_cards); j++) {
	      s = *(h_c.cards)[j];
	      if ((r.value - s.value) <= diff) {
		if (index != 0) {
		  temp = *(h_c.cards)[index - 1];
		  if (r.suit == temp.suit)
		    return 0;
		}
		if(s.suit == fs) {
		  count++;
		  diff++;
		  if (count == n-1)
		    return 1;
		}
	      }
	    }
	  }
	}
	else return 0;
      }
      else return 0;
    }
    else {
      if ((r.value - s.value) < 2) {
	if ((r.value - s.value) == 0)
	  idx = i;
	if ((r.value - s.value) == 1) {
	  idx = i;
	  count++;
	  if (count == n-1)
	    return 1;
	}
      }
    }
  }
  return 0;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
  int b = is_n_length_straight_at(hand, index, fs, 5);
  deck_t h_c = *hand;
  card_t s;
  size_t idx = index;
  if (b == 0) {
    for (size_t i = idx; i < (hand->n_cards); i++) {
      s = *(h_c.cards)[i];
      if (s.value == 5) {
	int a = is_n_length_straight_at(hand, i, fs, 4);
	if (a == 1)
	  return -1;
	else return 0;
      }
    }
    return 0;
  }
  else return 1;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  deck_t h_c = *hand;
  card_t s = *(h_c.cards)[index];
  if (s.value == VALUE_ACE)
    return is_ace_low_straight_at(hand, index, fs);
  else return is_n_length_straight_at(hand, index, fs, 5);
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {
  hand_eval_t ans;
  size_t index = idx;
  size_t index0 = 0;
  size_t index1 = 0;
  ans.ranking = what;
  deck_t h_c = *hand;
  for (size_t i = 0; i < n; i++) {
    ans.cards[i] = (h_c.cards)[index];
    index++;
  }
  if(idx == 0) {
    index = n;
    for (size_t j = n; j < 5; j++) {
      ans.cards[j] = (h_c.cards)[index];
      index++;
    }
  }
  if (idx != 0) {
    if(idx >= 5 - n) {
      for (size_t k = n; k < 5; k++) {
	ans.cards[k] = (h_c.cards)[index0];
	index0++;
      }
    }
    if(idx < 5 - n) {
      for (size_t l = n; l < 5; l++) {
	ans.cards[l] = (h_c.cards)[index1];
	index1++;
	if (index1 == idx)
	  index1 += n;
      }
    }
  }
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(hand1->cards[0]), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(hand2->cards[0]), card_ptr_comp);
  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);
  card_t s, r;
  if (h1.ranking != h2.ranking) {
    if (h1.ranking < h2.ranking)
      return 1;
    else return -1;
  }
  else {
    for (int j = 0; j < 5; j++) {
      s = *(h1.cards)[j];
      r = *(h2.cards)[j];
      if ((s.value - r.value) != 0)
	return s.value - r.value;
    }
    return 0;
  }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {
  unsigned match = 0;
  unsigned * matchCounts = malloc((hand->n_cards) * sizeof(*matchCounts));
  for (int i = 0; i < hand->n_cards; i++)
    matchCounts[i] = 1;
  while (match < hand->n_cards) {
    unsigned count = 1;
    for (unsigned j = match + 1; j < hand->n_cards; j++) {
      if ((hand->cards[match]->value) == (hand->cards[j]->value))
	count++;
    }
    for (unsigned k = match; k < (match + count); k++)
      matchCounts[k] = count;
    match += count; 
  }
  return matchCounts;
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4]; 
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
