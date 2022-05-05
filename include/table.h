#pragma once

#include <vector>

#include "player.h"
#include "hand.h"
#include "card.h"


class table {
public:
  table(int np) : _n(np)
  {
    _players.resize(np);
  }

  void deal_player(int idx, card first, card second)
  {
    _players[idx].set_cards(first, second);
    _players[idx].render();
  }

  int get_winner(card& flop1, card& flop2, card& flop3, card& turn, card& river)
  {
    int best_player = 0;
    card cards[7] = {flop1, flop2, flop3, turn, river, _players[0][0], _players[0][1]};
    hand best(cards);
    for (int i = 1 ; i < _n ; ++ i)
    {
      cards[5] = _players[i][0];
      cards[6] = _players[i][1];
      hand current(cards);
      if (current > best) best_player = i;
    }
    return best_player;
  }

private:
  int _n;
  std::vector<player> _players;
};
