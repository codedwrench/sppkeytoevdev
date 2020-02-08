#include <iostream>
#include <chrono>
#include <thread>

#include "virtualkeyboard.h"
#include "bluetoothrfcomm.h"
#include "serialcomm.h"

#define RFCOMM_DEVICE_NUMBER 0
#define BT_ADDRESS "00:0f:6f:00:36:bd"
#define SERIAL_PORT "/dev/rfcomm0"
#define CYCLE_TIME_MS 12

void
HandleReconnect(clsSerialComm& aSerialComm, clsBluetoothRfComm& aBtComm)
{
  /* We add a little bit of sleep time so any characters still coming from the
   * keyboard will cause this prompt to show a bunch of times */
  std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_TIME_MS));

  std::cout << "Press 'y' to reconnect" << std::endl;
  if(getchar() == 'y')
  {
    std::cout << "Reconnecting keyboard!"
              << std::endl;
    aBtComm.ConfigureDevice(BT_ADDRESS);
    aSerialComm.ConfigureDevice();
  }
  else
  {
    HandleReconnect(aSerialComm, aBtComm);
  }
}

int
main()
{
  clsKeymap lKeyMap;
  clsBluetoothRfComm lBtComm(RFCOMM_DEVICE_NUMBER);
  clsSerialComm lSerialComm(SERIAL_PORT);
  clsVirtualKeyboard lKeyboard(lKeyMap);

  if(!lBtComm.ConfigureDevice(BT_ADDRESS))
  {
    std::cerr << "Setting up bluetooth socket failed" << std::endl;
  }

  if(!lSerialComm.ConfigureDevice())
  {
    std::cerr << "Setting up serial communication failed" << std::endl;
  }

  // Set-up a virtual keyboard
  if(lKeyboard.ConfigureDevice())
  {
    unsigned int lByteCount = 0;
    std::array<uint8_t, 100> lBuffer = {};

    /* Lets flush any buffers sent to the serial port after a small delay
     * otherwise the initial data sent by the BT-keyboard will press some
     * random keys */
    std::this_thread::sleep_for(
          std::chrono::milliseconds(CYCLE_TIME_MS));

    // We're done with the setup, start looping!
    while(true)
    {
      lByteCount = lSerialComm.ReadBytes(lBuffer.data(), sizeof(lBuffer));
      if(lByteCount > 0)
      {
        for(unsigned int lCount = 0; lCount < lByteCount; lCount++)
        {
          if(lBuffer.at(lCount) != 0xff && lBuffer.at(lCount) != 0x00)
          {
            const std::pair<int,bool>& lKey =
                lKeyMap.ConvertKey(lBuffer.at(lCount));

            // Only send a key out if it's an actual key
            if(lKey.first != 0 && lKey.first != KEY_BLUETOOTH)
            {
              lKeyboard.SendKeyEvent(lKey.first, lKey.second);
            }
            else if(lKey.first == KEY_BLUETOOTH)
            {
              // Kill the connection so the keyboard can sleep
              lSerialComm.DeconfigureDevice();
              lBtComm.DeconfigureDevice();

              /* Stop FN-key since the keyboard isn't going to do that itself
               * anymore */
              lKeyMap.SetFnKeyPressed(false);

              /* TODO: Make reconnection possible, properly.
               * Possibly with some kind of connection handler which would
               * handle bluetooth and serial, so main doesn't have to, also try
               * to detect incoming connection from BT-keyboard, since a
               * keyboard press is hard to do without a keyboard */
              HandleReconnect(lSerialComm, lBtComm);
            }
          }
        }
      }
      /* Use a 12 millisecond cycle time, this will keep the CPU less
       * busy and since a frame is 16.7 ms on a 60hz monitor should keep
       * us within 2 frames assuming the code above this and the keyboard
       * reaction time takes less than 21.4 milliseconds, would be
       * unsuitable for gaming, but whoever uses this kind of keyboard
       * for that purpose anyway! */
      std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_TIME_MS));
    }
  }
  else
  {
    std::cerr << "Setting up the virtual keyboard failed" << std::endl;
  }

  return 0;
}
