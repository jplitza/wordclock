#ifndef WORDCLOCK_H
#define WORDCLOCK_H

struct position {
  const position* next; // pointer to next position to be lit after this one
  uint8_t x;
  uint8_t y;
};

struct wordlist {
  struct wordlist* next;
  const struct wordpos* wordpos;
};

struct wordpos {
  uint8_t x;           // start position x coordinate
  uint8_t y;           // start position y coordinate
  uint8_t vertical;    // true=vertical, false=horizontal
  uint8_t length;      // length in characters/positions
};
#endif
