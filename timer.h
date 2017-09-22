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

#ifndef MUSIC_BOX_TIMER_H
#define MUSIC_BOX_TIMER_H

#include <stdint.h>

// 2^15=32768 samples per second
#define SAMPLE_RATE_POW 15
#define SAMPLE_RATE (1u << SAMPLE_RATE_POW)
#define HALF_SAMPLE_RATE (SAMPLE_RATE >> 1)
#define SAMPLE_RATE_MASK (SAMPLE_RATE - 1)

typedef uint32_t time;

namespace timer {
  extern time currentTime;

  void setup();
}

#endif  // MUSIC_BOX_TIMER_H
