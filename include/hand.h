#pragma once

#include <algorithm>


class hand {
public:
  hand(card cards[7])
  {
    for (int i = 0 ; i < 7 ; ++ i) std::cout << cards[i] << " "; std::cout << std::endl;
    std::sort(cards, cards+7, [](const card& a, const card& b) {
      return a._face > b._face;
    });
    for (int i = 0 ; i < 7 ; ++ i) std::cout << cards[i] << " "; std::cout << std::endl;
    // check for royal flush
    // check for straight flush
    // check for four of a kind
    // check for full house
    // check for flush
    // check for straight
    // check for three of a kind
    // check for double pair
    // check for pair
    // check for high card
  }

  bool operator>(const hand& rhs)
  {
    return false;
  }

private:
};
