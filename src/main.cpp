#include <iostream>
#include <thread>
#include <future>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
  std::atomic<int> won(0);
  auto run = []() -> int {
    game g(2);
    int res = 0;
    for (int i = 0 ; i < 100000 ; ++ i)
    {
      res += g.simulate_hand(
        card(_A, SPADES),
        card(_A, HEARTS)
      );
    }
    return res;
  };
  std::future<int> f1 = std::async(run);
  std::future<int> f2 = std::async(run);
  std::future<int> f3 = std::async(run);
  std::future<int> f4 = std::async(run);
  std::cout << "won: " << (100.*(f1.get() + f2.get() + f3.get() + f4.get()) / 400000.) << "%" << std::endl;

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
