#include <iostream>
#include <chrono>
#include <thread>

#include "virtualkeyboard.h"
#include "bluetoothrfcomm.h"

#define RFCOMM_DEVICE_NUMBER 0
#define BT_ADDRESS "00:00:00:00:00:00"

int
main()
{
  clsKeymap lKeyMap;
  clsVirtualKeyboard lKeyboard(lKeyMap);
  clsBluetoothRfComm lComm(RFCOMM_DEVICE_NUMBER);

  // Set-up a virtual keyboard
  if(lKeyboard.ConfigureDevice())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    lKeyboard.SendKeyEvent(KEY_LEFTSHIFT, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_H, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_H, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_LEFTSHIFT, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_E, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_E, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_L, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_L, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_L, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_L, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_O, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_O, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_SPACE, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_SPACE, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_LEFTSHIFT, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_W, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_W, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_LEFTSHIFT, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_O, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_O, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_R, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_R, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_L, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_L, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_D, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_D, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_LEFTSHIFT, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_1, clsKeymapNamespace::cPressed);
    lKeyboard.SendKeyEvent(KEY_1, clsKeymapNamespace::cNotPressed);
    lKeyboard.SendKeyEvent(KEY_LEFTSHIFT, clsKeymapNamespace::cNotPressed);
  }
  else
  {
    std::cerr << "Setting up the virtual keyboard failed" << std::endl;
  }



  if(lComm.ConfigureDevice(BT_ADDRESS))
  {
    std::cout << "succeeded!" << std::endl;

  }
  else
  {
    std::cerr << "Setting up bluetooth socket failed" << std::endl;
  }

  return 0;
}
