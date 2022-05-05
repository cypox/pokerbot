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
      for (int f = 0 ; f < 13 ; ++ f)
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

private:
  std::vector<card> _d;
};
