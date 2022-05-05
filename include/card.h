#pragma once

#include <iostream>


// thanks to https://stackoverflow.com/questions/27133508/how-to-print-spades-hearts-diamonds-etc-in-c-and-linux
#if defined(_WIN32) || defined(__MSDOS__)
  #define SPADE   "\x06"
  #define CLUB    "\x05"
  #define HEART   "\x03"
  #define DIAMOND "\x04"
#else
  #define SPADE   "\xE2\x99\xA0"
  #define CLUB    "\xE2\x99\xA3"
  #define HEART   "\xE2\x99\xA5"
  #define DIAMOND "\xE2\x99\xA6"
#endif

enum suit {
  SPADES = 1,
  HEARTS = 2,
  CLUBS = 3,
  DIAMONDS = 4
};

enum face {
  _A = 1,
  _2 = 2,
  _3 = 3,
  _4 = 4,
  _5 = 5,
  _6 = 6,
  _7 = 7,
  _8 = 8,
  _9 = 9,
  _10 = 10,
  _J = 11,
  _Q = 12,
  _K = 13
};

// use struct and bit-fields to reduce card size
class card {
public:
  card()
  {
    _suit = SPADES;
    _face = _A;
  }

  card(char s, char f)
  {
    _suit = (suit)s;
    _face = (face)f;
  }

  friend std::ostream& operator<<(std::ostream& s, const card& c)
  {
    switch(c._face)
    {
      case 1: s << "A"; break;
      case 2: s << "2"; break;
      case 3: s << "3"; break;
      case 4: s << "4"; break;
      case 5: s << "5"; break;
      case 6: s << "6"; break;
      case 7: s << "7"; break;
      case 8: s << "8"; break;
      case 9: s << "9"; break;
      case 10: s << "T"; break;
      case 11: s << "J"; break;
      case 12: s << "Q"; break;
      case 13: s << "K"; break;
      default: s << "Unknown"; break;
    }

    switch (c._suit)
    {
      case HEARTS: s << HEART; break;
      case DIAMONDS: s << DIAMOND; break;
      case CLUBS: s << CLUB; break;
      case SPADES: s << SPADE; break;
      default: s << "Unknown"; break;
    }
    return s;
  }

private:
  suit _suit;
  face _face;
};
