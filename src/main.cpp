#include <iostream>
#include <thread>
#include <future>
#include <ctime>

#include "../include/game.h"


const int total_threads = 1;
const int thread_iters = 2500;

int main(int argc, char** argv)
{
  std::srand(std::time(0));
  //* -- test case 1 : AK suit vs AA
  int total_players = (argc - 1) / 2;
  std::vector<int> results(total_players);
  auto run = [total_players, argv](int thread_iters) -> std::vector<int> {
    game g(total_players);
    std::vector<int> res(total_players, 0);
    std::vector<std::pair<card, card>> player_cards;
    for (int i = 0 ; i < total_players ; ++ i)
    {
      player_cards.emplace_back(argv[i*2+1], argv[i*2+2]);
    }

    for (int i = 0 ; i < thread_iters ; ++ i)
    {
      std::vector<int> winners = g.simulate_situation(player_cards);
      for (auto p : winners)
        res[p] ++;
    }
    return res;
  };

  std::vector<int> total_won(total_players, 0);
  int total_played(0);
  for (int th = 0 ; th < total_threads ; ++ th)
  {
    std::future<std::vector<int>> f = std::async(run, thread_iters);
    std::vector<int> tw = f.get();
    for (int i = 0 ; i < tw.size() ; ++ i)
      total_won[i] += tw[i];
    total_played += thread_iters;
  }
  for (int i = 0 ; i < total_players; ++ i)
  {
    std::cout << "player " << i << ": " << (100.*total_won[i] / total_played) << "%" << std::endl;
  }
  //*/
  /* -- test case 1 : 27 offsuit vs all
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
  
  /* test hand
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
