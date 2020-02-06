#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

/* Copyright (c) 2020 [Rick de Bondt] - keymap.h
 *
 * This file contains the functions corresponding to the virtual keyboard
 *
 */

#include "keymap.h"

class clsVirtualKeyboard
{
public:
  /**
   * @brief clsVirtualKeyboard
   * Constructor of clsVirtualKeyboard, needs a keymap object to work
   * @param aKeyMap
   */
  clsVirtualKeyboard(clsKeymap& aKeyMap);

  ~clsVirtualKeyboard();

  /**
   * @brief ConfigureDevice
   * Configures a virtual keyboard that can be used to send keystrokes with.
   * @note Must be called before using any of the sendevent functions!
   * @return true if configuring the virtual keyboard has succeeded
   */
  bool ConfigureDevice();

  /**
   * @brief DeconfigureDevice
   * Destroys virtual keyboard and free resources
   */
  void DeconfigureDevice();

  /**
   * @brief SendKeyEvent
   * Sends a key event with with the provided key
   * @see https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
   * @param aKey
   * @param aState
   * @return true if sending the key event has succeeded
   */
  bool SendKeyEvent(int aKey, bool aState);

private:
  clsKeymap& mKeyMap;
  struct libevdev *mDevice = nullptr;
  struct libevdev_uinput *mUserInputDevice = nullptr;
};

#endif // VIRTUALKEYBOARD_H
