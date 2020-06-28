#ifndef __TEST_BASE64_H_
#define __TEST_BASE64_H_

#include <string.h>

class Base64Class
{
public:
    int encode(char *output, char *input, int inputLength)
    {
        strcpy(output, "ABC123==");
        return strlen(output);
    }
};
Base64Class Base64;
#endif
