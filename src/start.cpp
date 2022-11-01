#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader.h> // Image-reading functions
#include <GyverButton.h>
#include "soc/rtc_wdt.h"

#define LEFT_DISTANCE 0
#define TOP_DISTANCE 15
#define S_RX 16 // Вывод RX
#define S_TX 17 // Вывод TX

// ESP32-WROOM
#define TFT_DC 2  // A0
#define TFT_CS 15 // CS
#define TFT_RST 4

#define SD_PIN 5

int povt1 = 0;
int povt2 = 0;

float yx[2] = {55.107500062790585, 61.35156885039418};
float yencode = yx[0];
float xencode = yx[1];
float move_map_coefficients[20] = {
    40,
    10,
    7,
    4,
    1,
    0.7,
    0.4,
    0.1,
    0.07,
    0.04,
    0.01,//10
    0.007,
    0.004,
    0.001,//13
    0.0007,
    0.0004,
    0.0001,
    0.00007,
    0.00004,
    0.00001};

int zooom = 15;

bool enreadxy = false;

float speed = 1;
float xvalue = 0;
float yvalue = 0;
bool enreadvalue = true;
bool can_change_window = true;
int envalueinterval = 1;

int window_enc = 0;

bool map_started = false;
bool window_flash_light_started = false;

bool panel_earsed = false;

bool isPress1 = false;
bool isPress2 = false;

//массивы для работы со списком сохранённых точек
String dot_list[10] = {"", "", "", "", "", ""};
String dot_list_x[10] = {"", "", "", "", "", ""};
String dot_list_y[10] = {"", "", "", "", "", ""};

#include "other/fakeSerial.h"
#include "other/functions.h"
#include "other/panel.h"
#include "other/readmeText.h"
#include "other/systemSettings.h"
#include "other/popups.h"
#include "windows/map.h"
#include "windows/flash_light.h"
#include "cores/core0.h"
#include "cores/core1.h"

void setup(void)
{
  setCpuFrequencyMhz(240);

  xTaskCreatePinnedToCore(
      Core0, "core0" // A name just for humans
      ,
      (1024 * 2 * 2 * 2 * 2 * 2 * 2) // This stack size can be checked & adjusted by reading the Stack Highwater
      ,
      NULL, 50 // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
      ,
      NULL, 0);

  xTaskCreatePinnedToCore(
      Core1, "core1", (1024 * 2 * 2 * 2 * 2 * 2) // Stack size
      ,
      NULL, 50 // Priority
      ,
      NULL, 1);

  rtc_wdt_protect_off();
  rtc_wdt_disable();
}

void loop()
{
  // nothing
}
