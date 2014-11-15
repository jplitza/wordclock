#include <arduino2.h> // fast digital I/O
#include <Time.h>
#include "wordclock.h"
#include "config.h"

#if (LED_COLS > LED_ROWS)
#define GRID_SIZE LED_COLS
#else
#define GRID_SIZE LED_ROWS
#endif

uint8_t modeButtonState = 0;
uint8_t setButtonState = 0;

enum modes {
  MODE_NORMAL,
  MODE_HOURS,
  MODE_MINUTES,
  MODE_MAX
} mode = MODE_NORMAL;

const char* modeNames[] = {"NORMAL", "HOURS", "MINUTES"};
uint8_t modeSetting[] = {0, 0, 0};
const uint8_t modeMax[] = {1, 12, 60};

unsigned long nextUpdate;
unsigned long nextRepeat;

const struct position* plist;

void light_position(const struct position* pos) {
  digitalWrite2(PIN_LATCH, LOW);
  for (uint8_t i = 0; i < GRID_SIZE; i++)  {
    digitalWrite2(PIN_CLOCK, LOW);	
    digitalWrite2(PIN_DATA_X,
#ifdef MIRROR_X
      GRID_SIZE - 1 - i
#else
      i
#endif
#ifdef INVERT_X
      !=
#else
      ==
#endif
      pos->x);
    digitalWrite2(PIN_DATA_Y,
#ifdef MIRROR_Y
      GRID_SIZE - 1 - i
#else
      i
#endif
#ifdef INVERT_Y
      !=
#else
      ==
#endif
      pos->y);
    digitalWrite2(PIN_CLOCK, HIGH);
  }
  digitalWrite2(PIN_LATCH, HIGH);  
}

void light_positions(const struct position* pos) {
  while(pos != NULL) {
    light_position(pos);
    pos = pos->next;
  }
}

const struct position* words2positions(const struct wordlist* cur) {
  struct position offset = {};
  return words2positions(cur, offset, NULL);
}

const struct position* words2positions(const struct wordlist* cur, const struct position offset, const struct position* pos) {
  while(cur != NULL) {
    for(uint8_t j = 0; j < cur->wordpos->length; j++) {
      struct position* newpos = (struct position*) malloc(sizeof(struct position));
      newpos->next = pos;

      newpos->x = cur->wordpos->x + (cur->wordpos->vertical? 0 : j) + offset.x;
      newpos->y = cur->wordpos->y + (cur->wordpos->vertical? j : 0) + offset.y;
      pos = newpos;
    }
    cur = cur->next;
  }
  return pos;
}

void free_list(const void* start) {
  while(start != NULL) {
    void* next = *((void**)start);
    free((void*)start);
    start = next;
  }
}

void print_words(struct wordlist* cur) {
  while(cur != NULL) {
    Serial.print("{");
    Serial.print(cur->wordpos->x);
    Serial.print(",");
    Serial.print(cur->wordpos->y);
    Serial.print(",");
    Serial.print(cur->wordpos->vertical);
    Serial.print(",");
    Serial.print(cur->wordpos->length);
    Serial.println("}");
    cur = cur->next;
  }
}

void print_positions(const struct position* pos) {
  while(pos != NULL) {
    Serial.print("(");
    Serial.print(pos->x);
    Serial.print(",");
    Serial.print(pos->y);
    Serial.println(")");
    pos = pos->next;
  }
}

void add_word(struct wordlist** cur, const struct wordpos* insert) {
  if(insert != NULL && insert->length > 0) {
    struct wordlist* ret = (struct wordlist*) malloc(sizeof(struct wordlist));
    ret->next = *cur;
    ret->wordpos = insert;
    *cur = ret;
  }
}

struct wordlist* minute2words(float minute) {
  struct wordlist* cur = NULL;
  int tmp = round(minute / 5) * 5;
  tmp = (tmp + 30) % 60 - 30; // shift [30,60) to [-30,0)
  if(abs(tmp) > 20) // HALB
    add_word(&cur, &minutes[4]);
  if(tmp % 30 != 0) {
    if((tmp > 0 && tmp <= 20) || tmp < -20) // NACH
      add_word(&cur, &minutes[5]);
    else // VOR
      add_word(&cur, &minutes[6]);
    add_word(&cur, &minutes[((abs(tmp)-5) % 20)/5]);
  }

  return cur;
}

const struct position* int2positions(int n) {
  struct wordlist* cur = NULL;
  const struct position* pos = NULL;
  struct position offset = { NULL, 5, 2 };
  for(uint8_t i = 0; i < 5; i++) {
    add_word(&cur, &digits[n % 10][i]);
  }
  pos = words2positions(cur, offset, NULL);
  free_list(cur);
  cur = NULL;
  offset.x = 1;
  for(uint8_t i = 0; i < 5; i++) {
    add_word(&cur, &digits[n / 10][i]);
  }
  pos = words2positions(cur, offset, pos);
  free_list(cur);
  return pos;
}

void test_lights() {
  test_lights(50);
}

void test_lights(int wait) {
  Serial.print("Testing lights (delay ");
  Serial.print(wait);
  Serial.println("ms)...");
  struct position pos = {NULL,0,0};
  int8_t dir = 1;
  for(pos.y = 0; pos.y < LED_ROWS; pos.y++) {
    for(; pos.x < LED_COLS; pos.x+=dir) { // we use unsigned integer overflow here!
      light_position(&pos);
      delay(wait);
    }
    pos.x -= dir;
    dir *= -1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_DATA_X, OUTPUT);
  pinMode(PIN_DATA_Y, OUTPUT);
  pinMode(PIN_CLOCK,  OUTPUT);
  pinMode(PIN_LATCH,  OUTPUT);
  pinMode(PIN_BUTTON_MODE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SET,  INPUT_PULLUP);
  mode = MODE_HOURS;
}

void loop() {
  if(!digitalRead2(PIN_BUTTON_MODE) != modeButtonState) {
    modeButtonState = !modeButtonState;
    if(modeButtonState) {
      mode = (modes) ((mode + 1) % MODE_MAX);
      Serial.print("Switched to mode ");
      Serial.println(modeNames[mode]);
      nextUpdate = millis();
      switch(mode) {
        case MODE_NORMAL:
          setTime(modeSetting[MODE_HOURS], modeSetting[MODE_MINUTES], 0, 0, 0, 0);
          break;
        case MODE_HOURS:
          modeSetting[mode] = hour() % 12;
          break;
        case MODE_MINUTES:
          modeSetting[mode] = minute();
          break;
        default:
          break;
      }
    }
  }
  if(!digitalRead2(PIN_BUTTON_SET) != setButtonState) {
    setButtonState = !setButtonState;
    if(setButtonState) {
      if(mode == MODE_NORMAL) {
        test_lights();
      } else {
        modeSetting[mode] = (modeSetting[mode] + 1) % modeMax[mode];
        nextUpdate = millis();
        if(!nextRepeat) {
          nextRepeat = millis() + 750;
        }
      }
    } else {
      nextRepeat = 0;
    }
  }
  if(mode != MODE_NORMAL && setButtonState && millis() >= nextRepeat) {
    modeSetting[mode] = (modeSetting[mode] + 1) % modeMax[mode];
    Serial.println(modeSetting[mode]);
    nextRepeat += 250;    
    nextUpdate = millis();
  }
  if(millis() >= nextUpdate) {
    free_list(plist);
    if(mode == MODE_NORMAL) {
      struct wordlist* wlist;
      float m = minute() + second() / 60.0;
      int h = hour();
      Serial.print(h);
      Serial.print(":");
      Serial.print(m);
      Serial.print(":");
      Serial.println(second());
      wlist = minute2words(m);
      add_word(&wlist, &hours[(h + (m >= 22.5? 1 : 0)) % 12]);
      nextUpdate += UPDATE_INTERVAL;
      plist = words2positions(wlist);
      free_list(wlist);
    } else {
      nextUpdate = (unsigned long) -1;
      plist = int2positions(modeSetting[mode]);
    }
  }
  light_positions(plist);
}
