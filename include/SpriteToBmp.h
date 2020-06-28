#ifndef __SPRITE_TO_BMP_H__
#define __SPRITE_TO_BMP_H__

#include <M5StickC.h>
#include <BmpBase64.h>

namespace SpriteToBmp
{
    namespace
    {
        Encoder _encoder = Encoder();
    }
    static void toBmpBase64(TFT_eSprite &sprite, std::function<void(uint8_t *, size_t)> cb)
    {
        _encoder.toBmpBase64((uint8_t *)sprite.frameBuffer(1), sprite.width(), sprite.height(), sprite.getColorDepth(), cb);
    }
}; // namespace SpriteToBmp

#endif