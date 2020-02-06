#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <glib.h>

#include "bluetoothrfcomm.h"

using namespace clsBluetoothRfCommNamespace;

clsBluetoothRfComm::clsBluetoothRfComm(int aDeviceNumber) :
  mDeviceNumber(aDeviceNumber)
{

}

clsBluetoothRfComm::~clsBluetoothRfComm()
{
  DeconfigureDevice();
}

void
clsBluetoothRfComm::ReleaseDevice()
{
  struct rfcomm_dev_req lRequest;
  int lErrorCode, lSuccess;

  memset(&lRequest, 0, sizeof(lRequest));
  lRequest.dev_id = mDeviceNumber;

  lSuccess = ioctl(mCtl, RFCOMMRELEASEDEV, &lRequest);
  lErrorCode = errno;

  /* Don't care if the device doesn't exist,
     because then it's already released */
  if (lSuccess < 0 && lErrorCode != ENODEV)
  {
    std::cerr << "Cannot release device: " << lErrorCode << ": "
              << strerror(lErrorCode) << std::endl;
  }
}

bool
clsBluetoothRfComm::ConfigureDevice(const std::string& aBluetoothAddress)
{
  bool lReturn = false;
  if(!mDeviceConfigured)
  {
    int lErrorCode, lSuccess;

    mCtl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_RFCOMM);
    if(mCtl >= 0)
    {
      // Try to release any sockets
      ReleaseDevice();

      struct rfcomm_dev_req lRequest;
      memset(&lRequest, 0, sizeof (lRequest));

      lRequest.dev_id = mDeviceNumber;
      str2ba(aBluetoothAddress.c_str(), &lRequest.dst);
      lRequest.channel = 1;

      lSuccess = ioctl(mCtl, RFCOMMCREATEDEV, &lRequest);
      lErrorCode = errno;

      if(lSuccess >= 0)
      {
        mDeviceConfigured = true;
        lReturn = true;
      }
      else
      {
        std::cerr << "Cannot create device: " << lErrorCode << ": "
                  << strerror(lErrorCode) << std::endl;
      }
    }
    else
    {
      std::cerr << "Cannot open RFCOMM control socket" << std::endl;
    }
  }
  else
  {
    lReturn = true;
  }
  return lReturn;
}

void
clsBluetoothRfComm::DeconfigureDevice()
{
  // Only deconfigure the device if it has been made by us.
  if(mDeviceConfigured)
  {
    ReleaseDevice();
  }
  close(mCtl);
}



