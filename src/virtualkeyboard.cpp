#include <libevdev/libevdev.h>
#include <libevdev/libevdev-uinput.h>
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

#include "virtualkeyboard.h"
#include "keymap.h"

clsVirtualKeyboard::clsVirtualKeyboard(clsKeymap& aKeyMap) : mKeyMap(aKeyMap)
{

}

clsVirtualKeyboard::~clsVirtualKeyboard()
{
  DeconfigureDevice();
}

bool
clsVirtualKeyboard::ConfigureDevice()
{
  bool lReturn = false;

  // Only configure a device if it hasn't been configured as of yet
  if(mDevice == nullptr)
  {
    mDevice = libevdev_new();

    libevdev_set_name(mDevice, "virtual-keyboard");
    libevdev_enable_event_type(mDevice, EV_KEY);

    // Enable events for every possible key
    for(auto& [lKey, lValue] : mKeyMap.GetKeymap())
    {
      /* Since every key is in the map twice to account for unpressed
       * states, only go through the pressed ones */
      if(lValue.second == clsKeymapNamespace::cPressed)
      {
        libevdev_enable_event_code(mDevice,
                                   EV_KEY,
                                   static_cast<unsigned int>(lValue.first),
                                   nullptr);
      }
    }
    for(auto& [lKey, lValue] : mKeyMap.GetFnKeymap())
    {
      libevdev_enable_event_code(mDevice,
                                 EV_KEY,
                                 static_cast<unsigned int>(lValue.first),
                                 nullptr);
    }

    int lErrorNumber =
        libevdev_uinput_create_from_device(mDevice,
                                           LIBEVDEV_UINPUT_OPEN_MANAGED,
                                           &mUserInputDevice);

    if(lErrorNumber != 0)
    {
      std::cerr << "VKEYBOARD: Could not create fake device: " << -lErrorNumber
                << ": " << strerror(-lErrorNumber) << std::endl;
    }
    else
    {
      lReturn = true;
    }
  }
  return lReturn;
}

void
clsVirtualKeyboard::DeconfigureDevice()
{
  if(mUserInputDevice != nullptr)
  {
    libevdev_uinput_destroy(mUserInputDevice);
    mUserInputDevice = nullptr;
  }

  if(mDevice != nullptr)
  {
    libevdev_free(mDevice);
    mDevice = nullptr;
  }
}

bool clsVirtualKeyboard::SendKey(int aKey, bool aState)
{
  bool lReturn = false;

  if(mUserInputDevice != nullptr)
  {
    int lErrorNumber = libevdev_uinput_write_event(mUserInputDevice,
                                                   EV_KEY,
                                                   aKey,
                                                   aState);

    if(lErrorNumber == 0)
    {
      lErrorNumber = libevdev_uinput_write_event(mUserInputDevice,
                                                 EV_SYN, SYN_REPORT,
                                                 0);
      if(lErrorNumber == 0)
      {
        lReturn = true;
      }
      else
      {
        std::cerr << "VKEYBOARD: Failure sending SYN_REPORT: " << -lErrorNumber
                  << ": " << strerror(-lErrorNumber) << std::endl;
      }
    }
    else
    {
      std::cerr << "VKEYBOARD: Failure sending event: " << -lErrorNumber
                << ": " << strerror(-lErrorNumber) << std::endl;
    }
  }
  return lReturn;
}

bool
clsVirtualKeyboard::SendKeyEvent(int aKey, bool aState)
{
  bool lReturn = SendKey(aKey, aState);

  if(mKeyMap.GetImmediateRelease())
  {
    SendKey(aKey, clsKeymapNamespace::cNotPressed);
  }

  return lReturn;
}
