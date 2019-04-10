#include "Arduino.h"
#include <avr/pgmspace.h>
const long interval = 37;
const int songlength = 363; //# of lines
const PROGMEM byte musicarray[][8] = {
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00001000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00100000,B00010010,B00000000,B00000000,B00000000,B00001000},
{B00000000,B00010000,B00100000,B00010000,B00010000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000001,B00000010,B00000001,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000001,B00000010,B00000000,B00100000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00001000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00000000,B00000000,B00001000,B00000000,B00010000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00001000,B00000000,B00010000,B00001000,B00000000,B00001011},
{B00000000,B00000001,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000},
{B00000000,B00000100,B00001000,B00001000,B10000000,B00000000,B00000000,B00000111},
{B00000000,B00000100,B00001000,B00001000,B00000100,B00000000,B00000000,B00000111},
{B00000000,B00000100,B00000000,B01000000,B10000000,B10000000,B00000000,B00000111},
{B00000000,B00000100,B00000000,B01000000,B10000000,B00000000,B00000000,B00000000},
{B00000000,B00000100,B00000000,B01000000,B10000000,B00001000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00000010,B00000000,B00000011},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00000010,B00000000,B00001011},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000},
{B00000000,B00000001,B00000010,B00000001,B00100000,B00000000,B00000000,B00000111},
{B00000000,B00000001,B00000010,B00000001,B00000001,B00000000,B00000000,B00000111},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00010000,B00000000,B00000111},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00000000,B00000000,B00000000},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000001,B00000000,B00000011},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000000,B01000000,B00000111},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000001,B00000000,B00001100},
{B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00001000,B00010000,B10001000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000010,B00100100,B00000010,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B01000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00001000,B00010000,B10001000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000010,B00100100,B00000010,B00000000,B00001100},
{B00000000,B00000000,B00000000,B01000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100010,B00000000,B00001111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B10000000,B00000000,B00010000,B00001001,B00000000,B00000111},
{B00000000,B00000000,B01000000,B00000000,B00001000,B00000100,B10000000,B00000011},
{B00000000,B00000000,B00100000,B00000000,B00000100,B00000010,B01000000,B00001011},
{B00000000,B00000000,B10000000,B00000000,B00000100,B00000010,B01000000,B00000111},
{B00000000,B00000001,B00000000,B00000000,B00000100,B00000010,B01000000,B00001000},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000100},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000010},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000111},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000100},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000100},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100000,B00000000,B00000111},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000011},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00001011},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00010000,B00100000,B00010000,B00010000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001011},
{B00000000,B00010000,B00000100,B00010010,B00010001,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00010100,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B10000001,B00000000,B10000000,B10000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00001111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000011},
{B00000000,B00000000,B10000000,B00000000,B10010000,B10001000,B00000000,B00001000},
{B00000000,B00000000,B10000000,B00000000,B10010000,B10100000,B00000000,B00000011},
{B00000000,B00000001,B00000000,B00000001,B00100001,B00100000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00000011},
{B00000000,B00000010,B00000000,B00000010,B01000010,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000100,B00000000,B00000100,B10000100,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00000000,B00000000,B00000010},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00000000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001011},
{B00000000,B00000100,B00000001,B00000100,B10000100,B01000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B01000000,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000101,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00100000,B00000000,B00000010},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00100000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00100000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B00001000,B00100100,B00100000,B01000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000100},
{B00000000,B00000000,B10000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000000,B00000000,B10000000,B00000000,B00000000,B00100000,B00000000,B00000011},
{B00000000,B00000001,B00000000,B00000000,B00000000,B00100000,B00000000,B00000111},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000011},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00001011},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000011},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00001011},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000100},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000010},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000100},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100000,B00000000,B00000111},
{B00000000,B00010000,B00100000,B00010000,B00010000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001100},
{B00000000,B00010000,B00000100,B00010010,B00010001,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010100,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B10000001,B00000000,B10000000,B10000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00001111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000011},
{B00000000,B00000000,B10000000,B00000000,B10010000,B10001000,B00000000,B00000111},
{B00000000,B00000000,B10000000,B00000000,B10010000,B10100000,B00000000,B00000011},
{B00000000,B00000001,B00000000,B00000001,B00100001,B00100000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00000011},
{B00000000,B00000010,B00000000,B00000010,B01000010,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000100},
{B00000000,B00000100,B00000000,B00000100,B10000100,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00000000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001100},
{B00000000,B00000100,B00000001,B00000100,B10000100,B01000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B01000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000101,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00100000,B00000000,B00001011},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00100000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B00001000,B00100100,B00100000,B01000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000000,B00000000,B10000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000000,B00000000,B10000000,B00000000,B00000000,B00100000,B00000000,B00000011},
{B00000000,B00000001,B00000000,B00000000,B00000000,B00100000,B00000000,B00000111},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00010000,B00100000,B00010010,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00100000,B00010000,B00010000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000001,B00000010,B00000001,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000001,B00000010,B00000000,B00100000,B00000000,B00001000},
{B00000000,B00000000,B00001000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00000000,B00000000,B00001000,B00000000,B00010000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00001000,B00000000,B00010000,B00001000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000001,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000100,B00001000,B00001000,B10000000,B00000000,B00000000,B00000111},
{B00000000,B00000100,B00001000,B00001000,B00000100,B00000000,B00000000,B00000111},
{B00000000,B00000100,B00000000,B01000000,B10000000,B10000000,B00000000,B00001000},
{B00000000,B00000100,B00000000,B01000000,B10000000,B00001000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00000010,B00000000,B00000011},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00000010,B00000000,B00001100},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000001,B00000010,B00000001,B00100000,B00000000,B00000000,B00000111},
{B00000000,B00000001,B00000010,B00000001,B00000001,B00000000,B00000000,B00001000},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00010000,B00000000,B00000111},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000001,B00000000,B00000011},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000000,B01000000,B00000111},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00001000,B00010000,B00010000,B00000001,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B10000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00001000,B00010000,B10001000,B00000000,B00001100},
{B00000000,B00000000,B00000000,B00000010,B00100100,B00000010,B00000000,B00001011},
{B00000000,B00000000,B00000000,B01000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00001000,B00010000,B10001000,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000010,B00100100,B00000010,B00000000,B00001011},
{B00000000,B00000000,B00000000,B01000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100010,B00000000,B00001111},
{B00000000,B00000000,B00100000,B01000000,B00100000,B00100010,B00000000,B00000000},
{B00000000,B00000000,B10000000,B00000000,B00010000,B00001001,B00000000,B00000111},
{B00000000,B00000000,B01000000,B00000000,B00001000,B00000100,B10000000,B00000011},
{B00000000,B00000000,B00100000,B00000000,B00000100,B00000010,B01000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00000010,B01000000,B00000000},
{B00000000,B00000000,B10000000,B00000000,B00000100,B00000010,B01000000,B00000111},
{B00000000,B00000001,B00000000,B00000000,B00000100,B00000010,B01000000,B00000111},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000011},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00001011},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000000},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100000,B00000000,B00000111},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000011},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00001011},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000010},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000000},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000100},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000010},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000000},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00100100,B00100000,B00000000,B00001000},
{B00000000,B00010000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00100001,B00000000,B00000011},
{B00000000,B00010000,B00000000,B00000000,B00000001,B00100001,B00000000,B00001011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00100000,B00000000,B00000000,B00000001,B00100000,B01000000,B00000011},
{B00000000,B00100000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000000,B00010000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000001,B00000000,B01000000,B00000011},
{B00000000,B10000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000010,B00000000,B00000000,B00000000,B00000001,B00001000,B01000000,B00000100},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000001,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00001000,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00001000,B00000000,B00000000,B00000000,B00010000,B00001000,B00000000,B00000011},
{B00001000,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000011},
{B00000010,B00000000,B00000000,B00000000,B00000000,B00000010,B00000000,B00000111},
{B00000000,B00000000,B00000000,B00000000,B00000100,B00100010,B00000000,B00000011},
{B00000000,B00000100,B00000000,B00000000,B00000100,B00100010,B00000000,B00000011},
{B00000000,B00000100,B00000000,B00000000,B00000000,B00000001,B00000000,B00001000},
{B00000000,B00000000,B00100000,B00000000,B00000100,B00000010,B01000000,B00000011},
{B00000000,B00000000,B10000000,B00001000,B00010000,B00001001,B00000000,B00001111},
{B00000000,B00000000,B10000000,B00001000,B00010000,B00001001,B00000000,B00000101},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00100010,B00000000,B00001000},
{B00000000,B00000001,B00000000,B00010000,B00100000,B00001000,B00000000,B00001000},
{B00000000,B00000100,B00000000,B00001000,B10010000,B00100000,B00000000,B00001111},
{B00000000,B00000100,B00000000,B00001000,B10010000,B00100000,B00000000,B00000001},
{B00000000,B00000000,B10000001,B00000000,B00000010,B00000000,B00000000,B00001111},
{B00000000,B00000000,B10000001,B00000000,B00000010,B00000000,B00000000,B00000001},
{B00000000,B00010000,B00100000,B00010010,B00000001,B00000000,B00000000,B00001111},
{B00000000,B00010000,B00100000,B00010010,B00000001,B00000000,B00000000,B00001111},
{B00000000,B00010000,B00100000,B00010010,B00000001,B00000000,B00000000,B00000100},
{B00000000,B00010000,B00100000,B00010000,B00010001,B00000000,B00000000,B00001111},
{B00000000,B00010000,B00100000,B00010000,B00010001,B00000000,B00000000,B00001111},
{B00000000,B00010000,B00100000,B00010000,B00010001,B00000000,B00000000,B00000011},
{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}};