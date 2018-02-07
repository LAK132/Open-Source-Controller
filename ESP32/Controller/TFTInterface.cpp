#include "TFTInterface.h"

TFTInterface::TFTInterface(TFT_22_ILI9225* tftref)
{
    tft = tftref;
}

//TFTInterface::TFTInterface(uint8_t rst, uint8_t rs, uint8_t cs, uint8_t led, uint8_t brightness)
//{
//    tft.begin();//tftspi);
//    tft.setFont(Terminal6x8);
//    digitalWrite(led, HIGH);
//    tft = TFT_22_ILI9225(rst, rs, cs, led, brightness);
//}
//
//TFTInterface::TFTInterface(uint8_t rst, uint8_t rs, uint8_t cs, uint8_t sdi, uint8_t clk, uint8_t led, uint8_t brightness = 128)
//{
//    tft.begin();//tftspi);
//    tft.setFont(Terminal6x8);
//    digitalWrite(led, HIGH);
//    tft = TFT_22_ILI9225(rst, rs, cs, sdi, clk, led, brightness);
//}

void TFTInterface::fill(uint16_t color)
{
    fillRect(0, 0, MAXX-1, MAXY-1, color);
}

void TFTInterface::fillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    for (uint16_t y = y1; y < y2 && y < MAXY; y++)
    {
        for (uint16_t x = x1; x < x2 && x < MAXX; x++)
        {
            tft->drawPixel(x, y, color);
        }
    }
}

bool TFTInterface::Page(String id)
{
    return true;
}

bool TFTInterface::HoriPanel()
{
    return true;
}

bool TFTInterface::VertPanel()
{
    return true;
}

bool TFTInterface::Display()
{
    return true;
}

bool TFTInterface::Button(String text)
{
    return true;
}
