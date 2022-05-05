#include <iostream>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
  game g(8);
  g.simulate_hand(
    card(SPADES, _A),
    card(SPADES, _K)
  );

  hand h(
    card(0, 10),
    card(0, 11),
    card(0, 12),
    card(0, 13),
    card(0, 14)
  );
  std::cout << h << std::endl;
  h.rank_hand();
  return 0;
}
