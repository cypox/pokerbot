#include <iostream>
#include <thread>
#include <future>
#include <ctime>

#include "../include/game.h"


int main(int argc, char** argv)
{
  std::srand(std::time(0));
    auto run = [](int thread_iters) -> std::vector<int> {
    game g(2);
    std::vector<int> res(2, 0);
    for (int i = 0 ; i < thread_iters ; ++ i)
    {
      int winner = g.simulate_situation({
        { card(_T, DIAMONDS), card(_K, CLUBS) },
        { card(_2, SPADES), card(_7, HEARTS) }
      });
      res[winner] ++;
    }
    return res;
  };
  std::atomic<int> won(0);
  int total_won_1(0), total_won_2(0);
  int total_played(0);
  const int total_threads = 4;
  const int thread_iters = 2500;
  for (int th = 0 ; th < total_threads ; ++ th)
  {
    std::future<std::vector<int>> f = std::async(run, thread_iters);
    std::vector<int> tw = f.get();
    total_won_1 += tw[0];
    total_won_2 += tw[1];
    total_played += thread_iters;
  }
  std::cout << "won1: " << (100.*total_won_1 / total_played) << "%" << std::endl;
  std::cout << "won1: " << (100.*total_won_2 / total_played) << "%" << std::endl;
  /*
  auto run = [](int thread_iters) -> int {
    game g(2);
    int res = 0;
    for (int i = 0 ; i < thread_iters ; ++ i)
    {
      res += g.simulate_hand(
        card(_2, SPADES),
        card(_7, HEARTS)
      );
    }
    return res;
  };
  std::atomic<int> won(0);
  int total_won(0);
  int total_played(0);
  const int total_threads = 4;
  const int thread_iters = 250;
  for (int th = 0 ; th < total_threads ; ++ th)
  {
    std::future<int> f = std::async(run, thread_iters);
    total_won += f.get();
    total_played += thread_iters;
  }
  std::cout << "won: " << (100.*total_won / total_played) << "%" << std::endl;
  */

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
