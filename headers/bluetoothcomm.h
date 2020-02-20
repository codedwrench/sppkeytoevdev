#ifndef BLUETOOTHCOMM_H
#define BLUETOOTHCOMM_H

/* Copyright (c) 2020 [Rick de Bondt] - bluetoothrfcomm.h
 *
 * This file contains functions to open a rfcomm connection so the bluetooth
 * keyboard can communicate with our machine.
 *
 * */

#include <array>
#include <iostream>
#include <vector>

/**
 * Will create the rfcomm socket /dev/rfcomm0 so a serial connection can be
 * opened to /dev/rfcomm0
 */
class clsBluetoothComm
{
public:
  /**
   * This will create the rfcomm socket /dev/rfcomm0 so a serial connection can
   * be opened to /dev/rfcomm0
   * @param aDeviceChannel - The channel to bind to (usually 1)
   * @param aBluetoothAddress - The bluetooth addess to connect to
   */
  clsBluetoothComm(uint8_t aDeviceChannel,
                   std::string aBluetoothAddress);

  // Do not allow copy or move assignments
  clsBluetoothComm(const clsBluetoothComm&) = delete;
  clsBluetoothComm operator=(const clsBluetoothComm&) = delete;
  clsBluetoothComm(clsBluetoothComm&&) = delete;
  clsBluetoothComm& operator=(clsBluetoothComm&&) = delete;

  ~clsBluetoothComm();


  /**
   * Configures a serial socket for bluetooth serial communication
   * *blocks* until connection is made with the keyboard
   * @note Must be called before using any of the other functions!
   * @return true if connecting the bluetooth socket has succeeded
   */
  bool ConnectToDevice();

  /**
   * Deconfigures the RfComm device
   */
  void DeconfigureDevice();

  /**
   * Reads as many bytes from the bluetooth serial port as possible.
   * @param aBuffer - Buffer to put the bytes into
   * @param aBufferSize - The size of the buffer
   * @return Amount of bytes read
   */
  unsigned int ReadBytes(uint8_t *aBuffer, size_t aBufferSize);

  /**
    * Checks if device is connected
    * @return State of connection
    **/
  bool GetDeviceConnected() const;

private:
  bool ConfigureDevice();

  uint8_t mDeviceChannel = 1;
  std::string mBluetoothAddress;
  int mSocket = -1;
  bool mDeviceConfigured = false;
  bool mDeviceConnected = false;
};

#endif // BLUETOOTHCOMM_H
