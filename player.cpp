/*
 * MIT License
 *
 * Copyright (c) 2017 Dmytro Meleshko
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <avr/io.h>
#include "./ports.h"
#include "./player.h"
#include "./timer.h"
#include "./melody.h"

uint16_t player::playingNoteFrequencies[SIMULTANEOUS_NOTES];
uint32_t player::playingNotePhases[SIMULTANEOUS_NOTES];
uint8_t player::playingNotesCount;

void player::setup() {
  SETD(PORTA_D6);
  SETD(PORTA_D7);
  SETD(PORTA_D8);
  SETD(PORTA_D9);
  SETD(PORTA_D10);
  SETD(PORTA_D11);
  SETD(PORTA_D12);
  SETD(PORTA_D13);

  // Setting up 8-bit timer on port D6
  TCCR0A = (bit(COM0A0+1)) | (bit(WGM00)) | (bit(WGM01));  // fast PWM, clear OC0 on compare match
  TCCR0B = (1 << CS00);                                  // no prescaller
}

void player::clearNotes() {
  playingNotesCount = 0;
  CLRP(PORTA_D7);
  CLRP(PORTA_D8);
  CLRP(PORTA_D9);
  CLRP(PORTA_D10);
  CLRP(PORTA_D11);
  CLRP(PORTA_D12);
  CLRP(PORTA_D13);
}

void player::addNote(uint8_t key, uint16_t frequency) {
  playingNoteFrequencies[playingNotesCount] = frequency;
  playingNotesCount++;

  uint8_t led = key * 7 / PACKED_FREQUENCIES_LENGTH;
  switch (led) {
    case 0:
      SETP(PORTA_D7);
      break;
    case 1:
      SETP(PORTA_D8);
      break;
    case 2:
      SETP(PORTA_D9);
      break;
    case 3:
      SETP(PORTA_D10);
      break;
    case 4:
      SETP(PORTA_D11);
      break;
    case 5:
      SETP(PORTA_D12);
      break;
    case 6:
      SETP(PORTA_D13);
      break;
  }
}

void player::play() {
  uint8_t pmwValue = 0;

  for (int i = 0; i < playingNotesCount; i++) {
    uint16_t freq = playingNoteFrequencies[i];
    uint32_t phase = playingNotePhases[i];
    phase += freq;
    playingNotePhases[i] = phase;
    pmwValue += (phase & SAMPLE_RATE_MASK) < HALF_SAMPLE_RATE ? 0 : 60;
  }

  OCR0A = pmwValue;
}
