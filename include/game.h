#pragma once

#include "deck.h"
#include "table.h"


class game {
public:
  game(int players) : _t(players), _n(players)
  {
  }

  int run()
  {
    _d.shuffle();
    for (int i = 0 ; i < _n ; ++ i)
    {
      _t.deal_player(i, _d.draw(), _d.draw());
    }

    // TODO: move flop, turn and river cards to table class
    _t.deal_flop(_d.draw(), _d.draw(), _d.draw());
    _t.deal_turn(_d.draw());
    _t.deal_river(_d.draw());

    return _t.get_winner();
  }

private:
  int _n;
  table _t;
  deck _d;
};
