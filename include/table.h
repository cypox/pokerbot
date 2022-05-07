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

  std::vector<int> get_winner()
  {
    std::vector<int> best_players{0};
    card cards[7] = {_flop[0], _flop[1], _flop[2], _turn, _river, _players[0][0], _players[0][1]};
    hand best(cards);
    for (int i = 1 ; i < _n ; ++ i)
    {
      cards[5] = _players[i][0];
      cards[6] = _players[i][1];
      hand current(cards);
      if (current > best)
      {
        best_players.clear();
        best_players.push_back(i);
        best = current;
      }
      else if (current == best)
      {
        best_players.push_back(i);
      }
    }
    for (auto& best_player : best_players) _players[best_player].render();
    std::cout << best << std::endl;
    return best_players;
  }

private:
  int _n;
  std::vector<player> _players;
  card _flop[3];
  card _turn;
  card _river;
};
