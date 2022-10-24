#pragma once

void window_flash_light(Adafruit_ST7735 &tft, TinyGPSPlus &gps, SoftwareSerial &SoftSerial, systemSettings &sS)
{
    static String path = "/";
    if (window_flash_light_started == false)
    {
        Serial.println("open_window_flash_light");
        window_flash_light_started = true;
        tft.fillRect(0 , 0 + TOP_DISTANCE, 160, 128 - TOP_DISTANCE, ST77XX_WHITE);
        path = "/";
    }
    /*
    if ((millis() % 377) == 0)
    {
        tft.fillRect(0, 0 + TOP_DISTANCE, 160, 124, ST77XX_WHITE);
    }
    if ((millis() % 773) == 0)
    {
        tft.fillRect(0, 0 + TOP_DISTANCE, 160, 124, ST77XX_BLACK);
    }*/

    static int old_distance = 179;
    int distance = 0;
    enreadvalue = false;
    int count = 0;
    for (int i = 0; i < 30; i++)
    {
        String readedd = read_file_list(path, i);
        if (readedd == "")
            break;
        count++;
    }
    envalueinterval = count - 1;
    enreadvalue = true;

    distance = yvalue - 10;
    if (distance < 0)
        distance = 0;
    if (distance != old_distance)
        tft.fillRect(0 , 0 + TOP_DISTANCE, 160, 128 - TOP_DISTANCE, ST77XX_WHITE);
    old_distance = distance;

    int ite = 0;
    for (int i = distance; i < count; i++)
    {
        String readedd = read_file_list(path, i);
        if (readedd == "") break;
        if ((int)yvalue == i)
        {
            drawtext("-", ST77XX_BLACK, 0, 30 + ite * 8 - 3, tft);
            drawtext(readedd, ST77XX_BLACK, 0 + 10, 30 + ite * 8 - 3, tft);
            if (isPress1)
            {
                path = path + readedd;
                Serial.println(path);
                tft.fillRect(0 , 0 + TOP_DISTANCE, 160, 128 - TOP_DISTANCE, ST77XX_WHITE);
                isPress1 = false;
                yvalue = 0;
            }
        }
        else
        {
            tft.fillRect(0, 25 + ite * 8, 10, 8, ST77XX_WHITE);
            drawtext(readedd, ST77XX_BLACK, 0 + 10, 30 + ite * 8 - 3, tft);
        }
        ite++;
    }
}