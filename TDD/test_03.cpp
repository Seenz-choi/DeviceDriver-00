#include <iostream>
#include <windows.h>

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
private:
    const int MULTI_READ_DELAY = 1; // 200
    const int MULTI_READ_TIMES = 5;
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int readData = 0;
    for (int i = 1; i < MULTI_READ_TIMES; i++) {
        readData |= m_hardware->read(address);
        Sleep(1);
    }
    if (readData != m_hardware->read(address))
        throw ReadFailException();

    return readData;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}