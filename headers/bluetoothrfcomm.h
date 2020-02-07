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

class clsBluetoothRfComm
{
public:
  clsBluetoothRfComm(int aDeviceNumber);
  ~clsBluetoothRfComm();

  /**
   * @brief ConfigureDevice
   * Configures a serial socket for bluetooth serial communication
   * @param aBluetoothAddress - The bt address the socket needs to listen to
   * @note Must be called before using any of the other functions!
   * @return true if configuring the bluetooth serial socket has succeeded
   */
  bool ConfigureDevice(const std::string& aBluetoothAddress);

  /**
   * @brief ReleaseDevice
   * Releases a device from rfcomm
   */
  void ReleaseDevice();

  /**
   * @brief DeconfigureDevice
   * Deconfigures the RfComm device
   */
  void DeconfigureDevice();

private:
  int mCtl = 0;
  int mDeviceNumber;
  bool mDeviceConfigured;
};

#endif // BLUETOOTHCOMM_H
