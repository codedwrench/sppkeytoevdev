#include <utility>
#include <iostream>

#include "../headers/serialcomm.h"


namespace clsSerialCommNamespace {
  // Maximum time it may take to read a key
  constexpr unsigned int cMaxReadTimeMs = 2;

  constexpr unsigned int cBaudrate = 9600;
  constexpr unsigned int cBits = 8;
  constexpr unsigned int cStopBits = 1;

}

using namespace clsSerialCommNamespace;

clsSerialComm::clsSerialComm(std::string aPortName) :
    mPortName(std::move(aPortName))
{

}

clsSerialComm::~clsSerialComm()
{
    DeconfigureDevice();
}

bool
clsSerialComm::ConfigureDevice()
{
    bool lReturn = false;

    if(CheckError(sp_get_port_by_name(mPortName.c_str(), &mPort)))
    {
        std::cout << "SerialComm: Setting port to 9600 8N1, no flow control"
                  << std::endl;

        if(CheckError(sp_open(mPort, SP_MODE_READ_WRITE)) &&
           CheckError(sp_set_baudrate(mPort, cBaudrate)) &&
           CheckError(sp_set_bits(mPort, cBits)) &&
           CheckError(sp_set_parity(mPort, SP_PARITY_NONE)) &&
           CheckError(sp_set_stopbits(mPort, cStopBits)) &&
           CheckError(sp_set_flowcontrol(mPort, SP_FLOWCONTROL_NONE)))
        {
            lReturn = true;
        }
    }
    return lReturn;
}

void
clsSerialComm::DeconfigureDevice()
{
    CheckError(sp_close(mPort));
    sp_free_port(mPort);
}

void
clsSerialComm::FlushData() const
{
    sp_flush(mPort, SP_BUF_BOTH);
}

unsigned int
clsSerialComm::ReadBytes(uint8_t* aBuffer, size_t aBufferSize)
{
    auto lResult = static_cast<sp_return>(0);
    int lBytesWaiting = sp_input_waiting(mPort);

    if(lBytesWaiting > 0)
    {
        if(static_cast<size_t>(lBytesWaiting) > aBufferSize)
        {
            lBytesWaiting = static_cast<int>(aBufferSize);
        }

        lResult = sp_blocking_read(mPort,
                                   static_cast<void*>(aBuffer),
                                   static_cast<size_t>(lBytesWaiting),
                                   cMaxReadTimeMs);

        // Print possible errors;
        if(!CheckError(lResult))
        {
            lResult = static_cast<sp_return>(0);
        }
    }

    return static_cast<unsigned int>(lResult);
}

// Helper function for error handling.
bool
clsSerialComm::CheckError(enum sp_return aResult)
{
    bool lReturn = false;
    char* lErrorMessage = nullptr;

    switch (aResult) {
    case SP_ERR_ARG:
        std::cerr << "SerialComm: Invalid argument." << std::endl;
        break;
    case SP_ERR_FAIL:
        lErrorMessage = sp_last_error_message();
        std::cerr << "Error: Failed: " << lErrorMessage << std::endl;
        sp_free_error_message(lErrorMessage);
        break;
    case SP_ERR_SUPP:
        std::cerr << "SerialComm: Not supported." << std::endl;
        break;
    case SP_ERR_MEM:
        std::cerr << "SerialComm: Couldn't allocate memory." << std::endl;
        break;
    case SP_OK:
    default:
        lReturn = (aResult >= 0);
    }

    return lReturn;
}
