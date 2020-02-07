#include <iostream>
#include <chrono>
#include <thread>

#include "virtualkeyboard.h"
#include "bluetoothrfcomm.h"
#include "serialcomm.h"

#define RFCOMM_DEVICE_NUMBER 0
#define BT_ADDRESS "00:0f:6f:00:36:bd"
#define SERIAL_PORT "/dev/rfcomm0"

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
        uint8_t lBuffer[100];

        // We're done with the setup, start looping!
        while(true)
        {
            lByteCount = lSerialComm.ReadBytes(lBuffer, sizeof(lBuffer));
            if(lByteCount > 0)
            {
                for(unsigned int i = 0; i < lByteCount; i++)
                {
                    if(lBuffer[i] != 0xff && lBuffer[i] != 0x00)
                    {
                        const std::pair<int,bool>& lKey =
                                lKeyMap.ConvertKey(lBuffer[i]);

                        // Only send a key out if it's an actual key
                        if(lKey.first != 0 && lKey.first != KEY_BLUETOOTH)
                        {
                            lKeyboard.SendKeyEvent(lKey.first, lKey.second);
                        }
                        else if(lKey.first == KEY_BLUETOOTH)
                        {
                            // Kill the connection so the keyboard can sleep
                            lSerialComm.DeconfigureDevice();

                            /* Stop FN-key since the keyboard isn't going to do
                            that itself anymore */
                            lKeyMap.SetFnKeyPressed(false);

                            std::this_thread::sleep_for(
                                        std::chrono::seconds(60));

                            lSerialComm.ConfigureDevice();
                        }
                    }
                }
            }
        }
    }
    else
    {
        std::cerr << "Setting up the virtual keyboard failed" << std::endl;
    }

    return 0;
}
