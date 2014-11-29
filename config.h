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
    {0,6,0,5}, // ZWÖLF
    {6,7,0,4}, // EINS
    {4,7,0,4}, // ZWEI
    {0,7,0,4}, // DREI
    {6,4,0,4}, // VIER
    {4,6,0,4}, // FÜNF
    {4,9,0,5}, // SECHS
    {0,8,0,6}, // SIEBEN
    {0,9,0,4}, // ACHT
    {5,5,0,4}, // NEUN
    {2,5,0,4}, // ZEHN
    {6,8,0,3}  // ELF
};

const struct wordpos minutes[] = {
    {1,0,0,4}, // FÜNF
    {5,0,0,4}, // ZEHN
    {2,1,0,7}, // VIERTEL
    {1,2,0,7}, // ZWANZIG
    {1,4,0,4}, // HALB
    {4,3,0,4}, // NACH
    {1,3,0,3}, // VOR
    {0,0,1,5}  // PUNKT
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
};

const struct wordpos easteregg_leds[] = {
  {0,5,0,2}, {9,0,1,7}, {1,2,2,4}, {2,0,3,2}, {3,0,2,2}, {5,0,0,2}, {7,1,1,2}, {6,3,3,2}, {0,0,0,0}
};


const struct wordpos mode_led[] = {
  {},
  { 9,8,0,1 },
  { 9,9,0,1 }
};
#endif
