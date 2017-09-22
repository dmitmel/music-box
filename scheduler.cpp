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

#include <avr/pgmspace.h>
#include "scheduler.h"
#include "player.h"
#include "timer.h"
#include "melody.h"

bool scheduler::shouldUpdatePlayingNotes;

void updatePlayingNotes() {
  static int startI = 0;
  static time startTime = 0;
  for (; startI < PACKED_NOTES_LENGTH; ++startI) {
    uint16_t packedNote = PACKED_NOTE(startI);
    uint8_t offset = NOTE_OFFSET((packedNote & OFFSET_BITMASK) >> OFFSET_BITOFFSET);
    uint8_t duration = NOTE_DURATION((packedNote & DURATION_BITMASK) >> DURATION_BITOFFSET);

    if (timer::currentTime < startTime + offset + duration) break;
    startTime += duration;
  }

  int endI = startI;
  time endTime = startTime;
  for (; endI < PACKED_NOTES_LENGTH; ++endI) {
    uint16_t packedNote = PACKED_NOTE(endI);
    uint8_t offset = NOTE_OFFSET((packedNote & OFFSET_BITMASK) >> OFFSET_BITOFFSET);

    if (timer::currentTime < endTime + offset) break;
    endTime += offset;
  }

  time totalOffset = startTime;
  player::playingNotesCount = 0;
  for (int i = startI; i < endI && player::playingNotesCount < SIMULTANEOUS_NOTES; i++) {
    uint16_t packedNote = PACKED_NOTE(i);
    uint8_t offset = NOTE_OFFSET((packedNote & OFFSET_BITMASK) >> OFFSET_BITOFFSET);
    uint8_t duration = NOTE_DURATION((packedNote & DURATION_BITMASK) >> DURATION_BITOFFSET);

    if (i > startI) totalOffset += offset;

    if (totalOffset <= timer::currentTime && timer::currentTime < totalOffset + duration) {
      uint8_t key = (packedNote & KEY_BITMASK) >> KEY_BITOFFSET;
      uint16_t frequency = NOTE_FREQUENCY(key);
      player::displayNoteKey(key);
      player::playingNoteFrequencies[player::playingNotesCount] = frequency;
      ++player::playingNotesCount;
    }
  }
}

void scheduler::checkUpdates() {
  if (shouldUpdatePlayingNotes) {
    shouldUpdatePlayingNotes = false;
    player::resetLEDs();
    updatePlayingNotes();
  }
}
