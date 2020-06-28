#include <string>
#include <functional>

#include <BmpHeader.h>
#include <BmpBase64.h>

void SpriteToBmp::Encoder::toBmpBase64(uint8_t *src, int16_t w, int16_t h, int8_t depth, std::function<void(uint8_t *, size_t)> cb)
{
    uint32_t i;

    // depth = 16 で決め打ち.
    SpriteToBmp::BmpHeader bh = BmpHeader(w, h);
    int headerSize = bh.headerSize();
    unsigned char *header = bh.header();
    for (i = 0; i + _splitSize < headerSize; i = i + _splitSize)
    {
        _encodeBase64((uint8_t *)&header[i], _splitSize, cb);
    }
    _encodeBase64((uint8_t *)&header[i], (headerSize - i), cb);

    uint32_t bufSize = w * h * 2;
    uint8_t buf[_splitSize]; // スタックで確保しても大丈夫?
    for (i = 0; i + _splitSize < bufSize; i = i + _splitSize)
    {
        _swapBytes(&src[i], buf, _splitSize);
        _encodeBase64(buf, _splitSize, cb);
    }
    _swapBytes(&src[i], buf, (bufSize - i));
    _encodeBase64(buf, (bufSize - i), cb);

    cb(NULL, 0);
}