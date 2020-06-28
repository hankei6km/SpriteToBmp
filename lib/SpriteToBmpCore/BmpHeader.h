#ifndef __BMP_HEADER_H__
#define __BMP_HEADER_H__

// #include <cstdint.h>
#include <stdint.h>
#include <string.h>

namespace SpriteToBmp
{
    class BmpHeader
    {
        static const uint32_t _fileHeaderSize = 14;
        // static const uint32_t _infoHeaderSize = 56; // v3?: PC bitmap, Adobe Photoshop with alpha channel mask.
        // (incompatible with some tools)
        static const uint32_t _infoHeaderSize = 108; // v4: PC bitmap, Windows 95/NT4 and newer format.
        static const uint32_t _headerSize = _fileHeaderSize + _infoHeaderSize;
        uint8_t _header[_headerSize];
        int16_t _w = 0;
        int16_t _h = 0;
        int8_t _depth = 0;
        uint32_t _fileSize = 0;

    public:
        BmpHeader(int16_t w, int16_t h)
        {
            _w = w;
            _h = h;
            _depth = 16;

            _fileSize = _headerSize + (_depth / 8) * _w * _h;

            // https://gist.github.com/rogerclarkmelbourne/8b15184a30d256bccc46080f01163553
            // https://www.wdic.org/w/TECH/BMP

            memset(_header, 0, _headerSize);
            _header[0] = 'B';
            _header[1] = 'M';
            _header[2] = (uint8_t)(_fileSize);
            _header[3] = (uint8_t)(_fileSize >> 8);
            _header[4] = (uint8_t)(_fileSize >> 16);
            _header[5] = (uint8_t)(_fileSize >> 24);
            _header[10] = (uint8_t)_headerSize;

            _header[14] = _infoHeaderSize;
            _header[18] = (uint8_t)(_w);
            _header[19] = (uint8_t)(_w >> 8);
            _header[20] = (uint8_t)(_w >> 16);
            _header[21] = (uint8_t)(_w >> 24);
            int16_t ih = _h * (-1); // top-down.
            _header[22] = (uint8_t)(ih);
            _header[23] = (uint8_t)(ih >> 8);
            _header[24] = (uint8_t)(ih >> 16);
            _header[25] = (uint8_t)(ih >> 24);
            _header[26] = 1;
            _header[28] = _depth;
            // BI_BITFIELDS, it to effect color masks
            // (TFT_eSprite 16bit buffer: the color format is RGB565).
            _header[30] = 3;

            _header[54] = 0;
            _header[55] = 0xF8;
            _header[56] = 0;
            _header[57] = 0;

            _header[58] = 0xe0;
            _header[59] = 0x7;
            _header[60] = 0;
            _header[61] = 0;

            _header[62] = 0x1f;
            _header[63] = 0;
            _header[64] = 0;
            _header[65] = 0;
        };
        uint8_t *fileHeader();
        uint32_t fileHeaderSize();
        uint8_t *infoHeader();
        uint32_t infoHeaderSize();
        uint8_t *header();
        uint32_t headerSize();
    };
}; // namespace SpriteToBmp

#endif