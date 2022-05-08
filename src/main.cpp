#include <iostream>
#include <thread>
#include <future>
#include <ctime>

#include "../include/game.h"


const int total_threads = 4;
const int thread_iters = 250;

int main(int argc, char** argv)
{
  std::srand(std::time(0));
  //* -- test case 1 : AK suit vs AA
  auto run = [](int thread_iters) -> std::vector<int> {
    game g(2);
    std::vector<int> res(3, 0);
    for (int i = 0 ; i < thread_iters ; ++ i)
    {
      std::vector<int> winner = g.simulate_situation({
        { {"Ad"}, {"Kc"} },
        { {"As"}, {"Ah"} }
      });
      if (winner.size() == 1) res[winner[0]] ++;
      else res[2] ++;
    }
    return res;
  };

  int total_won_1(0), total_won_2(0), total_tie(0);
  int total_played(0);
  for (int th = 0 ; th < total_threads ; ++ th)
  {
    std::future<std::vector<int>> f = std::async(run, thread_iters);
    std::vector<int> tw = f.get();
    total_won_1 += tw[0];
    total_won_2 += tw[1];
    total_tie += tw[2];
    total_played += thread_iters;
  }
  std::cout << "won1: " << (100.*total_won_1 / total_played) << "%" << std::endl;
  std::cout << "won2: " << (100.*total_won_2 / total_played) << "%" << std::endl;
  std::cout << "tie : " << (100.*total_tie / total_played) << "%" << std::endl;
  //*/
  //* -- test case 1 : 27 offsuit vs all
  auto run2 = [](int thread_iters) -> int {
    game g(2);
    int res = 0;
    for (int i = 0 ; i < thread_iters ; ++ i)
    {
      res += g.simulate_hand(
        {"2s"},
        {"7h"}
      );
    }
    return res;
  };

  int total_won(0);
  total_played = 0;
  for (int th = 0 ; th < total_threads ; ++ th)
  {
    std::future<int> f = std::async(run2, thread_iters);
    total_won += f.get();
    total_played += thread_iters;
  }
  std::cout << "won: " << (100.*total_won / total_played) << "%" << std::endl;
  //*/
  
  //* test hand
  hand h(
    {"Ts"},
    {"Js"},
    {"Qs"},
    {"As"},
    {"Ks"}
  );
  std::cout << h << std::endl;
  h.rank_hand();
  //*/
  return 0;
}
