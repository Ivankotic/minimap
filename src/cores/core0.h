#pragma once

void Core0(void *pvParameters)
{
    (void)pvParameters;

    Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    // Use this initializer if using a 1.8" TFT screen:
    tft.setSPISpeed(80*1000000); // set speed
    tft.initR(INITR_BLACKTAB);
    tft.cp437(true);
    tft.setRotation(3);
    tft.fillScreen(ST77XX_BLACK);
    drawtext("загрузка и запуск", ST77XX_RED, tft.width() / 2 - 60, tft.height() / 2, tft);
    /*
    Adafruit_Image *img = new Adafruit_Image();
    SdFat SD;   
  Adafruit_ImageReader reader(SD);
  SD.begin(SD_PIN, SD_SCK_MHZ(25));
    reader.loadBMP("10.3_tiles/600/300.bmp", *img);
    img->draw(tft, 0, 0);
    delete img;
    vTaskDelay(1000*3);*/
    // reader.drawBMP("/parrot.bmp", tft, Y, X);
    TinyGPSPlus gps;
    SoftwareSerial SoftSerial(S_RX, S_TX);
    int window;
    int old_window;
    // init
    pinMode(27, INPUT);
    pinMode(26, INPUT);
    pinMode(25, INPUT);
    pinMode(33, INPUT);
    pinMode(32, INPUT);
    pinMode(35, INPUT);
    Serial.begin(9600);
    SoftSerial.begin(9600);

    window = 0;
    old_window = 100;
    // tft.invertDisplay(true);
    systemSettings sS = systemSettings();
    //-init
    // loop
    for (;;)
    {
        if (old_window != window)
        {
            stop_window();
            tft.invertDisplay(false);
        }
        old_window = window;

        if (window == 0)
        {
            window_map(tft, gps, SoftSerial, sS);
        }
        else if (window == 1)
        {
            window_flash_light(tft, gps, SoftSerial, sS);
        }
        else if (window == 2)
        {
        }
        else if (window == 3)
        {
        }
        panel(tft, window);

        vTaskDelay(1);
    }
    //-loop
    vTaskDelete(NULL);
}