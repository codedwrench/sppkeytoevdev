#include <utility>

#include "serialcomm.h"
#include <iostream>

// Maximum time it may take to read a key
#define MAX_READ_TIME_MS 2

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
           CheckError(sp_set_baudrate(mPort, 9600)) &&
           CheckError(sp_set_bits(mPort, 8)) &&
           CheckError(sp_set_parity(mPort, SP_PARITY_NONE)) &&
           CheckError(sp_set_stopbits(mPort, 1)) &&
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
                                      MAX_READ_TIME_MS);

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
    char *lErrorMessage;

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
