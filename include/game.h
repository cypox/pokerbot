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

    _t.deal_flop(_d.draw(), _d.draw(), _d.draw());
    _t.deal_turn(_d.draw());
    _t.deal_river(_d.draw());

    //_t.show_common();

    return _t.get_winner();
  }

  bool simulate_hand(card first, card second)
  {
    _d.init();
    _d.shuffle();
    _d.discard(first);
    _d.discard(second);
    _t.deal_player(0, first, second);
    for (int i = 1 ; i < _n ; ++ i)
    {
      _t.deal_player(i, _d.draw(), _d.draw());
    }

    _t.deal_flop(_d.draw(), _d.draw(), _d.draw());
    _t.deal_turn(_d.draw());
    _t.deal_river(_d.draw());

    //_t.show_common();

    return !_t.get_winner();
  }

private:
  int _n;
  table _t;
  deck _d;
};
