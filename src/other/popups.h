#pragma once

//шаблон
/*
int my_popup(Adafruit_ST7735 &tft, systemSettings &sS)
{
  stop_window();
  can_change_window = false;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("КАААААРП", ST77XX_RED, 31, 31 - 8, tft);
  stop_window();
  panel_earsed = false;
  return (0);
}
*/

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
  String modes[8] = {"выб. масштаб", "сохр. точку", "откр. точку", "выб. цель", "тёмный режим", "изм. скорость", "удалить точку", "выйти"};
  yvalue = 0;
  enreadvalue = true;
  envalueinterval = 7;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("опции карты", ST77XX_RED, 31, 31 - 8, tft);
  tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED);
  while (true)
  {
    vTaskDelay(10);
    int ite = 0;
    for (int i = 0; i < 8; i++)
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

int popup_map_save_dot(Adafruit_ST7735 &tft, systemSettings &sS, float xa, float ya)
{
  stop_window();
  can_change_window = false;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("ЗАПИСЬ", ST77XX_RED, 31, 31 - 8, tft);
  sS.saveDot(xa, ya, String(random(10000,99999)));
  drawtext("ГОТОВО", ST77XX_RED, 31, 31 - 8, tft);
  vTaskDelay(1000);
  stop_window();
  panel_earsed = false;
  return (0);
}

int popup_map_delete_dot(Adafruit_ST7735 &tft, systemSettings &sS)
{
  stop_window();
  can_change_window = false;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("УДАЛЕНИЕ", ST77XX_RED, 31, 31 - 8, tft);
  drawtext("ПОСЛЕДНЕЙ", ST77XX_RED, 31, 31 - 8 + 8, tft);
  drawtext("ТОЧКИ", ST77XX_RED, 31, 31 - 8 + 8 + 8, tft);
  //sS.saveDot(xa, ya, String(random(10000,99999)));
  vTaskDelay(1000);
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  drawtext("ГОТОВО", ST77XX_RED, 31, 31 - 8, tft);
  vTaskDelay(1000);
  stop_window();
  panel_earsed = false;
  return (0);
}

int popup_map_open_dot(Adafruit_ST7735 &tft, systemSettings &sS, float &o_x, float &o_y)
{
  stop_window(); //обнуляем флаги
  can_change_window = false; //запрещаем переключать страницу
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK); //рисуем чёрный прямоугольник (основа для окна)
  tft.drawRect(29, 19, 91, 96, ST77XX_RED); //рисуем рамку окна
  drawtext("выбор точки", ST77XX_RED, 31, 31 - 8, tft); // пишем название окна
  tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED); // рисуем линию под названием

  //String dot_list[6];
  sS.getDotList(); // загружаем в память (в специальные глобальные переменные) из SD данные (список точек и их парамметры)
  yvalue = 0; // обнуляем положение курсора
  enreadvalue = true; // сообщаем второму ядру, что нужно работать с циклическим списком
  envalueinterval = 9; // задаем длинну циклического списка для второго ядра (отсчет там идёт от 0, поэтому n-1)
  int out_num = 0; //объявляем переменную для выбора точки из спика 

  while (true) // вечный цикл
  {
    vTaskDelay(10); // задержка для стабильности

    for (int i = 0; i < 10; i++) //цикл отрисовки списка (i < длинна списка)
    {
      //String readedd = modes[i];
      if ((int)yvalue == i) //если курсор (двигаемый вторым ядром) указывает на отрисовываемый сейчас пунк списка
      {
        drawtext(">", ST77XX_RED, 31, 34 + i * 8, tft); // рисуем курсор
        drawtext(dot_list[i], ST77XX_RED, 31 + 10, 34 + i * 8, tft); // пишем название пункта списка
        if (isPress1) // если есть нажатие кнопки "выбрать"
        {
          out_num = yvalue;
          goto end; //уходим из цикла
        }
      }
      else // иначе
      {
        tft.fillRect(31, 34 + i * 8, 10, 8, ST77XX_BLACK); // закрашеваем место где может быть курсор
        drawtext(dot_list[i], ST77XX_RED, 31 + 10, 34 + i * 8, tft); //пишем название пункта списка
      }
    }
  }
end:

  //vTaskDelay(1000);
  o_x = dot_list_x[out_num].toFloat();
  o_y = dot_list_y[out_num].toFloat();
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  drawtext("ГОТОВО", ST77XX_RED, 31, 31 - 8, tft);
  vTaskDelay(1000);
  stop_window();
  panel_earsed = false;
  return (0);
}

int popup_map_set_speed(Adafruit_ST7735 &tft, int old_result)
{
  stop_window();
  can_change_window = false;
  int out;
  String modes[4] = {"медленно", "средне", "быстро", "выйти"};
  yvalue = old_result;
  enreadvalue = true;
  envalueinterval = 3;
  tft.fillRect(30, 20, 90, 95, ST77XX_BLACK);
  tft.drawRect(29, 19, 91, 96, ST77XX_RED);
  drawtext("скорость карты", ST77XX_RED, 31, 31 - 8, tft);
  tft.drawLine(29, 31, 29 + 90, 31, ST77XX_RED);
  while (true)
  {
    vTaskDelay(10);
    int ite = 0;
    for (int i = 0; i < 4; i++)
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
