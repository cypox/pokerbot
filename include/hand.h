#pragma once


class hand {
public:
  hand(card _0, card _1, card _2, card _3, card _4)
  {
    _top_five[0] = _0;
    _top_five[1] = _1;
    _top_five[2] = _2;
    _top_five[3] = _3;
    _top_five[4] = _4;
    // sort the hand by face
    std::sort(_top_five, _top_five+5, [](const card& l, const card& r){
      return l._face > r._face;
    });
  }

  hand(card cards[7])
  {
    // demo here: http://jsfiddle.net/subskybox/r4mSF/
    bool has_next_combination = true;
    short best_hand_rank = 0;
    card best_five[5];
    short combination_index[5] = {0, 1, 2, 3, 4};
    int k = 5, n = 7;
    int i = 4; // start by increasing last index untill we reach the maximum
    int combi = 0;
    while (has_next_combination)
    {
      _top_five[0] = cards[combination_index[0]];
      _top_five[1] = cards[combination_index[1]];
      _top_five[2] = cards[combination_index[2]];
      _top_five[3] = cards[combination_index[3]];
      _top_five[4] = cards[combination_index[4]];
      //std::cout << "combi " << ++combi << ": " << *this << std::endl;
      //for (int j = 0 ; j < 5 ; ++ j) std::cout << combination_index[j]; std::cout << std::endl;
      short current_hand_index = rank_hand();
      if (ranks[current_hand_index] > best_hand_rank)
      {
        best_hand_rank = ranks[current_hand_index];
        std::copy(_top_five, _top_five+5, best_five);
      }
      // generate next combination in order: 01234, 01235, 01236, 01245, etc
      // by incrementing the digits from right to left
      i = 4;
      ++ combination_index[i];
      // max combinatio is 23456 so combination_index[i] should be less than or equal to: 2 + i
      while (i > 0 && combination_index[i] > 2 + i)
      {
        -- i; ++combination_index[i];
      }
      if (combination_index[0] > 2) has_next_combination = false;
      // increase remaining of the combination after reaching the end of the previous
      for (int j = i + 1; j < k; ++ j)
      {
        combination_index[j] = combination_index[j-1] + 1;
      }
    }
    std::copy(best_five, best_five+5, _top_five);
    // sort the hand by face
    std::sort(_top_five, _top_five+5, [](const card& l, const card& r){
      return l._face > r._face;
    });
  }

  short rank_hand() const
  {
    // full explanation is here:
    // https://www.codeproject.com/Articles/569271/A-Poker-hand-analyzer-in-JavaScript-using-bit-math
    // great thanks to the original author!
    short card_ranks(0);
    // 2,3,4,5,6	[0,0,0,0,0,0,0,0,1,1,1,1,1,0,0]
    // 2,4,6,7,9	[0,0,0,0,0,1,0,1,1,0,1,0,1,0,0]
    // 10,J,Q,K,A	[1,1,1,1,1,0,0,0,0,0,0,0,0,0,0]
    long long rank_repetitions(0);
    // Each 4 bits represent the number of repetitions of the rank starting from 2 (4 LSBs) to A (4 MSBs)
    // A,A,Q,Q,9 is represented as:
    // 0	0	1	1	0	0	0	0	0	0	1	1	0	0	0	0	0	0	0	0	0	0	0	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
    // A,A,J,J,J:
    // 0	0	1	1	0	0	0	0	0	0	0	0	0	1	1	1	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
    short suit_count[4] = {0, 0, 0, 0};
    bool is_flush = false;
    for (int i = 0 ; i < 5 ; ++ i)
    {
      is_flush = (++ suit_count[_top_five[i]._suit]) >= 5;
      auto f = _top_five[i]._face;
      card_ranks |= 1 << f;
      // get current card's face repetition
      char current_repetition = (rank_repetitions >> (f-2)*4) & 0x0F;
      // add 1 to the current card's face repetition
      current_repetition = (current_repetition << 1) | 1;
      // set the repetition back to the total repetitions
      rank_repetitions |= ((long long int)current_repetition << (f-2)*4);
    }
    short rank_index = 0;
    // card_ranks/(card_ranks&-card_ranks) gets the truncated values where the first '1' is the LSB
    // A straight only occurs if the five LSBs are ones, which can be checked by comparing to 31 (0b11111)
    // In order to include the straight A2345 (where A = 14), we check specifically with 0x403C which is the equivalent
    // binary representation of that hand
    // rank_repititions % 15 calcultates the number of repetitions of the same value
    rank_index = rank_repetitions%15 - ((card_ranks/(card_ranks&-card_ranks) == 31) || (card_ranks == 0x403C) ? 3 : 1);
    // We check if we have a flush or a royal flush (0x7C00)
    rank_index -= (is_flush) * ((card_ranks == 0x7C00) ? -5 : 1);

    return rank_index;
  }

  bool operator>(const hand& rhs)
  {
    if (ranks[rank_hand()] == ranks[rhs.rank_hand()])
    {
      int i = 0;
      while (i < 5 && _top_five[i]._face == rhs._top_five[i]._face) i++;
      if (i == 5) return false;
      else return _top_five[i]._face > rhs._top_five[i]._face;
    }
    else return ranks[rank_hand()] > ranks[rhs.rank_hand()];
  }

  bool operator==(const hand& rhs)
  {
    if (ranks[rank_hand()] == ranks[rhs.rank_hand()])
    {
      int i = 0;
      while (i < 5 && _top_five[i]._face == rhs._top_five[i]._face) i++;
      if (i == 5) return true;
    }
    return false;
  }

  hand operator=(const hand &other)
  {
    for (int i = 0 ; i < 5 ; ++ i) _top_five[i] = other._top_five[i];
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& s, const hand& h)
  {
    s << "["
      << h._top_five[0] << " "
      << h._top_five[1] << " "
      << h._top_five[2] << " "
      << h._top_five[3] << " "
      << h._top_five[4] << "]";
    return s;
  }

private:
  card _top_five[5];
  const std::string rank_title[11] = {"4 of a Kind", "Straight Flush", "Straight", "Flush", "High Card", 
                                      "1 Pair", "2 Pair", "Royal Flush", "3 of a Kind", "Full House", 
                                      "-Invalid-"};
  const short ranks[11] = {8, 9, 5, 6, 1, 2, 3, 10, 4, 7, 0};
};
