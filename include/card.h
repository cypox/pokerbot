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

enum suit_t {
  SPADES = 0,
  HEARTS = 1,
  CLUBS = 2,
  DIAMONDS = 3
};

enum face_t {
  _2 = 2,
  _3 = 3,
  _4 = 4,
  _5 = 5,
  _6 = 6,
  _7 = 7,
  _8 = 8,
  _9 = 9,
  _T = 10,
  _J = 11,
  _Q = 12,
  _K = 13,
  _A = 14
};

// use struct and bit-fields to reduce card size
class card {
public:
  card()
  {
    _suit = SPADES;
    _face = _A;
  }

  card(face_t f, suit_t s) : _face(f), _suit(s) {}

  card(char f, char s) : _face((face_t)f), _suit((suit_t)s) {}

  card (const char* s) {
    if (s[0] >= '2' && s[0] <= '9') _face = (face_t) (s[0] - '0');
    else if (s[0] == 'A' || s[0] == 'a') _face = _A;
    else if (s[0] == 'K' || s[0] == 'k') _face = _K;
    else if (s[0] == 'Q' || s[0] == 'q') _face = _Q;
    else if (s[0] == 'J' || s[0] == 'j') _face = _J;
    if (s[1] == 'S' || s[1] == 's') _suit = SPADES;
    else if (s[1] == 'H' || s[1] == 'h') _suit = HEARTS;
    else if (s[1] == 'D' || s[1] == 'd') _suit = DIAMONDS;
    else if (s[1] == 'C' || s[1] == 'c') _suit = CLUBS;
  }

  card (const std::string s) {
    card(s.c_str());
  }

  bool operator!=(const card& other)
  {
    return other._face != _face || other._suit != _suit;
  }

  friend std::ostream& operator<<(std::ostream& s, const card& c)
  {
    switch(c._face)
    {
      case _2: s << "2"; break;
      case _3: s << "3"; break;
      case _4: s << "4"; break;
      case _5: s << "5"; break;
      case _6: s << "6"; break;
      case _7: s << "7"; break;
      case _8: s << "8"; break;
      case _9: s << "9"; break;
      case _T: s << "T"; break;
      case _J: s << "J"; break;
      case _Q: s << "Q"; break;
      case _K: s << "K"; break;
      case _A: s << "A"; break;
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
  suit_t _suit;
  face_t _face;
};
