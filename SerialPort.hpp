#ifndef __SERIAL_PORT_HPP__
#define __SERIAL_PORT_HPP__
// * Read using readSerialData(char* bytes, size_t length)
// * Write using writeSerialData(const char* bytes, size_t length)
// * Remember to flush potentially buffered data when necessary
// * Close serial port when done
#include <unistd.h> //ssize_t
#include <vector>
#include <string>
int openAndConfigureSerialPort(const char* portPath, int baudRate);
bool serialPortIsOpen();
ssize_t flushSerialData();
ssize_t writeSerialData(const char* bytes, size_t length);
ssize_t readSerialData(char* bytes, size_t length);
ssize_t closeSerialPort(void);
ssize_t enumSerialPort(std::vector<std::string>& ports);
#endif //__SERIAL_PORT_HPP__