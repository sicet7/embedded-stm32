#pragma once
#include <mbed.h>

namespace sicet7{

    namespace Serial{

        class Console{
            public:
                static mbed::Serial* serial;
                static void Output(const char* customString);
                static void Output(const char* customString, bool newline);
                static void Output(const char* customString, bool newline, bool threadPrefix);
        };

    }

}

