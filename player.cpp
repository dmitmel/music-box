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

#include <Arduino.h>
#include "player.h"
#include "timer.h"
#include "melody.h"

#define FIRST_LED_PIN 2
#define LED_COUNT 8
#define BUZZER_PIN 10

uint16_t player::playingNoteFrequencies[SIMULTANEOUS_NOTES];
uint32_t playingNotePhases[SIMULTANEOUS_NOTES];
uint8_t player::playingNotesCount;

void player::setup() {
  for (uint8_t led = 0; led < LED_COUNT; ++led)
    pinMode(FIRST_LED_PIN + led, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void player::resetLEDs() {
  for (uint8_t led = 0; led < LED_COUNT; ++led)
    digitalWrite(FIRST_LED_PIN + led, LOW);
}

void player::displayNoteKey(uint8_t key) {
  uint8_t led = key * LED_COUNT / PACKED_FREQUENCIES_LENGTH;
  digitalWrite(FIRST_LED_PIN + LED_COUNT - 1 - led, HIGH);
}

void player::play() {
  uint8_t pmwValue = 0;

  for (int i = 0; i < playingNotesCount; i++) {
    uint32_t freq = playingNoteFrequencies[i];
    uint32_t phase = playingNotePhases[i];
    phase += freq;
    playingNotePhases[i] = phase;
    pmwValue += (phase & SAMPLE_RATE_MASK) < HALF_SAMPLE_RATE ? 0 : 32;
  }

  analogWrite(BUZZER_PIN, pmwValue);
}
