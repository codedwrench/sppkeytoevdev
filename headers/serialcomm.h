#ifndef SERIALCOMM_H
#define SERIALCOMM_H

/* Copyright (c) 2020 [Rick de Bondt] - serialcomm.h
 *
 * This file contains the functions required to open a serial connection.
 */

#include <memory>
#include <libserialport.h>

/**
 * @brief The clsSerialComm class
 * Contains the functions required to open a serial connection.
 * This will open /dev/rfcomm0 so serial characters can be picked up and send
 * through to the virtual keyboard
 */
class clsSerialComm
{
public:
    /**
     * @brief clsSerialComm
     *
     * Constructor of clsSerialComm, takes a portname argument. This is the
     * location of your serialport, e.g. /dev/rfcomm0
     *
     * @param aPortName
     */
    clsSerialComm(const std::string &aPortName);
    ~clsSerialComm();

    /**
     * @brief ConfigureDevice
     *
     * Configures the serial port so it can be read.
     * @note Must be called before using any of the read functions!
     * @return true if configuring the serial port has succeeded
     */
    bool ConfigureDevice();

    /**
     * @brief DeconfigureDevice
     *
     * Deconfigures the serial port.
     */
    void DeconfigureDevice();

    /**
     * @brief ReadBytes
     *
     * Reads as many bytes from the serial port as possible.
     * @param aBuffer - Buffer to put the bytes into
     * @param aBufferSize - The size of the buffer
     * @return Amount of bytes read
     */
    unsigned int ReadBytes(uint8_t *aBuffer, size_t aBufferSize);

private:
    bool CheckError(enum sp_return aResult);

    const std::string mPortName;
    struct sp_port* mPort;
};

#endif