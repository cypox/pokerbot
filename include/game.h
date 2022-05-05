#pragma once

#include "deck.h"
#include "table.h"


class game {
public:
  game(int players) : _t(players)
  {
    _d.shuffle();
    for (int i = 0 ; i < players ; ++ i)
    {
      _t.deal_player(i, _d.draw(), _d.draw());
    }
  }

private:
  table _t;
  deck _d;
};
