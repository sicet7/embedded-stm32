#ifndef MY_CONVERT_LIBRARY
    #define MY_CONVERT_LIBRARY
    #include <stdint.h>
    namespace sicet7{
        class Convert{

            public:
                
                //TODO: Only define when needed.

                static const char* ToCharArray16(const uint16_t unsignedInteger);
                static const char* ToCharArray32(const uint32_t unsignedInteger);
                static const char* ToCharArrayI32(const int32_t integer);

                static const char* ToCharArrayF(const float floatVar);

                //static char* ToChar(uint16_t unsignedInteger);
                //static const char* ToChar(const uint32_t unsignedInteger);
                //static char* ToChar(uint64_t unsignedInteger);

                //static char* ToChar(int16_t intVar);
                //static char* ToChar(int32_t intVar);
                //static char* ToChar(int64_t intVar);

                //static char* ToChar(float floatVar);
                //static char* ToChar(double doubleVar);

                //static const uint16_t Convert::ToUInt16(const uint8_t unsignedInteger);
                static uint16_t ToUInt16(const uint32_t unsignedInteger);
                //static const uint16_t Convert::ToUInt16(const uint64_t unsignedInteger);

        };
    }
#endif