#pragma once

#include <tuple>

#include "card.h"


class player {
public:
  player()
  {
  }

  void set_cards(card& first, card& second)
  {
    _cards = {first, second};
    std::cout << "player is dealt:\n" << first << "\n" << second << "\n";
  }

private:
  std::pair<card, card> _cards;
};
