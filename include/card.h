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
  SPADES = 0,
  HEARTS = 1,
  CLUBS = 2,
  DIAMONDS = 3
};

enum face {
  _2 = 0,
  _3 = 1,
  _4 = 2,
  _5 = 3,
  _6 = 4,
  _7 = 5,
  _8 = 6,
  _9 = 7,
  _10 = 8,
  _J = 9,
  _Q = 10,
  _K = 11,
  _A = 12
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
      case 0: s << "2"; break;
      case 1: s << "3"; break;
      case 2: s << "4"; break;
      case 3: s << "5"; break;
      case 4: s << "6"; break;
      case 5: s << "7"; break;
      case 6: s << "8"; break;
      case 7: s << "9"; break;
      case 8: s << "T"; break;
      case 9: s << "J"; break;
      case 10: s << "Q"; break;
      case 11: s << "K"; break;
      case 12: s << "A"; break;
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

//private:
  suit _suit;
  face _face;
};
