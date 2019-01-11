#include <classes/sicet7/Convert.h>
#include <cstring>
#include <stdio.h>
#include <stdint.h>
namespace sicet7{

    const char* Convert::ToCharArray16(const uint16_t unsignedInteger){
        char* buffer;
        sprintf(buffer,"%u",unsignedInteger);
        char* returnValue = new char[(sizeof(buffer))];
        std::memcpy(returnValue,buffer,(sizeof(buffer)));
        return returnValue;
    }

    const char* Convert::ToCharArray32(const uint32_t unsignedInteger){
        char* buffer;
        sprintf(buffer,"%u",unsignedInteger);
        char* returnValue = new char[(sizeof(buffer))];
        std::memcpy(returnValue,buffer,(sizeof(buffer)));
        return returnValue;
    }

    const char* Convert::ToCharArrayI32(const int32_t integer){
        char* buffer;
        sprintf(buffer,"%d",integer);
        char* returnValue = new char[(sizeof(buffer))];
        std::memcpy(returnValue,buffer,(sizeof(buffer)));
        return returnValue;
    }

    const char* Convert::ToCharArrayF(const float floatVar){
        char* buffer;
        sprintf(buffer,"%Lf",floatVar);
        
        char* returnValue = new char[(sizeof(buffer))];
        std::memcpy(returnValue,buffer,(sizeof(buffer)));
        return returnValue;
    }

    uint16_t Convert::ToUInt16(const uint32_t unsignedInteger){
        uint16_t uint16_max = ((uint16_t)UINT16_MAX);
        uint32_t uint16_max_as32 = ((uint32_t)uint16_max);
        if(unsignedInteger >= uint16_max_as32){
            return uint16_max;
        }

        return ((uint16_t)unsignedInteger);

    }
    
}