#pragma once

#include <tuple>

#include "hand.h"
#include "card.h"


class player {
public:
  player()
  {
  }

  void set_cards(card& first, card& second)
  {
    _cards = {first, second};
  }

  void render()
  {
    std::cout << "hand: [" << _cards.first << ", " << _cards.second << "]\n";
  }

  card& operator[](int idx)
  {
    return idx ? _cards.second : _cards.first;
  }

private:
  std::pair<card, card> _cards;
};
