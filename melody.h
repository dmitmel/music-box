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

#ifndef MELODY_H_
#define MELODY_H_

#include <avr/pgmspace.h>
#include "./bits.h"

typedef uint32_t packed_note_t;

#define KEY_BITS 4
#define OFFSET_BITS 3
#define DURATION_BITS 3

const PROGMEM uint16_t packedOffsets[] = {0, 64, 192, 256, 512, };
#define PACKED_OFFSETS_LENGTH 5
const PROGMEM uint16_t packedDurations[] = {58, 173, 231, 462, 718, };
#define PACKED_DURATIONS_LENGTH 5
const PROGMEM uint16_t packedFrequencies[] = {220, 294, 370, 392, 440, 494, 554, 587, 659, 740, 784, 880, };
#define PACKED_FREQUENCIES_LENGTH 12
const PROGMEM packed_note_t packedNotes[] = {132, 36, 277, 513, 514, 308, 311, 438, 512, 515, 196, 36, 277, 512, 515, 308, 312, 439, 513, 514, 196, 36, 283, 513, 514, 313, 311, 310, 513, 515, 309, 186, 42, 281, 385, 386, 311, 312, 256, 259, 567, 513, 514, };
#define PACKED_NOTES_LENGTH 43

#define NOTE_OFFSET(index) pgm_read_word(&packedOffsets[index])
#define NOTE_DURATION(index) pgm_read_word(&packedDurations[index])
#define NOTE_FREQUENCY(index) pgm_read_word(&packedFrequencies[index])
#define PACKED_NOTE(index) pgm_read_word(&packedNotes[index])

#define KEY_BITOFFSET 0
#define KEY_BITMASK bitmask(KEY_BITS)
#define OFFSET_BITOFFSET (KEY_BITOFFSET + KEY_BITS)
#define OFFSET_BITMASK (bitmask(OFFSET_BITS) << OFFSET_BITOFFSET)
#define DURATION_BITOFFSET (OFFSET_BITOFFSET + OFFSET_BITS)
#define DURATION_BITMASK (bitmask(DURATION_BITS) << DURATION_BITOFFSET)

#endif  // MELODY_H_
