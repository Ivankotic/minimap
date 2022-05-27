/*
 * Print size, modify date/time, and name for all files in root.
 */
#include <SPI.h>
#include "SdFat.h"
#include "Adafruit_SPIFlash.h"

// Uncomment to run example with custom SPI and SS e.g with FRAM breakout
// #define CUSTOM_CS   A5
// #define CUSTOM_SPI  SPI

#if defined(CUSTOM_CS) && defined(CUSTOM_SPI)
  Adafruit_FlashTransport_SPI flashTransport(CUSTOM_CS, CUSTOM_SPI);

#elif defined(ARDUINO_ARCH_ESP32)
  // ESP32 use same flash device that store code.
  // Therefore there is no need to specify the SPI and SS
  Adafruit_FlashTransport_ESP32 flashTransport;

#elif defined(ARDUINO_ARCH_RP2040)
  // RP2040 use same flash device that store code.
  // Therefore there is no need to specify the SPI and SS
  // Use default (no-args) constructor to be compatible with CircuitPython partition scheme
  Adafruit_FlashTransport_RP2040 flashTransport;

  // For generic usage: Adafruit_FlashTransport_RP2040(start_address, size)
  // If start_address and size are both 0, value that match filesystem setting in
  // 'Tools->Flash Size' menu selection will be used

#else
  // On-board external flash (QSPI or SPI) macros should already
  // defined in your board variant if supported
  // - EXTERNAL_FLASH_USE_QSPI
  // - EXTERNAL_FLASH_USE_CS/EXTERNAL_FLASH_USE_SPI
  #if defined(EXTERNAL_FLASH_USE_QSPI)
    Adafruit_FlashTransport_QSPI flashTransport;
  
  #elif defined(EXTERNAL_FLASH_USE_SPI)
    Adafruit_FlashTransport_SPI flashTransport(EXTERNAL_FLASH_USE_CS, EXTERNAL_FLASH_USE_SPI);
  
  #else
    #error No QSPI/SPI flash are defined on your board variant.h !
  #endif
#endif

Adafruit_SPIFlash flash(&flashTransport);

// file system object from SdFat
FatFileSystem fatfs;

FatFile root;
FatFile file;

//------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  // Init external flash
  flash.begin();

  // Init file system on the flash
  fatfs.begin(&flash);
  
  // Wait for USB Serial 
  while (!Serial) {
    SysCall::yield();
  }
  
  if (!root.open("/")) {
    Serial.println("open root failed");
  }
  // Open next file in root.
  // Warning, openNext starts at the current directory position
  // so a rewind of the directory may be required.
  while (file.openNext(&root, O_RDONLY)) {
    file.printFileSize(&Serial);
    Serial.write(' ');
    file.printModifyDateTime(&Serial);
    Serial.write(' ');
    file.printName(&Serial);
    if (file.isDir()) {
      // Indicate a directory.
      Serial.write('/');
    }
    Serial.println();
    file.close();
  }
  
  if (root.getError()) {
    Serial.println("openNext failed");
  } else {
    Serial.println("Done!");
  }
}
//------------------------------------------------------------------------------
void loop() {}