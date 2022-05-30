#pragma once

int popup_list_change_zoom(Adafruit_ST7735 &tft, systemSettings &sS)
{
  stop_window();
  can_change_window = false;
  int out;
  int zooms[10] = {1, 3, 4, 6, 8, 10, 13, 15, 16, 17};
  yvalue = get_index_by_value(zooms, sS.getZoom());
  enreadvalue = true;
  envalueinterval = 9;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("выбор масштаба", ST77XX_RED, 31, 31 - 8, tft);
  while (true)
  {
    vTaskDelay(100);
    tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED);
    int ite = 0;
    for (int i = 0; i < 10; i++)
    {
      String readedd = String(zooms[i]);
      if ((int)yvalue == i)
      {
        drawtext(">", ST77XX_RED, 31, 34 + ite * 8, tft);
        drawtext(readedd, ST77XX_RED, 31 + 10, 34 + ite * 8, tft);
        if (isPress1)
        {
          out = zooms[i];
          goto end;
        }
      }
      else
      {
        tft.fillRect(31, 34 + ite * 8, 10, 8, ST77XX_BLACK);
        drawtext(readedd, ST77XX_RED, 31 + 10, 34 + ite * 8, tft);
      }
      ite++;
    }
    tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED);
  }
end:
  stop_window();
  panel_earsed = false;
  return out;
}

int popup_loading(Adafruit_ST7735 &tft)
{
  stop_window();
  can_change_window = false;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("ЗАГРУЗКА", ST77XX_RED, 31, 31 - 8, tft);
  stop_window();
  panel_earsed = false;
  return (0);
}

int popup_list_map_options(Adafruit_ST7735 &tft)
{
  stop_window();
  can_change_window = false;
  int out;
  String modes[3] = {"выб. масштаб", "выбрать цель", "выйти"};
  yvalue = 0;
  enreadvalue = true;
  envalueinterval = 2;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("опции карты", ST77XX_RED, 31, 31 - 8, tft);
  while (true)
  {
    vTaskDelay(100);
    tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED);
    int ite = 0;
    for (int i = 0; i < 3; i++)
    {
      String readedd = modes[i];
      if ((int)yvalue == i)
      {
        drawtext(">", ST77XX_RED, 31, 34 + ite * 8, tft);
        drawtext(readedd, ST77XX_RED, 31 + 10, 34 + ite * 8, tft);
        if (isPress1)
        {
          out = yvalue;
          goto end;
        }
      }
      else
      {
        tft.fillRect(31, 34 + ite * 8, 10, 8, ST77XX_BLACK);
        drawtext(readedd, ST77XX_RED, 31 + 10, 34 + ite * 8, tft);
      }
      ite++;
    }
    tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED);
  }
end:
  stop_window();
  panel_earsed = false;
  return out;
}
