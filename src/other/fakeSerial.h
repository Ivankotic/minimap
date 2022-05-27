#pragma once
/*
class fakeSerial
{
public:
    fakeSerial(int j) {
        _value = "";
    }
    void write(char new_val) {
        _value += (char)new_val;
    }
    String get_value() {
        return _value;
    }
private:
    String _value;
};*/

class fakeSerial : public Stream
{
public:
    fakeSerial(int j)
    {
        _value = "";
    }
    void write(const char *s)
    {
        _value += s;
    }
    String get_value()
    {
        return _value;
    }
    void begin(unsigned long baud, uint32_t config = 60, int8_t rxPin = -1, int8_t txPin = -1, bool invert = false, unsigned long timeout_ms = 20000);
    void end();
    void updateBaudRate(unsigned long baud);
    int available(void);
    int availableForWrite(void);
    int peek(void);
    int read(void);
    size_t read(uint8_t *buffer, size_t size);
    inline size_t read(char *buffer, size_t size)
    {
        size_t o = 0;
        return o;
    }
    void flush(void);
    void flush(bool txOnly);

    size_t write(uint8_t n)
    {
        _value += (char)n;
        size_t r = 0;
        return r;
    }

    size_t write(const uint8_t *buffer, size_t size)
    {
        _value += (char *)buffer;
        return size;
    }

    size_t write(const char *buffer, size_t size)
    {
        _value += String(buffer);
        size_t o = 0;
        return o;
    }
    size_t write(unsigned long n)
    {
        write((char *)n);
        size_t o = 0;
        return o;
    }
    size_t write(long n)
    {
        write((char *)n);
        size_t o = 0;
        return o;
    }
    size_t write(unsigned int n)
    {
        write((char *)n);
        size_t o = 0;
        return o;
    }
    size_t write(int n)
    {
        write((char *)n);
        size_t o = 0;
        return o;
    }

    uint32_t baudRate();
    operator bool() const;

    size_t setRxBufferSize(size_t);
    void setDebugOutput(bool);

    void setRxInvert(bool);
    size_t readBytes(char *buffer, size_t length)
    {
        size_t o = 0;
        return o;
    } // read chars from stream into buffer
    size_t readBytes(uint8_t *buffer, size_t length)
    {
        size_t o = 0;
        return o;
    }
    String readString()
    {
        String o = "";
        return o;
    }

    ~fakeSerial(){};

protected:
    int _uart_nr;
    uart_t *_uart;
    uint8_t _tx_pin;
    uint8_t _rx_pin;
    String _value;
};

void fakeSerial::begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert, unsigned long timeout_ms)
{
}

void fakeSerial::updateBaudRate(unsigned long baud)
{
    uartSetBaudRate(_uart, baud);
}

void fakeSerial::end()
{
}

size_t fakeSerial::setRxBufferSize(size_t new_size)
{
    size_t o = 0;
    return o;
}

void fakeSerial::setDebugOutput(bool en)
{
}

int fakeSerial::available(void)
{
    int o = 0;
    return o;
}
int fakeSerial::availableForWrite(void)
{
    size_t o = 0;
    return o;
}

int fakeSerial::peek(void)
{
    return -1;
}

int fakeSerial::read(void)
{
    return -1;
}

// read characters into buffer
// terminates if size characters have been read, or no further are pending
// returns the number of characters placed in the buffer
// the buffer is NOT null terminated.
size_t fakeSerial::read(uint8_t *buffer, size_t size)
{
    size_t o = 0;
    return o;
}

void fakeSerial::flush(void)
{
}

void fakeSerial::flush(bool txOnly)
{
}

uint32_t fakeSerial::baudRate()
{
    uint32_t o = 0;
    return o;
}
fakeSerial::operator bool() const
{
    return true;
}

void fakeSerial::setRxInvert(bool invert)
{
}
