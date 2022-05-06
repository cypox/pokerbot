#include <iostream>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
  game g(2);
  int won = 0;
  for (int i = 0 ; i < 100000 ; ++ i)
  {
    won += g.simulate_hand(
      card(_A, SPADES),
      card(_A, HEARTS)
    );
  }
  std::cout << "won: " << won << "/" << 100000 << std::endl;

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
