#pragma once

#include <algorithm>
#include <vector>

#include "card.h"


class deck {
public:
  deck()
  {
    init();
  }

  void init()
  {
    _d.clear();
    for (int s = 0 ; s < 4 ; ++ s)
    {
      for (int f = 2 ; f <= 14 ; ++ f)
      {
        _d.emplace_back(s, f);
      }
    }
  }

  void shuffle()
  {
    std::random_shuffle(_d.begin(), _d.end());
  }

  card draw()
  {
    card c = _d.back();
    _d.pop_back();
    return c;
  }

  void burn()
  {
    _d.pop_back();
  }

  void discard(card& c)
  {
    int i = -1;
    while (_d[++i] != c);
    _d.erase(_d.begin()+ i);
  }

private:
  std::vector<card> _d;
};
