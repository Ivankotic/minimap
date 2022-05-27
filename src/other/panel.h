#pragma once

void panel(Adafruit_ST7735 &tft, int &window)
{
    window = window_enc;
    if (((millis() % 1) < 10))
    {
        //tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        //tft.fillRect(130, 0, 10, 15, ST77XX_YELLOW);
        drawtext(String(window) + " страница ", ST77XX_RED, 10, 5, tft); /*
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);*/
    }
    if ((millis() % 1500) < 5)
    {
        //window = !window;
    }
    if (panel_earsed) {
        tft.fillRect(0, 0, 160, 15, ST77XX_BLACK);
        tft.fillRect(130, 0, 10, 15, ST77XX_RED);
        tft.drawLine(0, 14, 160, 14, ST77XX_RED);
        panel_earsed = false;
    }
}