#ifndef MY_SERIAL_CONNECTION
    #define MY_SERIAL_CONNECTION
    #include <mbed.h>
    namespace sicet7{
        namespace Serial{
            mbed::Serial serialConnection(USBTX,USBRX);
        }
    }
#endif