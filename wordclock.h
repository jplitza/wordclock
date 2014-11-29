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

enum modes {
  MODE_NORMAL,
  MODE_HOURS,
  MODE_MINUTES,
  MODE_MAX
};

enum direction {
  DIR_H, // to the right
  DIR_V, // down
  DIR_R, // diagonally down right
  DIR_L  // diagonally down left
};

struct wordpos {
  uint8_t x;           // start position x coordinate
  uint8_t y;           // start position y coordinate
  direction orientation;  // orientation
  uint8_t length;      // length in characters/positions
};
#endif
