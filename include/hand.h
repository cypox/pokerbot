#pragma once


class hand {
public:
  hand(card& _0, card& _1, card& _2, card& _3, card& _4)
  {
    _top_five[0] = _0;
    _top_five[1] = _1;
    _top_five[2] = _2;
    _top_five[3] = _3;
    _top_five[4] = _4;
  }

  hand(card cards[7])
  {
  }

  short rank_hand()
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
    return false;
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
