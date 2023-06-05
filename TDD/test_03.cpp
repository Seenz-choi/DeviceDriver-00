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
class WriteFailException : public std::exception
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
    const int MULTI_READ_DELAY = 200; // 200
    const int MULTI_READ_TIMES = 5;
private:
    int getMultiReadData(const long& address);
    bool IsValidReading(const long& address, const int& ReadedData);
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}


int DeviceDriver::read(long address)
{
	int multiReadData = getMultiReadData(address);
	if (IsValidReading(address, multiReadData))
        throw ReadFailException();

    return multiReadData;
}

void DeviceDriver::write(long address, int data)
{
    if (m_hardware->read(address) != 0xFF) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}

int DeviceDriver::getMultiReadData(const long& address)
{
    int readData = 0;
    for (int i = 1; i < MULTI_READ_TIMES; i++) {
        readData |= m_hardware->read(address);
        Sleep(1);
    }
    return readData;
}

bool DeviceDriver::IsValidReading(const long& address, const int& ReadedData)
{
    return ReadedData != m_hardware->read(address);
}