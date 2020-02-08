#ifndef KEYMAP_H
#define KEYMAP_H

/* Copyright (c) 2020 [Rick de Bondt] - keymap.h
 *
 * This file contains the keymap between a bluetooth keyboard and its evdev
 * events
 *
 */

#include <vector>
#include <linux/uinput.h>
#include <map>

// Include the defines corresponding to your keyboard type
#include "keyboard_defines.h"

// Namespace containing constants for this class
namespace
clsKeymapNamespace {
  static const bool cPressed = true;
  static const bool cNotPressed = false;
} // clsKeymapNamespace

/**
 * The clsKeymap class contains a map with all of the bluetooth codes to
 * input-event-codes. It contains functions to return the appropriate eventcode
 * based on the bluetooth code.
 */
class
    clsKeymap
{
public:
  clsKeymap();

  /**
   * This function returns the entire keymap as a constant map
   * @return The entire keymap
   */
  const std::map<uint8_t, std::pair<unsigned int, bool>> &GetKeymap();

  /** @brief GetFnKeymap
   *
   * This function returns the entire FN keymap as a constant map
   * @return The entire keymap
   **/
  const std::map<uint8_t, std::pair<unsigned int, bool>>& GetFnKeymap();

  /**
   * This function returns an input event code and pressed state based on
   * bt-keycode
   * @return pair with pressed state and input event code, if code is not
   * found, will return {0, false}.
   */
  std::pair<unsigned int, bool> ConvertKey(uint8_t aKey);

  /**
   * This function gets wether keys should be held until the key is no longer
   * held (release keycode is sent), or if it should release immediately.
   */
  bool GetImmediateRelease() const;

  /**
   * This function allows you the set/reset the FN-key externally
   * @param aFnKeyPressed - Whether the FN-key should be pressed or not
   */
  void SetFnKeyPressed(bool aFnKeyPressed);
private:

  static std::map<uint8_t, std::pair<unsigned int, bool>> InitKeymap();
  static std::map<uint8_t, std::pair<unsigned int, bool>> InitFnKeymap();

  bool mFnKeyPressed = false;

  // This keymap translates the bluetooth inputs to libevdev scancodes
  const std::map<uint8_t, std::pair<unsigned int, bool>> mKeymap;

  /* This keymap translates the bluetooth inputs to libevdev scancodes when fn
   * is pressed */
  const std::map<uint8_t, std::pair<unsigned int, bool>> mFnKeymap;
};
#endif


