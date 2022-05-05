#include <iostream>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
  game g(8);
  g.run();
  return 0;
}
