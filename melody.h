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

#ifndef MUSIC_BOX_MELODY_H
#define MUSIC_BOX_MELODY_H

//#define NOTE_OFFSET(index) pgm_read_word(&noteOffsets[index])
//#define NOTE_KEY(index) pgm_read_word(&noteKeys[index])
//#define NOTE_DURATION(index) pgm_read_word(&noteDurations[index])
//
//#define MELODY_LENGTH 41
//const PROGMEM uint8_t noteOffsets[MELODY_LENGTH] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
//const PROGMEM uint8_t noteKeys[MELODY_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
//const PROGMEM uint8_t noteDurations[MELODY_LENGTH] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

const PROGMEM uint16_t packedOffsets[] = {0, 16, 32, 48, 64, 96, 144, 192};
#define PACKED_DELTA_TIMES_LENGTH 8
const PROGMEM uint16_t packedDurations[] = {46, 48, 62, 94, 160, 528, 720};
#define PACKED_DURATIONS_LENGTH 7
const PROGMEM uint16_t packedFrequencies[] = {165, 175, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 554, 587, 622, 659, 698, 740, 784, 831, 880, 988, 1047, 1109, 1175, 1245, 1319, 1480, 1760};
#define PACKED_FREQUENCIES_LENGTH 34
const unsigned int PROGMEM packedNotes[] = {19, 28, 4, 211, 28, 4, 339, 28, 4, 339, 25, 4, 211, 28, 4, 856, 543, 532, 2516, 521, 465, 25, 9, 398, 20, 6, 393, 17, 2, 398, 22, 7, 336, 24, 9, 335, 23, 8, 206, 22, 7, 1358, 1044, 1030, 1300, 1052, 1038, 1304, 1055, 1041, 281, 32, 18, 342, 29, 16, 1752, 1567, 1553, 342, 28, 14, 337, 25, 11, 210, 26, 13, 208, 24, 9, 401, 25, 9, 398, 20, 6, 393, 17, 2, 398, 22, 7, 336, 24, 9, 335, 23, 8, 206, 22, 7, 1358, 1044, 1030, 1300, 1052, 1038, 1304, 1055, 1041, 281, 32, 18, 342, 29, 16, 1752, 1567, 1553, 342, 28, 14, 337, 25, 11, 210, 26, 13, 208, 24, 9, 386, 348, 31, 219, 30, 9, 218, 29, 216, 27, 206, 217, 28, 199, 209, 21, 210, 22, 212, 25, 14, 334, 22, 14, 209, 25, 7, 210, 26, 194, 348, 31, 219, 30, 6, 218, 29, 216, 27, 201, 217, 28, 14, 349, 31, 33, 349, 31, 33, 221, 31, 33, 329, 322, 348, 31, 219, 30, 9, 218, 29, 216, 27, 206, 217, 28, 199, 209, 21, 210, 22, 212, 25, 14, 334, 22, 14, 209, 25, 7, 210, 26, 194, 341, 27, 10, 402, 26, 12, 401, 25, 14, 393, 201, 322, 322, 348, 31, 219, 30, 9, 218, 29, 216, 27, 206, 217, 28, 199, 209, 21, 210, 22, 212, 25, 14, 334, 22, 14, 209, 25, 7, 210, 26, 194, 348, 31, 219, 30, 6, 218, 29, 216, 27, 201, 217, 28, 14, 349, 31, 33, 349, 31, 33, 221, 31, 33, 329, 322, 348, 31, 219, 30, 9, 218, 29, 216, 27, 206, 217, 28, 199, 209, 21, 210, 22, 212, 25, 14, 334, 22, 14, 209, 25, 7, 210, 26, 194, 341, 27, 10, 402, 26, 12, 401, 25, 14, 393, 201, 322, 341, 25, 1, 213, 25, 341, 25, 5, 341, 25, 215, 26, 10, 340, 28, 9, 209, 25, 337, 22, 2, 206, 20, 320, 341, 25, 1, 213, 25, 341, 25, 5, 341, 25, 215, 26, 10, 1748, 1564, 201, 386, 384, 341, 25, 1, 213, 25, 341, 25, 5, 341, 25, 215, 26, 10, 340, 28, 9, 209, 25, 337, 22, 2, 206, 20, 320, 339, 28, 4, 211, 28, 4, 339, 28, 4, 339, 25, 4, 211, 28, 4, 856, 543, 532, 2516, 521, 465, 25, 9, 398, 20, 6, 393, 17, 2, 398, 22, 7, 336, 24, 9, 335, 23, 8, 206, 22, 7, 1358, 1044, 1030, 1300, 1052, 1038, 1304, 1055, 1041, 281, 32, 18, 342, 29, 16, 1752, 1567, 1553, 342, 28, 14, 337, 25, 11, 210, 26, 13, 208, 24, 9, 401, 25, 9, 398, 20, 6, 393, 17, 2, 398, 22, 7, 336, 24, 9, 335, 23, 8, 206, 22, 7, 1358, 1044, 1030, 1300, 1052, 1038, 1304, 1055, 1041, 281, 32, 18, 342, 29, 16, 1752, 1567, 1553, 342, 28, 14, 337, 25, 11, 210, 26, 13, 208, 24, 9, 409, 28, 2, 214, 25, 337, 20, 8, 201, 337, 21, 14, 338, 22, 7, 217, 29, 199, 217, 29, 210, 22, 14, 206, 199, 1364, 1048, 4, 1309, 1056, 1309, 1056, 71, 1245, 1056, 9, 1308, 1055, 141, 1178, 1053, 281, 28, 9, 214, 25, 201, 210, 22, 209, 20, 14, 206, 201, 345, 28, 2, 214, 25, 337, 20, 8, 201, 337, 21, 14, 338, 22, 7, 217, 29, 199, 217, 29, 210, 22, 14, 206, 199, 340, 24, 9, 218, 29, 346, 29, 9, 1242, 1053, 1033, 1305, 1052, 1035, 1304, 1050, 1037, 276, 25, 14, 209, 201, 209, 206, 2, 473, 28, 2, 214, 25, 337, 20, 8, 201, 337, 21, 14, 338, 22, 7, 217, 29, 199, 217, 29, 210, 22, 14, 206, 199, 1364, 1048, 4, 1309, 1056, 1309, 1056, 71, 1245, 1056, 9, 1308, 1055, 141, 1178, 1053, 281, 28, 9, 214, 25, 201, 210, 22, 209, 20, 14, 206, 201, 345, 28, 2, 214, 25, 337, 20, 8, 201, 337, 21, 14, 338, 22, 7, 217, 29, 199, 217, 29, 210, 22, 14, 206, 199, 340, 24, 9, 218, 29, 346, 29, 9, 1242, 1053, 1033, 1305, 1052, 1035, 1304, 1050, 1037, 276, 25, 14, 209, 201, 209, 206, 2, 467, 28, 4, 211, 28, 4, 339, 28, 4, 339, 25, 4, 211, 28, 4, 856, 543, 532, 2516, 521, 473, 28, 2, 214, 25, 337, 20, 8, 201, 337, 21, 14, 338, 22, 7, 217, 29, 199, 217, 29, 210, 22, 14, 206, 199, 1364, 1048, 4, 1309, 1056, 1309, 1056, 71, 1245, 1056, 9, 1308, 1055, 141, 1178, 1053, 281, 28, 9, 214, 25, 201, 210, 22, 209, 20, 14, 206, 201, 345, 28, 2, 214, 25, 337, 20, 8, 201, 337, 21, 14, 338, 22, 7, 217, 29, 199, 217, 29, 210, 22, 14, 206, 199, 340, 24, 9, 218, 29, 346, 29, 9, 1242, 1053, 1033, 1305, 1052, 1035, 1304, 1050, 1037, 276, 25, 14, 209, 201, 209, 206, 2, 465, 25, 9, 398, 20, 6, 397, 17, 2, 1366, 2066, 2055, 1304, 1302, 1301, 2066, 2051, 1303, 1301, 273, 3092, 3074, 208, 2769};
#define PACKED_NOTES_LENGTH 856

#define KEY_BITS 6
#define OFFSET_BITS 3
#define DURATION_BITS 3

#define NOTE_OFFSET(index) pgm_read_word(&packedOffsets[index])
#define NOTE_DURATION(index) pgm_read_word(&packedDurations[index])
#define NOTE_FREQUENCY(index) pgm_read_word(&packedFrequencies[index])
#define PACKED_NOTE(index) pgm_read_word(&packedNotes[index])

#define BITMASK(bits) ((1 << (bits)) - 1)
#define KEY_BITOFFSET 0
#define KEY_BITMASK BITMASK(KEY_BITS)
#define OFFSET_BITOFFSET (KEY_BITOFFSET + KEY_BITS)
#define OFFSET_BITMASK (BITMASK(OFFSET_BITS) << OFFSET_BITOFFSET)
#define DURATION_BITOFFSET (OFFSET_BITOFFSET + OFFSET_BITS)
#define DURATION_BITMASK (BITMASK(DURATION_BITS) << DURATION_BITOFFSET)

#endif  // MUSIC_BOX_MELODY_H
