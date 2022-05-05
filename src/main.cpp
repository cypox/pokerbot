#include <iostream>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
  game g(8);
  g.run();

  const card five[5] = {
    {0, 10},
    {0, 11},
    {0, 12},
    {0, 13},
    {0, 14}
  };

  hand h(five);
  std::cout << h << std::endl;
  h.rank_hand();
  return 0;
}
