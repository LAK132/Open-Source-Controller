#include "SPI.h"
#include <TFT_22_ILI9225.h>

#ifndef MAXX
#   define MAXX 220
#endif
#ifndef MAXY
#   define MAXY 176
#endif

class TFTInterface
{
private:
    TFT_22_ILI9225* tft;
public:
    TFTInterface(TFT_22_ILI9225* tftref);
//    TFTInterface(uint16_t width, uint16_t height, uint8_t rst, uint8_t rs, uint8_t cs, uint8_t led, uint8_t brightness = 128);
//    TFTInterface(uint16_t width, uint16_t height, uint8_t rst, uint8_t rs, uint8_t cs, uint8_t sdi, uint8_t clk, uint8_t led, uint8_t brightness = 128);
    bool getUpd(size_t index);
    void setUpd(size_t index, bool val);
    void fill(uint16_t color);
    void fillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
    bool Page(String id);
    bool HoriPanel();
    bool VertPanel();
    bool Display();
    bool Button(String text);
};
