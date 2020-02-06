#ifndef BLUETOOTHCOMM_H
#define BLUETOOTHCOMM_H
#include <vector>
#include <iostream>
#include <dbus/dbus.h>

namespace clsBluetoothRfCommNamespace {
  static std::vector<std::string> cRfCommState = {
    "unknown",
    "connected",
    "clean",
    "bound",
    "listening",
    "connecting",
    "connecting",
    "config",
    "disconnecting",
    "closed"
  };
}
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
  DBusConnection *mDbusConnection;
};

#endif // BLUETOOTHCOMM_H
