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

    if (SoftSerial.available() > 0)
    {
        if (gps.encode(SoftSerial.read()))
        {
            if (gps.location.isValid())
            {
                // showcords("/6.3_tiles", 0, 0);
                /*
                testdrawtext("time   =     " + String(gps.time.hour() + 5) + ":" + String(gps.time.minute()), ST77XX_BLACK, 5, 10, tft);
                testdrawtext("Y      =    " + String(gps.location.lat(), 5), ST77XX_BLACK, 5, 20, tft);
                testdrawtext("x      =    " + String(gps.location.lng(), 5), ST77XX_BLACK, 5, 30, tft);
                testdrawtext("Z      =     " + String(gps.altitude.meters()) + "m", ST77XX_BLACK, 5, 40, tft);
                testdrawtext("Speed  =     " + String(gps.speed.kmph()) + "kmh", ST77XX_BLACK, 5, 50, tft);
                */
                // delay(10000);
                yencode = gps.location.lat();
                xencode = gps.location.lng();
            }
        }
    }

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
        case 0: {//new zoom
            int new_zoom = popup_list_change_zoom(tft, sS);
            popup_loading(tft);
            sS.setZoom(new_zoom);
            break;
        }
        case 1: { //save dot
            break;
        }
        case 2: {//open dot
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
        case 5: {// exit
            //nothing
            break;
        }
        }
    }
}