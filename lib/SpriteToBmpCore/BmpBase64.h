#ifndef __BMP_BASE64_H__
#define __BMP_BASE64_H__

#include <functional>

#include <Base64.h>

namespace SpriteToBmp
{
    class Encoder
    {
    private:
        static const uint32_t _splitSize = 300;        // 300 に特に意味はない
        static const uint32_t _encodedSplitSize = 401; // 300 に対する最大値(NULL終端)
        static inline void _swapBytes(uint8_t *src, uint8_t *dst, uint32_t size)
        {
            for (int32_t j = 0; j < size; j = j + 2)
            {
                dst[j] = src[j + 1];
                dst[j + 1] = src[j];
            }
        };
        static inline void _encodeBase64(uint8_t *src, uint32_t size, std::function<void(uint8_t *, size_t)> cb)
        {
            char encoded[_encodedSplitSize]; // スタックで確保しても大丈夫?
            size_t len = Base64.encode((char *)encoded, (char *)src, size);
            encoded[len] = 0;
            cb((uint8_t *)encoded, len);
        };

    public:
        static void toBmpBase64(uint8_t *src, int16_t w, int16_t h, int8_t depth, std::function<void(uint8_t *, size_t)> cb);
    };
}; // namespace SpriteToBmp

#endif
