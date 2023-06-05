#include <iostream>

class FlashMemoryDevice
{
public:
    virtual unsigned char read(long address) = 0;
    virtual void write(long address, unsigned char data) = 0;
};

class ReadFailException : public std::exception
{};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int readData = 0;
    for (int i = 0; i < 4; i++)
        readData |= m_hardware->read(address);
    if (readData != m_hardware->read(address))
        throw ReadFailException();

    return readData;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}