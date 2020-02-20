#include <iostream>
#include <chrono>
#include <thread>

#include "../headers/virtualkeyboard.h"
#include "../headers/bluetoothcomm.h"

namespace MainConstants {
  constexpr uint8_t cBtChannel = 1;
  constexpr auto cBtAddress = "00:0f:6f:00:36:bd";
  constexpr auto cSerialPort = "/dev/rfcomm0";
  constexpr unsigned int cSerialBufferSize = 100;
  constexpr std::chrono::milliseconds cCycleTimeMs =
      std::chrono::milliseconds(12);
  constexpr std::chrono::milliseconds cDisconnectedCycleTimeMs =
      std::chrono::milliseconds(10000);
  constexpr std::chrono::seconds cTimeToSleepKeyboardS =
      std::chrono::seconds(60);
}

using namespace MainConstants;

int
main()
{
  /* Use a 12 millisecond cycle time, this will keep the CPU less
   * busy and since a frame is 16.7 ms on a 60hz monitor should keep
   * us within 2 frames assuming the code above this and the keyboard
   * reaction time takes less than 21.4 milliseconds, would be
   * unsuitable for gaming, but whoever uses this kind of keyboard
   * for that purpose anyway! */
  std::chrono::milliseconds lCycleTime = std::chrono::milliseconds(0);

  clsKeymap lKeyMap;
  clsBluetoothComm lBtComm(cBtChannel, cBtAddress);
  clsVirtualKeyboard lKeyboard(lKeyMap);

  if(lKeyboard.ConfigureDevice())
  {
    unsigned int lByteCount = 0;
    std::array<uint8_t, cSerialBufferSize> lBuffer = {};
    while(true)
    {
      if(!lBtComm.GetDeviceConnected())
      {
        /* Keep a slower cycle time when disconnected, we don't need to poll
         * that often when the device is disconnected */
        lCycleTime = cDisconnectedCycleTimeMs;
        lBtComm.ConnectToDevice();

        if(lBtComm.GetDeviceConnected())
        {
          lCycleTime = cCycleTimeMs;
        }
      }
      else
      {
        lByteCount = lBtComm.ReadBytes(lBuffer.data(), sizeof(lBuffer));
        if(lByteCount > 0)
        {
          for(unsigned int lCount = 0; lCount < lByteCount; lCount++)
          {
            // If there is valid data
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
                lBtComm.DeconfigureDevice();

                /* Stop FN-key since the keyboard isn't going to do that itself
                 * anymore */
                lKeyMap.SetFnKeyPressed(false);

                /* Stop it from reconnecting for about a minute, so keyboard
                 * disconnects */
                std::cout << "Main: Disconnected by hand, waiting 60 sec"
                          << std::endl;

                std::this_thread::sleep_for(cTimeToSleepKeyboardS);

                std::cout << "Main: Accepting connections again!"
                          << std::endl;
              }
            }
          }
        }
      }

      std::this_thread::sleep_for(lCycleTime);
    }
  }
  return 0;
}
