#pragma once

#include <vector>

#include "player.h"
#include "card.h"


class table {
public:
  table(int np)
  {
    _players.resize(np);
  }

  void deal_player(int idx, card first, card second)
  {
    _players[idx].set_cards(first, second);
  }

private:
  std::vector<player> _players;
};
