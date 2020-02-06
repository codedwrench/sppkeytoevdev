#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

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
  int lErrorCode, lSuccess;

  mCtl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_RFCOMM);
  if(mCtl >= 0)
  {
    struct rfcomm_dev_req lRequest;
    memset(&lRequest, 0, sizeof (lRequest));

    lRequest.dev_id = mDeviceNumber;
    str2ba(aBluetoothAddress.c_str(), &lRequest.dst);
    lRequest.channel = 1;

    lSuccess = ioctl(mCtl, RFCOMMCREATEDEV, &lRequest);
    lErrorCode = errno;

    if(lSuccess >= 0)
    {
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
  return lReturn;
}

void
clsBluetoothRfComm::DeconfigureDevice()
{
  ReleaseDevice();
  close(mCtl);
}



