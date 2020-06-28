#include "BmpHeader.h"

unsigned char *SpriteToBmp::BmpHeader::fileHeader()
{
    return _header;
}

uint32_t SpriteToBmp::BmpHeader::fileHeaderSize()
{
    return _fileHeaderSize;
}

unsigned char *SpriteToBmp::BmpHeader::infoHeader()
{
    return &_header[14];
}

uint32_t SpriteToBmp::BmpHeader::infoHeaderSize()
{
    return _infoHeaderSize;
}

unsigned char *SpriteToBmp::BmpHeader::header()
{
    return _header;
}

uint32_t SpriteToBmp::BmpHeader::headerSize()
{
    return _headerSize;
}
