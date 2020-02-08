#ifndef KEYBOARD_DEFINES_H
#define KEYBOARD_DEFINES_H
#include <cstdint>

/* Copyright (c) 2020 [Rick de Bondt] - keyboard_defines.h
 *
 * This file contains the hex-codes the HP IPaq foldable BT-Keyboard sends.
 * It has a press and release code for every key, release is always 0x80 higher
 *
 * */


static const uint8_t cKeyReleaseOffset = static_cast<uint8_t>(0x80);

// Special keys, order
static const uint8_t cEsc          = static_cast<uint8_t>(0x08);
static const uint8_t cBackspace    = static_cast<uint8_t>(0x71);
static const uint8_t cTab          = static_cast<uint8_t>(0x0d);
static const uint8_t cDelete       = static_cast<uint8_t>(0x66);
static const uint8_t cCapsLock     = static_cast<uint8_t>(0x58);
static const uint8_t cEnter        = static_cast<uint8_t>(0x5a);
static const uint8_t cLeftShift    = static_cast<uint8_t>(0x12);
static const uint8_t cRightShift   = static_cast<uint8_t>(0x59);
static const uint8_t cLeftCtrl     = static_cast<uint8_t>(0x14);
static const uint8_t cFn           = static_cast<uint8_t>(0x02);
static const uint8_t cLeftWin      = static_cast<uint8_t>(0x07);
static const uint8_t cLeftAlt      = static_cast<uint8_t>(0x10);
static const uint8_t cRightAlt     = static_cast<uint8_t>(0x13);
static const uint8_t cSpacebar     = static_cast<uint8_t>(0x5c);
static const uint8_t cUp           = static_cast<uint8_t>(0x28);
static const uint8_t cLeft         = static_cast<uint8_t>(0x5e);
static const uint8_t cDown         = static_cast<uint8_t>(0x60);
static const uint8_t cRight        = static_cast<uint8_t>(0x2f);

// Number keys
static const uint8_t cOne          = static_cast<uint8_t>(0x16);
static const uint8_t cTwo          = static_cast<uint8_t>(0x1e);
static const uint8_t cThree        = static_cast<uint8_t>(0x26);
static const uint8_t cFour         = static_cast<uint8_t>(0x25);
static const uint8_t cFive         = static_cast<uint8_t>(0x2e);
static const uint8_t cSix          = static_cast<uint8_t>(0x36);
static const uint8_t cSeven        = static_cast<uint8_t>(0x3d);
static const uint8_t cEight        = static_cast<uint8_t>(0x3e);
static const uint8_t cNine         = static_cast<uint8_t>(0x46);
static const uint8_t cZero         = static_cast<uint8_t>(0x45);

// Alphabetic keys
static const uint8_t cA            = static_cast<uint8_t>(0x1c);
static const uint8_t cB            = static_cast<uint8_t>(0x32);
static const uint8_t cC            = static_cast<uint8_t>(0x21);
static const uint8_t cD            = static_cast<uint8_t>(0x23);
static const uint8_t cE            = static_cast<uint8_t>(0x24);
static const uint8_t cF            = static_cast<uint8_t>(0x2b);
static const uint8_t cG            = static_cast<uint8_t>(0x34);
static const uint8_t cH            = static_cast<uint8_t>(0x33);
static const uint8_t cI            = static_cast<uint8_t>(0x43);
static const uint8_t cJ            = static_cast<uint8_t>(0x3b);
static const uint8_t cK            = static_cast<uint8_t>(0x42);
static const uint8_t cL            = static_cast<uint8_t>(0x4b);
static const uint8_t cM            = static_cast<uint8_t>(0x3a);
static const uint8_t cN            = static_cast<uint8_t>(0x31);
static const uint8_t cO            = static_cast<uint8_t>(0x44);
static const uint8_t cP            = static_cast<uint8_t>(0x4d);
static const uint8_t cQ            = static_cast<uint8_t>(0x15);
static const uint8_t cR            = static_cast<uint8_t>(0x2d);
static const uint8_t cS            = static_cast<uint8_t>(0x1b);
static const uint8_t cT            = static_cast<uint8_t>(0x2c);
static const uint8_t cU            = static_cast<uint8_t>(0x3c);
static const uint8_t cV            = static_cast<uint8_t>(0x2a);
static const uint8_t cW            = static_cast<uint8_t>(0x1d);
static const uint8_t cX            = static_cast<uint8_t>(0x22);
static const uint8_t cY            = static_cast<uint8_t>(0x35);
static const uint8_t cZ            = static_cast<uint8_t>(0x1a);

// Misc characters
static const uint8_t cGrave        = static_cast<uint8_t>(0x0e);
static const uint8_t cMinus        = static_cast<uint8_t>(0x4e);
static const uint8_t cEqual        = static_cast<uint8_t>(0x55);
static const uint8_t cLeftBrace    = static_cast<uint8_t>(0x54);
static const uint8_t cRightBrace   = static_cast<uint8_t>(0x5b);
static const uint8_t cBackSlash    = static_cast<uint8_t>(0x5d);
static const uint8_t cSemiColon    = static_cast<uint8_t>(0x4c);
static const uint8_t cApostrophe   = static_cast<uint8_t>(0x52);
static const uint8_t cComma        = static_cast<uint8_t>(0x41);
static const uint8_t cDot          = static_cast<uint8_t>(0x49);
static const uint8_t cSlash        = static_cast<uint8_t>(0x4a);

#endif
