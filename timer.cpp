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
#include <avr/interrupt.h>
#include "./timer.h"
#include "./scheduler.h"
#include "./player.h"

time_t timer::currentTime;

void timer::setup() {
  // setting up 16-bit timer
  TCCR2A = 1 << WGM21;                    // CTC mode
  TCCR2B = 2 << CS20;                     // set prescaler to 8
  OCR2A = F_CPU >> SAMPLE_RATE_POW >> 3;  // 16,000,000 / 32,768 / 8 = 61
  TIMSK2 = 1 << OCIE2A;                   // interrupt on compare
}

ISR(TIMER2_COMPA_vect) {
  cli();

  static uint8_t samples;

  samples++;
  if (samples >= TEMPO_SAMPLES) {
    samples = 0;
    timer::currentTime++;
    scheduler::shouldUpdatePlayingNotes = true;
  }

  player::play();

  sei();
}

