#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

/* Copyright (c) 2020 [Rick de Bondt] - keymap.h
 *
 * This file contains the functions corresponding to the virtual keyboard
 *
 */

#include "keymap.h"

/**
 * The clsVirtualKeyboard class creates a virtual keyboard which can send key-
 * events. Use this to send the keyboard codes from the bluetooth device to
 * the machine.
 */
class clsVirtualKeyboard
{
public:
  /**
   * Constructor of clsVirtualKeyboard, needs a keymap object to work
   * @param aKeyMap
   */
  clsVirtualKeyboard(clsKeymap& aKeyMap);
  ~clsVirtualKeyboard();

  // Do not allow move or copy assignments
  clsVirtualKeyboard(const clsVirtualKeyboard&) = delete;
  clsVirtualKeyboard operator=(const clsVirtualKeyboard&) = delete;
  clsVirtualKeyboard(clsVirtualKeyboard&&) = delete;
  clsVirtualKeyboard& operator=(clsVirtualKeyboard&&) = delete;

  /**
   * Configures a virtual keyboard that can be used to send keystrokes with.
   * @note Must be called before using any of the sendevent functions!
   * @return true if configuring the virtual keyboard has succeeded
   */
  bool ConfigureDevice();

  /**
   * Destroys virtual keyboard and free resources
   */
  void DeconfigureDevice();

  /**
   * Sends a key event with with the provided key
   * @see https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h
   * @param aKey
   * @param aState
   * @return true if sending the key event has succeeded
   */
  bool SendKeyEvent(int aKey, bool aState);

private:
  bool SendKey(int aKey, bool aState);

  clsKeymap& mKeyMap;
  struct libevdev *mDevice = nullptr;
  struct libevdev_uinput *mUserInputDevice = nullptr;
};

#endif
