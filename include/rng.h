#pragma once

#include <random>


class rng {
public:
  rng(int min, int max) {
    _e = std::default_random_engine(_r());
    _uniform_dist = std::uniform_int_distribution<int>(min, max);
  }

  template<typename T>
  T get()
  {
    return _uniform_dist(_e);
  }

private:
  std::random_device _r;
  std::default_random_engine _e;
  std::uniform_int_distribution<int> _uniform_dist;
};
