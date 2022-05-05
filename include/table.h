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

  void deal_flop(card first, card second, card third)
  {
    _flop[0] = first;
    _flop[1] = second;
    _flop[2] = third;
  }

  void deal_turn(card turn)
  {
    _turn = turn;
  }

  void deal_river(card river)
  {
    _river = river;
  }

  void show_common()
  {
    std::cout << "[" << _flop[0] << ", "
              << _flop[1] << ", "
              << _flop[2] << ", "
              << _turn << ", "
              << _river << "]"
              << std::endl;
  }

  int get_winner()
  {
    int best_player = 0;
    card cards[7] = {_flop[0], _flop[1], _flop[2], _turn, _river, _players[0][0], _players[0][1]};
    hand best(cards);
    for (int i = 1 ; i < _n ; ++ i)
    {
      //cards[5] = _players[i][0];
      //cards[6] = _players[i][1];
      card cards[7] = {_flop[0], _flop[1], _flop[2], _turn, _river, _players[i][0], _players[i][1]};
      hand current(cards);
      if (current > best) best_player = i;
    }
    return best_player;
  }

private:
  int _n;
  std::vector<player> _players;
  card _flop[3];
  card _turn;
  card _river;
};
