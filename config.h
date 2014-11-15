#ifndef WORDCLOCK_CONFIG_H
#define WORDCLOCK_CONFIG_H

#include "wordclock.h"

// pin configuration
#define PIN_CLOCK       5
#define PIN_LATCH       4
#define PIN_DATA_X      3
#define PIN_DATA_Y      2
#define PIN_BUTTON_MODE 6
#define PIN_BUTTON_SET  7

// matrix size and orientation
#define LED_ROWS 10
#define LED_COLS 10
#define INVERT_X
#undef INVERT_Y
#undef MIRROR_X
#undef MIRROR_Y

#define UPDATE_INTERVAL 30000

// LED configuration
const struct wordpos hours[] = {
    {1,5,1,5}, // ZWÖLF
    {2,6,0,4}, // EINS
    {0,6,0,4}, // ZWEI
    {5,4,0,4}, // DREI
    {8,5,1,4}, // VIER
    {1,9,0,4}, // FÜNF
    {3,8,0,5}, // SECHS
    {2,7,0,6}, // SIEBEN
    {5,9,0,4}, // ACHT
    {4,5,0,4}, // NEUN
    {1,5,0,4}, // ZEHN
    {0,8,0,3}  // ELF
};

const struct wordpos minutes[] = {
    {0,0,0,4}, // FÜNF
    {5,0,0,4}, // ZEHN
    {1,1,0,7}, // VIERTEL
    {2,2,0,7}, // ZWANZIG
    {0,4,0,4}, // HALB
    {4,3,0,4}, // NACH
    {0,3,0,3}  // VOR
};

const struct wordpos digits[][5] = {
  { {0,0,0,3}, {0,1,1,3}, {2,1,1,3}, {0,4,0,3}, {} },
  { {1,0,1,5}, {}, {}, {}, {} },
  { {0,0,0,3}, {2,1,0,1}, {0,2,0,3}, {0,3,0,1}, {0,4,0,3} },
  { {0,0,0,3}, {2,1,0,1}, {0,2,0,3}, {2,3,0,1}, {0,4,0,3} },
  { {0,0,1,3}, {1,2,0,1}, {2,0,1,5}, {}, {} },
  { {0,0,0,3}, {0,1,0,1}, {0,2,0,3}, {2,3,0,1}, {0,4,0,3} },
  { {0,0,0,3}, {0,1,1,4}, {1,2,0,2}, {2,3,0,1}, {1,4,0,2} },
  { {0,0,0,3}, {2,1,1,4}, {}, {}, {} },
  { {0,0,0,3}, {0,1,1,4}, {1,2,0,1}, {1,4,0,1}, {2,1,1,4} },
  { {0,0,0,3}, {0,1,1,2}, {1,2,0,1}, {2,1,1,4}, {0,4,0,3} },
  { {0,2,0,2}, {5,1,1,5}, {3,3,0,5}, {9,0,1,7}, {9,9,0,1} }
};

const struct wordpos mode_led[] = {
  {},
  { 9,7,0,1 },
  { 9,8,0,1 }
};
#endif
