#pragma once

void window_map(Adafruit_ST7735 &tft, TinyGPSPlus &gps, SoftwareSerial &SoftSerial, systemSettings &sS)
{
    static float checksum = 0;
    static bool doInvert = false;
    // delay(5000);
    enreadxy = true;

    if (map_started == false)
    {
        Serial.println("open_window_map");
        checksum = 0;
        map_started = true;
    }

/*
    if (SoftSerial.available() > 0)
    {
        //Serial.write(SoftSerial.read());
        if (gps.encode(SoftSerial.read()))
        {
            
                // showcords("/6.3_tiles", 0, 0);
                
                drawtext("time   =     " + String(gps.time.hour() + 5) + ":" + String(gps.time.minute()), ST77XX_BLACK, 5, 10+10, tft);
                drawtext("Y      =    " + String(gps.location.lat(), 5), ST77XX_BLACK, 5, 20+10, tft);
                drawtext("x      =    " + String(gps.location.lng(), 5), ST77XX_BLACK, 5, 30+10, tft);
                drawtext("Z      =     " + String(gps.altitude.meters()) + "m", ST77XX_BLACK, 5, 40+10, tft);
               drawtext("Speed  =     " + String(gps.speed.kmph()) + "kmh", ST77XX_BLACK, 5, 50+10, tft);
                
                // delay(10000);
                yencode = gps.location.lat();
                xencode = gps.location.lng();
            
        }
    }
*/
    if (checksum != (xencode + yencode + xvalue + yvalue))
    {
        vTaskDelay(300);
        checksum = xencode + yencode + xvalue + yvalue;

        zooom = sS.getZoom();
        showcords(yencode, xencode, zooom, tft);

        double courseTol =
            TinyGPSPlus::courseTo(
                yencode, xencode,
                55.14643114923195, 61.382051867788256) *
            3.141592653589793238462643383279 / 180;

        unsigned long distanceTol =
            (unsigned long)TinyGPSPlus::distanceBetween(
                yencode, xencode,
                55.14643114923195, 61.382051867788256);

        long endx = ((tft.width() / 2) + LEFT_DISTANCE) + (sin(courseTol) * 300);
        long endy = ((tft.height() / 2) + TOP_DISTANCE) + (-cos(courseTol) * 300);

        tft.drawLine((tft.width() / 2) + LEFT_DISTANCE, (tft.height() / 2) + TOP_DISTANCE, endx, endy, ST77XX_RED);

        tft.fillRect(7, 110, 131, 15, ST77XX_WHITE);
        tft.drawRect(6, 109, 132, 16, ST77XX_BLACK);
        drawtext(String(distanceTol) + " метров до цели", ST77XX_BLACK, 10, 115, tft);

        panel_earsed = true;

        Serial.print(String(distanceTol) + " ");
        Serial.print(String(cos(courseTol)) + " ");
        Serial.println(sin(courseTol));

        // write_to_card("mydir/testomb.txt", read_from_card("mydir/testomb.txt") + "sf");
        // drawtext(read_from_card("mydir/testomb.txt"), ST77XX_GREEN, 0, 30, tft);
    }

    if (isPress1)
    {
        
        switch (popup_list_map_options(tft))
        {
        case 0: {// new zoom
            int new_zoom = popup_list_change_zoom(tft, sS);
            popup_loading(tft);
            sS.setZoom(new_zoom);
            break;
        }
        case 1: {// save dot
            popup_map_save_dot(tft, sS, xencode, yencode);
            break;
        }
        case 2: {// open dot
            popup_map_open_dot(tft, sS, xencode, yencode);
            break;
        }
        case 3: {// select target
            break;
        }
        case 4: {// dark mode
            doInvert = !doInvert;
            tft.invertDisplay(doInvert);
            break;
        }
        case 5: {// set speed
            static int old_res = 1;
            switch (popup_map_set_speed(tft, old_res)) {
                case 0: {
                    old_res = 0;
                    speed = 0.1;
                    break;
                }
                case 1: {
                    old_res = 1;
                    speed = 1;
                    break;
                }
                case 2: {
                    old_res = 2;
                    speed = 2.5;
                    break;
                }
                case 3: {// exit
                    break;
                }
            }
            break;
        }
        case 6: {// delete dot
            popup_map_delete_dot(tft, sS);
            break;
        }
        case 7: {// exit
            //nothing
            break;
        }
        }
    }
}