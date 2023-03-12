#include "SerialPort.hpp"
#include "dir_iterate.h"
#include <chrono>
#include <fcntl.h> //open()
#include <stdio.h>
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#endif
#include <unistd.h> //write(), read(), close()
#include <errno.h> //errno
#include <cstring>

using namespace std::chrono;

#ifdef WIN32
static HANDLE handler = nullptr;
#else
//Serial port file descriptor
static const int SFD_UNAVAILABLE = -1;
static int sfd = SFD_UNAVAILABLE;
#endif

int openAndConfigureSerialPort(const char* portPath, int baudRate)
{
    
    //If port is already open, close it
    if (serialPortIsOpen())
    {
#ifdef WIN32
		CloseHandle(handler);
        handler = nullptr;
#else
        close(sfd);
#endif
    }
    
#ifdef WIN32
    handler = CreateFileA(static_cast<LPCSTR>(portPath),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (handler == INVALID_HANDLE_VALUE)
    {
        if (GetLastError() == ERROR_FILE_NOT_FOUND)
        {
            printf("ERROR: Handle was not attached.Reason : %s not available\n", portPath);
        }
        else
        {
            printf("ERROR!!!\n");
        }
        return -1;
    }
    else
    {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(handler, &dcbSerialParameters))
        {
            printf("Failed to get current serial parameters\n");
            CloseHandle(handler);
            handler = nullptr;
            return -1;
        }
        else
        {
            DWORD rate;
            switch (baudRate)
            {
                case 9600: rate = CBR_9600; break;
                case 19200: rate = CBR_19200; break;
                case 38400: rate = CBR_38400; break;
                case 57600: rate = CBR_57600; break;
                case 115200: rate = CBR_115200; break;
                default:
                    printf("Requested baud rate %d not currently supported. Defaulting to 9,600.\n", baudRate);
                    rate = CBR_9600;
                break;
            }
            dcbSerialParameters.BaudRate = rate;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set serial port parameters\n");
                CloseHandle(handler);
                handler = nullptr;
                return -1;
            }
            else
            {
                //this->connected = true;
                PurgeComm(handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
            }
        }
    }
    return 0;
#else
    //Open port, checking for errors
    sfd = open(portPath, (O_RDWR | O_NOCTTY | O_NDELAY));
    if (sfd == -1)
    {
        printf("Unable to open serial port: %s at baud rate: %d\n", portPath, baudRate);
        return sfd;
    }
    
    //Configure i/o baud rate settings
    struct termios options;
    tcgetattr(sfd, &options);
    switch (baudRate)
    {
        case 9600:
            cfsetispeed(&options, B9600);
            cfsetospeed(&options, B9600);
            break;
        case 19200:
            cfsetispeed(&options, B19200);
            cfsetospeed(&options,B19200);
            break;
        case 38400:
            cfsetispeed(&options, B38400);
            cfsetospeed(&options, B38400);
            break;
        case 57600:
            cfsetispeed(&options, B57600);
            cfsetospeed(&options, B57600);
            break;
        case 115200:
            cfsetispeed(&options, B115200);
            cfsetospeed(&options, B115200);
            break;
        default:
            printf("Requested baud rate %d not currently supported. Defaulting to 9,600.\n", baudRate);
            cfsetispeed(&options, B9600);
            cfsetospeed(&options, B9600);
            break;
    }
    
    //Configure other settings
    //Settings from:
    //  https://github.com/Marzac/rs232/blob/master/rs232-linux.c
    //
    options.c_iflag &= ~(INLCR | ICRNL);
    options.c_iflag |= IGNPAR | IGNBRK;
    options.c_oflag &= ~(OPOST | ONLCR | OCRNL);
    options.c_cflag &= ~(PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS);
    options.c_cflag |= CLOCAL | CREAD | CS8;
    options.c_lflag &= ~(ICANON | ISIG | ECHO);
    options.c_cc[VTIME] = 1;
    options.c_cc[VMIN]  = 0;
    
    //Apply settings
    //TCSANOW vs TCSAFLUSH? Was using TCSAFLUSH; settings source above
    //uses TCSANOW.
    if (tcsetattr(sfd, TCSANOW, &options) < 0)
    {
        printf("Error setting serial port attributes.\n");
        close(sfd);
        return -2; //Using negative value; -1 used above for different failure
    }
    return sfd;
#endif
}

bool serialPortIsOpen()
{
#ifdef WIN32
    return handler != nullptr;
#else
    return sfd != SFD_UNAVAILABLE;
#endif
}

milliseconds getSteadyClockTimestampMs()
{
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch());
}

ssize_t flushSerialData()
{    
    //For some reason, setting this too high can cause the serial port to not start again properly...
    float flushDurationMs = 150.0f;
    ssize_t result = 0;
    milliseconds startTimestampMs = getSteadyClockTimestampMs();
    while (getSteadyClockTimestampMs().count() - startTimestampMs.count() < flushDurationMs)
    {
        char buffer[1];
        result = readSerialData(buffer, 1);
        if (result < 0) {
            printf("readSerialData() failed. Error: %s", strerror(errno));
        }
    };
        
    return result;
}

//Returns -1 on failure, with errno set appropriately
ssize_t writeSerialData(const char* bytesToWrite, size_t numBytesToWrite)
{  
#ifdef WIN32
    DWORD bytesSend;
    COMSTAT status;
    DWORD errors;
    if (!WriteFile(handler, (void*) bytesToWrite, numBytesToWrite, &bytesSend, 0))
    {
        ClearCommError(handler, &errors, &status);
        return 0;
    }
    
    return bytesSend;
#else
    ssize_t numBytesWritten = write(sfd, bytesToWrite, numBytesToWrite);
    if (numBytesWritten < 0)
    {
        fprintf(stderr, "Serial port write() failed. Error: %s", strerror(errno));
    }
    
    return numBytesWritten;
#endif
}

//Returns -1 on failure, with errno set appropriately
ssize_t readSerialData(char* const rxBuffer, size_t numBytesToReceive)
{  
#ifdef WIN32
    DWORD bytesRead{};
    unsigned int toRead = 0;
    COMSTAT status;
    DWORD errors;

    ClearCommError(handler, &errors, &status);

    if (status.cbInQue > 0)
    {
        if (status.cbInQue > numBytesToReceive)
        {
            toRead = numBytesToReceive;
        }
        else
        {
            toRead = status.cbInQue;
        }
    }

    memset((void*) rxBuffer, 0, numBytesToReceive);

    if (ReadFile(handler, (void*) rxBuffer, toRead, &bytesRead, NULL))
    {
        return bytesRead;
    }

    return 0;
#else
    ssize_t numBytesRead = read(sfd, rxBuffer, numBytesToReceive);
    if (numBytesRead < 0) {
        fprintf(stderr, "Serial port read() failed. Error:%s", strerror(errno));
    }
    
    return numBytesRead;
#endif
}

ssize_t closeSerialPort(void)
{
    ssize_t result = 0;
    if (serialPortIsOpen())
    {
#ifdef WIN32
        CloseHandle(handler);
        handler = nullptr;
#else
        result = close(sfd);
        sfd = SFD_UNAVAILABLE;
#endif
    }
    return result;
}

ssize_t enumSerialPort(std::vector<std::string>& ports)
{
    ports.clear();
#ifdef WIN32
    HKEY hKey;
#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
    TCHAR       achValue[MAX_VALUE_NAME];                   // buffer for subkey name
    DWORD       cchValue = MAX_VALUE_NAME;                  // size of name string
    TCHAR       achClass[MAX_PATH] = "";                // buffer for class name
    DWORD       cchClassName = MAX_PATH;                    // size of class string
    DWORD       cSubKeys = 0;                               // number of subkeys
    DWORD       cbMaxSubKey;                                // longest subkey size
    DWORD       cchMaxClass;                                // longest class string
    DWORD       cKeyNum;                                    // number of values for key
    DWORD       cchMaxValue;                                // longest value name
    DWORD       cbMaxValueData;                             // longest value data
    DWORD       cbSecurityDescriptor;                       // size of security descriptor
    FILETIME    ftLastWriteTime;                            // last write time

    int iRet = -1;
    bool bRet = false;

    std::string strPortName;
    //SerialPortInfo m_serialPortInfo;

    TCHAR strDSName[MAX_VALUE_NAME];
    memset(strDSName, 0, MAX_VALUE_NAME);
    DWORD nValueType = 0;
    DWORD nBuffLen = 10;
    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey))
    {
        // Get the class name and the value count.
        iRet = RegQueryInfoKey(
            hKey,                    // key handle
            achClass,                // buffer for class name
            &cchClassName,           // size of class string
            NULL,                    // reserved
            &cSubKeys,               // number of subkeys
            &cbMaxSubKey,            // longest subkey size
            &cchMaxClass,            // longest class string
            &cKeyNum,                // number of values for this key
            &cchMaxValue,            // longest value name
            &cbMaxValueData,         // longest value data
            &cbSecurityDescriptor,   // security descriptor
            &ftLastWriteTime);       // last write time

        // Enumerate the key values.
        if (cKeyNum > 0 && ERROR_SUCCESS == iRet)
        {
            for (int i = 0; i < (int)cKeyNum; i++)
            {
                cchValue = MAX_VALUE_NAME;
                achValue[0] = '\0';
                nBuffLen = MAX_KEY_LENGTH;//防止 ERROR_MORE_DATA 234L 错误

                if (ERROR_SUCCESS == RegEnumValue(hKey, i, achValue, &cchValue, NULL, NULL, (LPBYTE)strDSName, &nBuffLen))
                {

#ifdef UNICODE
                    strPortName = wstringToString(strDSName);
#else
                    strPortName = std::string(strDSName);
#endif
                    ports.push_back(strPortName);
                }
            }
        }
        else
        {

        }
    }
    RegCloseKey(hKey);

#else
    std::vector<std::string> _dev, _name, _suffix;
    if (DIR_Iterate("/dev", _dev, _name, _suffix, "cu.", false, true) == 0)
    {
        ports = _dev;
    }
#endif
    return ports.size();
}
