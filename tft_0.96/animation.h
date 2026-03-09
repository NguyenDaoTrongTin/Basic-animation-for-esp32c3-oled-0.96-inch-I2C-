#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include <Arduino.h>
#include <pgmspace.h>

extern const uint8_t* const animation1[] PROGMEM;
extern const uint8_t* const animation2[] PROGMEM;
extern const uint8_t* const animation3[] PROGMEM;
extern const uint8_t* const* const bufferAnimation[] PROGMEM;

extern const uint16_t FRAME_COUNT1;
extern const uint16_t FRAME_COUNT2;
extern const uint16_t FRAME_COUNT3;
extern const uint16_t FRAME_COUNT[];

#endif
