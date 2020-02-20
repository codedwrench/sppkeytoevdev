#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include "../headers/bluetoothcomm.h"

clsBluetoothComm::clsBluetoothComm(uint8_t aDeviceChannel,
                                   std::string aBluetoothAddress) :
  mDeviceChannel(aDeviceChannel),
  mBluetoothAddress(std::move(aBluetoothAddress))
{

}

clsBluetoothComm::~clsBluetoothComm()
{
  DeconfigureDevice();
}

bool
clsBluetoothComm::ConfigureDevice()
{
  bool lReturn = false;
  if(!mDeviceConfigured)
  {
    int lErrorCode = 0;

    mSocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
    lErrorCode = errno;
    if(mSocket >= 0)
    {
      mDeviceConfigured = true;
      lReturn = true;
    }
    else
    {
      std::cerr << "RFCOMM: Cannot create socket: " << lErrorCode << ": "
                << strerror(lErrorCode) << std::endl;
    }
  }
  return lReturn;
}


bool
clsBluetoothComm::ConnectToDevice()
{
  bool lReturn = false;
  if(!mDeviceConfigured)
  {
    ConfigureDevice();
  }
  else if(!mDeviceConnected)
  {
    int lErrorCode = 0;
    struct sockaddr_rc lDestAddr = {0,
                                    {{0, 0, 0, 0, 0, 0}},
                                    0};

    lDestAddr.rc_family = AF_BLUETOOTH;
    lDestAddr.rc_channel = mDeviceChannel;
    str2ba(mBluetoothAddress.c_str(), &lDestAddr.rc_bdaddr);

    int lStatus =
        connect(mSocket,
                reinterpret_cast<struct sockaddr*>(&lDestAddr),
                sizeof (lDestAddr));
    lErrorCode = errno;

    if(lStatus >= 0)
    {
      std::cout << "RFCOMM: Succesfully connected" << std::endl;
      lReturn = true;
      mDeviceConnected = true;
    }
    else
    {
     DeconfigureDevice();
      /* If host is down, don't complain, that would be annoying for
       * our retry mechanism */
      if(lErrorCode != EHOSTDOWN)
      {
        std::cerr << "RFCOMM: Cannot connect to device: "
                  << lErrorCode << ": " << strerror(lErrorCode)
                  << std::endl;
      }
    }
  }
  return lReturn;
}

void
clsBluetoothComm::DeconfigureDevice()
{
  if(mDeviceConnected)
  {
    std::cout << "RFCOMM: Device disconnected" << std::endl;
    mDeviceConnected = false;
  }
  close(mSocket);
  mSocket = -1;
  mDeviceConfigured = false;
}

unsigned int
clsBluetoothComm::ReadBytes(uint8_t* aBuffer, size_t aBufferSize)
{
  int lBytesWaiting = read(mSocket, aBuffer, aBufferSize);
  int lErrorCode = errno;
  if(lBytesWaiting >= 0 && static_cast<size_t>(lBytesWaiting) > aBufferSize)
  {
    lBytesWaiting = static_cast<int>(aBufferSize);
  }
  else if(lBytesWaiting < 0)
  {
    std::cerr << "RFCOMM: Cannot read socket: " << lErrorCode << ": "
              << strerror(lErrorCode) << std::endl;
    lBytesWaiting = 0;

    // If anything happened to the socket, the socket probably went bad
    DeconfigureDevice();
  }

  return static_cast<unsigned int>(lBytesWaiting);
}

bool
clsBluetoothComm::GetDeviceConnected() const
{
  return mDeviceConnected;
}





