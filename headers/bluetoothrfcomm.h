#ifndef BLUETOOTHRFCOMM_H
#define BLUETOOTHRFCOMM_H

/* Copyright (c) 2020 [Rick de Bondt] - bluetoothrfcomm.h
 *
 * This file contains functions to open a rfcomm connection so the bluetooth
 * keyboard can communicate with our machine.
 *
 * */

#include <vector>
#include <iostream>


/**
 * @brief The clsBluetoothRfComm class
 *
 * Will create the rfcomm socket /dev/rfcomm0 so a serial connection can be
 * opened to /dev/rfcomm0
 */
class clsBluetoothRfComm
{
public:
  /**
   * This will create the rfcomm socket /dev/rfcomm0 so a serial connection can
   * be opened to /dev/rfcomm0
   * @param aDeviceNumber - The number of the device to bind to (usually 0)
   */
  clsBluetoothRfComm(int16_t aDeviceNumber);

  // Do not allow copy or move assignments
  clsBluetoothRfComm(const clsBluetoothRfComm&) = delete;
  clsBluetoothRfComm operator=(const clsBluetoothRfComm&) = delete;
  clsBluetoothRfComm(clsBluetoothRfComm&&) = delete;
  clsBluetoothRfComm& operator=(clsBluetoothRfComm&&) = delete;

  ~clsBluetoothRfComm();

  /**
   * Configures a serial socket for bluetooth serial communication
   * @param aBluetoothAddress - The bt address the socket needs to listen to
   * @note Must be called before using any of the other functions!
   * @return true if configuring the bluetooth serial socket has succeeded
   */
  bool ConfigureDevice(const std::string& aBluetoothAddress);

  /**
   * Releases a device from rfcomm
   */
  void ReleaseDevice();

  /**
   * Deconfigures the RfComm device
   */
  void DeconfigureDevice();

private:
  int mCtl = 0;
  int16_t mDeviceNumber = 0;
  bool mDeviceConfigured = false;
};

#endif // BLUETOOTHCOMM_H
