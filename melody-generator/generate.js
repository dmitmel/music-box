#!/usr/bin/env node

const melodyLength = 41;

console.log('#define MELODY_LENGTH %d', melodyLength);

const offsets = [];
for (let i = 0; i < melodyLength; i++) offsets.push(8);
console.log('const PROGMEM uint8_t noteOffsets[MELODY_LENGTH] = {%s};', offsets.join(', '));

const keys = [];
for (let i = 0; i < melodyLength; i++) keys.push(i);
console.log('const PROGMEM uint8_t noteKeys[MELODY_LENGTH] = {%s};', keys.join(', '));

const durations = [];
for (let i = 0; i < melodyLength; i++) durations.push(8);
console.log('const PROGMEM uint8_t noteDurations[MELODY_LENGTH] = {%s};', durations.join(', '));
