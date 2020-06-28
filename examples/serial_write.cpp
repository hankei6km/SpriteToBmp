#include <M5StickC.h>
#include <SpriteToBmp.h>

TFT_eSprite sp = TFT_eSprite(&M5.Lcd);

void writeRec(const char *s)
{
    Serial.printf("==== BMP:%s\n", s);
}

void writeBMP(TFT_eSprite &sp)
{
    SpriteToBmp::toBmpBase64(sp, [](uint8_t *b, size_t s) {
        if (b != NULL)
        {
            writeRec((const char *)b);
        }
        else
        {
            writeRec("---- cut ----");
        }
    });
}

void setup()
{
    M5.begin();

    Serial.begin(115200);

    setCpuFrequencyMhz(20);
    M5.Axp.ScreenBreath(8);

    M5.Lcd.setRotation(3);
    M5.Lcd.setTextFont(4);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextDatum(MC_DATUM);
    M5.Lcd.fillScreen(BLACK);

    sp.createSprite(160, 80);
    sp.setTextFont(4);
    sp.setTextColor(TFT_WHITE);
    sp.setTextDatum(MC_DATUM);

    // ---- image 1 ----
    sp.fillSprite(TFT_DARKGREY);
    sp.drawString("C  O  M", 80, 40);
    sp.pushSprite(0, 0);
    writeBMP(sp);

    // ---- image 2 ----
    sp.fillSprite(TFT_BLUE);
    sp.drawString("F  L  X", 80, 40);
    sp.pushSprite(0, 0);
    writeBMP(sp);

    // ---- image 3 ----
    sp.fillSprite(TFT_DARKCYAN);
    sp.drawString("P  I  O", 80, 40);
    sp.pushSprite(0, 0);
    writeBMP(sp);

    Serial.println("====== end ======");
    Serial.flush();
    delay(1000);

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.drawString("Ctrl - C", 80, 40);
}

void loop()
{
    delay(10000);
}