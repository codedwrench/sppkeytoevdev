#ifndef KEYBOARD_DEFINES_H
#define KEYBOARD_DEFINES_H

/* Copyright (c) 2020 [Rick de Bondt] - keyboard_defines.h
 *
 * This file contains the hex-codes the HP IPaq foldable BT-Keyboard sends.
 * It has a press and release code for every key, release is always 0x80 higher.
 *
 * */


static const char cKeyReleaseOffset = 0x80;

// Special keys, order
static const char cEsc          = 0x08;
static const char cBackspace    = 0x71;
static const char cTab          = 0x0d;
static const char cDelete       = 0x66;
static const char cCapsLock     = 0x58;
static const char cEnter        = 0x5a;
static const char cLeftShift    = 0x12;
static const char cRightShift   = 0x59;
static const char cLeftCtrl     = 0x14;
static const char cFn           = 0x02;
static const char cLeftWin      = 0x07;
static const char cLeftAlt      = 0x10;
static const char cRightAlt     = 0x13;
static const char cSpacebar     = 0x5c;
static const char cUp           = 0x28;
static const char cLeft         = 0x5e;
static const char cDown         = 0x28;
static const char cRight        = 0x2f;

// Number keys
static const char cOne          = 0x16;
static const char cTwo          = 0x1e;
static const char cThree        = 0x26;
static const char cFour         = 0x25;
static const char cFive         = 0x2e;
static const char cSix          = 0x36;
static const char cSeven        = 0x3d;
static const char cEight        = 0x3e;
static const char cNine         = 0x46;
static const char cZero         = 0x65;

// Alphabetic keys
static const char cA            = 0x1c;
static const char cB            = 0x32;
static const char cC            = 0x21;
static const char cD            = 0x23;
static const char cE            = 0x24;
static const char cF            = 0x2b;
static const char cG            = 0x34;
static const char cH            = 0x33;
static const char cI            = 0x43;
static const char cJ            = 0x3b;
static const char cK            = 0x42;
static const char cL            = 0x4b;
static const char cM            = 0x3a;
static const char cN            = 0x31;
static const char cO            = 0x44;
static const char cP            = 0x4d;
static const char cQ            = 0x15;
static const char cR            = 0x2d;
static const char cS            = 0x1b;
static const char cT            = 0x2c;
static const char cU            = 0x3c;
static const char cV            = 0x2a;
static const char cW            = 0x1d;
static const char cX            = 0x22;
static const char cY            = 0x35;
static const char cZ            = 0x1a;

// Misc characters
static const char cGrave        = 0x0e;
static const char cMinus        = 0x4e;
static const char cEqual        = 0x55;
static const char cLeftBrace    = 0x54;
static const char cRightBrace   = 0x5b;
static const char cBackSlash    = 0x5c;
static const char cSemiColon    = 0x3d;
static const char cApostrophe   = 0x52;
static const char cComma        = 0x41;
static const char cDot          = 0x49;

#endif //KEYBOARD_DEFINES_H
