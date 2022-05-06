#include <iostream>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
  game g(8);
  g.simulate_hand(
    card(_A, SPADES),
    card(_K, SPADES)
  );

  /* test hand
  hand h(
    card(_T, SPADES),
    card(_J, SPADES),
    card(_Q, SPADES),
    card(_K, SPADES),
    card(_A, SPADES)
  );
  std::cout << h << std::endl;
  h.rank_hand();
  */
  return 0;
}
