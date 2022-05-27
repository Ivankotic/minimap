#pragma once

// functions

String utf8rus(String source)
{
  int i, k;
  String target;
  unsigned char n;
  char m[2] = {'0', '\0'};

  k = source.length();
  i = 0;

  while (i < k)
  {
    n = source[i];
    i++;

    if (n >= 0xC0)
    {
      switch (n)
      {
      case 0xD0:
      {
        n = source[i];
        i++;
        if (n == 0x81)
        {
          n = 0xA8;
          break;
        }
        if (n >= 0x90 && n <= 0xBF)
          n = n + 0x30;
        break;
      }
      case 0xD1:
      {
        n = source[i];
        i++;
        if (n == 0x91)
        {
          n = 0xB8;
          break;
        }
        if (n >= 0x80 && n <= 0x8F)
          n = n + 0x70;
        break;
      }
      }
    }
    m[0] = n;
    target = target + String(m);
  }
  return (target);
}

String read_from_card(String path_to_file)
{
  SdFat sd;
  if (!sd.begin(SD_PIN, SD_SCK_MHZ(20)))
  {
    return ("err");
  }
  // sd.remove("/testomb.txt");
  File myFile;
  myFile = sd.open(path_to_file, FILE_READ);
  String readeddata = "";
  while (myFile.available())
  {
    readeddata += (char)myFile.read();
  }
  myFile.close();
  return (readeddata);
}

String read_file_list(String path_to_dir, int prohod)
{
  SdFat sd;
  SdFile root;
  SdFile file;
  fakeSerial ls_fakeSerial(0);
  int this_prohod = 0;

  if (!sd.begin(SD_PIN, SD_SCK_MHZ(25)))
  {
    return ("");
  }

  char *buf = new char[50];
  path_to_dir.toCharArray(buf, 50);
  const char *str2 = (const char *)buf;
  if (!root.open(str2))
  {
    return ("");
  }
  delete buf;
  while (file.openNext(&root, O_RDONLY))
  {
    if (prohod == this_prohod)
    {
      // file.printFileSize(&ls_fakeSerial);
      //  ls_fakeSerial.write(" ");
      //  file.printModifyDateTime(&ls_fakeSerial);
      // ls_fakeSerial.write("  ");
      file.printName(&ls_fakeSerial);
      if (file.isDir())
      {
        // Indicate a directory.
        ls_fakeSerial.write("/");
      }
    }
    file.close();
    this_prohod++;
  }

  return (ls_fakeSerial.get_value());
}

String write_to_card(String path, String to_write)
{
  SdFat sd;
  if (!sd.begin(SD_PIN, SD_SCK_MHZ(20)))
  {
    return ("err");
  }
  char *buf = new char[100];
  path.toCharArray(buf, 100);
  const char *str2 = (const char *)buf;
  sd.remove(str2);
  File myFile;
  myFile = sd.open(str2, FILE_WRITE);
  myFile.print(to_write);
  myFile.close();
  Serial.print("s ");
  Serial.print(to_write);
  Serial.print(" ");
  Serial.print(path);
  Serial.print(" ");
  Serial.println(str2);
  delete buf;
  return ("ok");
}

String make_dir(String path)
{
  SdFat sd;
  if (!sd.begin(SD_PIN, SD_SCK_MHZ(20)))
  {
    return ("err");
  }
  char *buf = new char[100];
  path.toCharArray(buf, 100);
  const char *str2 = (const char *)buf;
  sd.mkdir(str2);
  return ("ok");
}

void drawtile(String fold, int xx, int yy, int start_x, int start_y, Adafruit_ST7735 &tft)
{
  fold += "/";
  fold += xx;
  fold += "/";
  fold += yy;
  fold += ".bmp";
  char fold_out[50];
  fold.toCharArray(fold_out, 50);
  SdFat SD;
  Adafruit_ImageReader reader(SD);
  SD.begin(SD_PIN, SD_SCK_MHZ(25));
  reader.drawBMP(fold_out, tft, start_x, start_y, true);
}

float cordsconvert1(float lon_deg, int zoom)
{
  float n = pow(2, zoom);
  float xtile = ((lon_deg + 180.0) / 360.0 * n);
  return (xtile - (3 * (1 / float(10))));
}

float cordsconvert2(float lat_deg, int zoom)
{
  float lat_rad = lat_deg * 0.0174533;
  float n = pow(2, zoom);
  float ytile = ((1.0 - asinh(tan(lat_rad)) / 3.14159265) / 2.0 * n);
  return (ytile - (2.5 * (1 / float(10))));
}

void drawcros(Adafruit_ST7735 &tft)
{
  tft.drawLine((tft.width() / 2) + LEFT_DISTANCE - 5, (tft.height() / 2) + TOP_DISTANCE - 5, (tft.width() / 2) + LEFT_DISTANCE + 5, (tft.height() / 2) + TOP_DISTANCE + 5, ST77XX_RED);
  tft.drawLine((tft.width() / 2) + LEFT_DISTANCE - 5, (tft.height() / 2) + TOP_DISTANCE + 5, (tft.width() / 2) + LEFT_DISTANCE + 5, (tft.height() / 2) + TOP_DISTANCE - 5, ST77XX_RED);
}

void showcords(float y, float x, int zoom, Adafruit_ST7735 &tft)
{
  float x_converted = cordsconvert1(x, zoom);
  float y_converted = cordsconvert2(y, zoom);
  String fold = "/" + String(zoom) + ".3_tiles";
  Serial.println("pt");
  // float x3 = x33;
  // float y3 = y33;
 // Serial.println(String(x_converted) + " " + String(y_converted) + " " + String(x) + " " + String(y));
  tft.fillScreen(ST77XX_WHITE);
  int int_x_converted = (int)x_converted;
  int int_y_converted = (int)y_converted;
  int start_x = (int)(-((x_converted - int_x_converted) * 256) + LEFT_DISTANCE);
  int start_y = (int)(-((y_converted - int_y_converted) * 256) + TOP_DISTANCE);
  drawcros(tft);
  drawtile(fold, int_x_converted, int_y_converted, start_x, start_y, tft);
  drawcros(tft);
  drawtile(fold, int_x_converted + 1, int_y_converted, start_x + 256, start_y, tft);
  drawcros(tft);
  drawtile(fold, int_x_converted, int_y_converted + 1, start_x, start_y + 256, tft);
  drawcros(tft);
  drawtile(fold, int_x_converted + 1, int_y_converted + 1, start_x + 256, start_y + 256, tft);
  drawcros(tft);
}

void drawtext(String text, uint16_t color, int a, int b, Adafruit_ST7735 &tft)
{
  tft.setTextWrap(false);
  tft.setCursor(a, b);
  tft.setTextColor(color, ST7735_BLACK);
  tft.print(utf8rus(text));
}

void stop_window()
{
  map_started = false;
  window_flash_light_started = false;

  enreadvalue = false;
  enreadxy = false;
  envalueinterval = 1;
  panel_earsed = true;
  yvalue = 0;
  xvalue = 0;
  isPress1 = false;
  isPress2 = false;
  can_change_window = true;
}


//-functions