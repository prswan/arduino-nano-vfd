//
// Copyright (c) 2025, Paul R. Swan
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#ifndef Types_h
#define Types_h

#include "Arduino.h"

//
// Base types
//

typedef signed char  CHAR;
typedef signed char  INT8;
typedef signed short INT16;
typedef signed long  INT32;

typedef unsigned char  UCHAR;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UINT32;


typedef       unsigned char *PSTR;
typedef const unsigned char *PCSTR;

//
// System wide definitions
//

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

//
// Representation of an error as a code plus description to print.
//
typedef struct _ERROR {

    UINT16 code;
    String description;

} ERROR, *PERROR;

#define ERROR_SUCCESS (0)

#define SUCCESS(e) (e->code == ERROR_SUCCESS)
#define FAILED(e)  (e->code != ERROR_SUCCESS)


//
// Macro to format a UINT8 hex value into a string with leading zeros.
// The Arduino String library does not appear to have an option to do this.
//

#define STRING_UINT8_HEX(string, value)                     \
    {                                                       \
        UINT8 value8 = (UINT8) value;                       \
                                                            \
        if (value8 <= 0xF)                                  \
        {                                                   \
            string += " 0" + String(value8, HEX);           \
        }                                                   \
        else                                                \
        {                                                   \
            string += " "  + String(value8, HEX);           \
        }                                                   \
    }                                                       \

//
// Macro to format a UINT16 hex value into a string with leading zeros.
// The Arduino String library does not appear to have an option to do this.
//

#define STRING_UINT16_HEX(string, value)                      \
    {                                                         \
        UINT16 value16 = (UINT16) value;                      \
                                                              \
        if (value16 <= 0xF)                                   \
        {                                                     \
            string += " 000" + String(value16, HEX);          \
        }                                                     \
        else if (value16 <= 0xFF)                             \
        {                                                     \
            string += " 00" + String(value16, HEX);           \
        }                                                     \
        else if (value16 <= 0xFFF)                            \
        {                                                     \
            string += " 0" + String(value16, HEX);            \
        }                                                     \
        else                                                  \
        {                                                     \
            string += " " + String(value16, HEX);             \
        }                                                     \
    }                                                         \

//
// Macro to format a UINT32 24-bit hex value into a string with leading zeros.
// The Arduino String library does not appear to have an option to do this.
//

#define STRING_UINT32_24_HEX(string, value)                  \
    {                                                        \
        if (value <= 0xF)                                    \
        {                                                    \
            string += " 00000" + String(value, HEX);         \
        }                                                    \
        else if (value <= 0xFF)                              \
        {                                                    \
            string += " 0000" + String(value, HEX);          \
        }                                                    \
        else if (value <= 0xFFF)                             \
        {                                                    \
            string += " 000" + String(value, HEX);           \
        }                                                    \
        else if (value <= 0xFFFF)                            \
        {                                                    \
            string += " 00" + String(value, HEX);            \
        }                                                    \
        else if (value <= 0xFFFFF)                           \
        {                                                    \
            string += " 0" + String(value, HEX);             \
        }                                                    \
        else                                                 \
        {                                                    \
            string += " " + String((value & 0xFFFFFF), HEX); \
        }                                                    \
    }                                                        \


//
// Macro to format a UINT32 hex value into a string with leading zeros.
// The Arduino String library does not appear to have an option to do this.
//

#define STRING_UINT32_HEX(string, value)               \
    {                                                  \
        if (value <= 0xF)                              \
        {                                              \
            string += " 0000000" + String(value, HEX); \
        }                                              \
        else if (value <= 0xFF)                        \
        {                                              \
            string += " 000000" + String(value, HEX);  \
        }                                              \
        else if (value <= 0xFFF)                       \
        {                                              \
            string += " 00000" + String(value, HEX);   \
        }                                              \
        else if (value <= 0xFFFF)                      \
        {                                              \
            string += " 0000" + String(value, HEX);    \
        }                                              \
        else if (value <= 0xFFFFF)                     \
        {                                              \
            string += " 000" + String(value, HEX);     \
        }                                              \
        else if (value <= 0xFFFFFF)                    \
        {                                              \
            string += " 00" + String(value, HEX);      \
        }                                              \
        else if (value <= 0xFFFFFFF)                   \
        {                                              \
            string += " 0" + String(value, HEX);       \
        }                                              \
        else                                           \
        {                                              \
            string += " " + String(value, HEX);        \
        }                                              \
    }                                                  \

//
// Macro to check a boolean value and exit with an error if it's wrong.
//
#define CHECK_BOOL_VALUE_EXIT(error, message, recValue, expValue)           \
    {                                                                       \
        if (recValue != expValue)                                           \
        {                                                                   \
            error = errorCustom;                                            \
            error->code = ERROR_FAILED;                                     \
            error->description = "E:";                                      \
            error->description += message;                                  \
            error->description += (expValue) ? " Hi" : " Lo";               \
            error->description += (recValue) ? " Hi" : " Lo";               \
            goto Exit;                                                      \
        }                                                                   \
    }                                                                       \

//
// Macro to check an 8-bit value and exit with an error if it's wrong.
//
#define CHECK_UINT8_VALUE_EXIT(error, message, recValue, expValue)          \
    {                                                                       \
        if (recValue != expValue)                                           \
        {                                                                   \
            error = errorCustom;                                            \
            error->code = ERROR_FAILED;                                     \
            error->description = "E:";                                      \
            error->description += message;                                  \
            STRING_UINT8_HEX(error->description, expValue);                 \
            STRING_UINT8_HEX(error->description, recValue);                 \
            goto Exit;                                                      \
        }                                                                   \
    }                                                                       \

//
// Macro to check a 16-bit value and exit with an error if it's wrong.
//
#define CHECK_UINT16_VALUE_EXIT(error, message, recValue, expValue)         \
    {                                                                       \
        if (recValue != expValue)                                           \
        {                                                                   \
            error = errorCustom;                                            \
            error->code = ERROR_FAILED;                                     \
            error->description = "E:";                                      \
            error->description += message;                                  \
            STRING_UINT16_HEX(error->description, expValue);                \
            STRING_UINT16_HEX(error->description, recValue);                \
            goto Exit;                                                      \
        }                                                                   \
    }                                                                       \

//
// Macro to check a boolean value and break with an error if it's wrong.
//
#define CHECK_BOOL_VALUE_BREAK(error, message, recValue, expValue)          \
    {                                                                       \
        if (recValue != expValue)                                           \
        {                                                                   \
            error = errorCustom;                                            \
            error->code = ERROR_FAILED;                                     \
            error->description = "E:";                                      \
            error->description += message;                                  \
            error->description += (expValue) ? " Hi" : " Lo";               \
            error->description += (recValue) ? " Hi" : " Lo";               \
            break;                                                          \
        }                                                                   \
    }                                                                       \

//
// Macro to check an 8-bit value and break with an error if it's wrong.
//
#define CHECK_UINT8_VALUE_BREAK(error, message, recValue, expValue)         \
    {                                                                       \
        if (recValue != expValue)                                           \
        {                                                                   \
            error = errorCustom;                                            \
            error->code = ERROR_FAILED;                                     \
            error->description = "E:";                                      \
            error->description += message;                                  \
            STRING_UINT8_HEX(error->description, expValue);                 \
            STRING_UINT8_HEX(error->description, recValue);                 \
            break;                                                          \
        }                                                                   \
    }                                                                       \

//
// Macro to check a 16-bit value and exit with an error if it's wrong.
//
#define CHECK_UINT16_VALUE_BREAK(error, message, recValue, expValue)        \
    {                                                                       \
        if (recValue != expValue)                                           \
        {                                                                   \
            error = errorCustom;                                            \
            error->code = ERROR_FAILED;                                     \
            error->description = "E:";                                      \
            error->description += message;                                  \
            STRING_UINT16_HEX(error->description, expValue);                \
            STRING_UINT16_HEX(error->description, recValue);                \
            break;                                                          \
        }                                                                   \
    }                                                                       \


#endif
