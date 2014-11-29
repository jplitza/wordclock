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
    {0,6,DIR_H,5}, // ZWÖLF
    {6,7,DIR_H,4}, // EINS
    {4,7,DIR_H,4}, // ZWEI
    {0,7,DIR_H,4}, // DREI
    {6,4,DIR_H,4}, // VIER
    {4,6,DIR_H,4}, // FÜNF
    {4,9,DIR_H,5}, // SECHS
    {0,8,DIR_H,6}, // SIEBEN
    {0,9,DIR_H,4}, // ACHT
    {5,5,DIR_H,4}, // NEUN
    {2,5,DIR_H,4}, // ZEHN
    {6,8,DIR_H,3}  // ELF
};

const struct wordpos minutes[] = {
    {1,0,DIR_H,4}, // FÜNF
    {5,0,DIR_H,4}, // ZEHN
    {2,1,DIR_H,7}, // VIERTEL
    {1,2,DIR_H,7}, // ZWANZIG
    {1,4,DIR_H,4}, // HALB
    {4,3,DIR_H,4}, // NACH
    {1,3,DIR_H,3}, // VOR
    {0,0,DIR_V,5}  // PUNKT
};

const struct wordpos digits[][5] = {
  { {0,0,DIR_H,3}, {0,1,DIR_V,3}, {2,1,DIR_V,3}, {0,4,DIR_H,3}, {} },
  { {1,0,DIR_V,5}, {}, {}, {}, {} },
  { {0,0,DIR_H,3}, {2,1,DIR_H,1}, {0,2,DIR_H,3}, {0,3,DIR_H,1}, {0,4,DIR_H,3} },
  { {0,0,DIR_H,3}, {2,1,DIR_H,1}, {0,2,DIR_H,3}, {2,3,DIR_H,1}, {0,4,DIR_H,3} },
  { {0,0,DIR_V,3}, {1,2,DIR_H,1}, {2,0,DIR_V,5}, {}, {} },
  { {0,0,DIR_H,3}, {0,1,DIR_H,1}, {0,2,DIR_H,3}, {2,3,DIR_H,1}, {0,4,DIR_H,3} },
  { {0,0,DIR_H,3}, {0,1,DIR_V,4}, {1,2,DIR_H,2}, {2,3,DIR_H,1}, {1,4,DIR_H,2} },
  { {0,0,DIR_H,3}, {2,1,DIR_V,4}, {}, {}, {} },
  { {0,0,DIR_H,3}, {0,1,DIR_V,4}, {1,2,DIR_H,1}, {1,4,DIR_H,1}, {2,1,DIR_V,4} },
  { {0,0,DIR_H,3}, {0,1,DIR_V,2}, {1,2,DIR_H,1}, {2,1,DIR_V,4}, {0,4,DIR_H,3} },
};

const struct wordpos easteregg_leds[] = {
  {0,5,DIR_H,2}, {9,0,DIR_V,7}, {1,2,DIR_R,4}, {2,0,DIR_L,2}, {3,0,DIR_R,2}, {5,0,DIR_H,2}, {7,1,DIR_V,2}, {6,3,DIR_L,2}, {0,0,DIR_H,0}
};


const struct wordpos mode_led[] = {
  {},
  { 9,8,DIR_H,1 },
  { 9,9,DIR_H,1 }
};
#endif
