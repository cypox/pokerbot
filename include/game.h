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
    card flop[3] = {_d.draw(), _d.draw(), _d.draw()};
    card turn = _d.draw();
    card river = _d.draw();

    return _t.get_winner(flop[0], flop[1], flop[2], turn, river);
  }

private:
  int _n;
  table _t;
  deck _d;
};
