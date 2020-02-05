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
 * @brief The clsKeymap class
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
     * @brief GetKeymap
     * This function returns the entire keymap as a constant map
     * @return The entire keymap
     */
  const std::map<char, std::pair<int, bool>>& GetKeymap();
private:

  const std::map<char, std::pair<int, bool>> InitKeymap();

  // This keymap translates the bluetooth inputs to libevdev scancodes
  const std::map<char, std::pair<int, bool>> mKeymap;

};
#endif


