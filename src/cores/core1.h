#pragma once

void Core1(void *pvParameters)
{
    (void)pvParameters;

    GButton button1(26);
    GButton button2(25);
    GButton button3(33);
    button1.setDebounce(20);
    button2.setDebounce(20);
    button3.setDebounce(20);
    // init
    digitalWrite(27, LOW);
    digitalWrite(26, LOW);
    digitalWrite(25, LOW);
    digitalWrite(33, LOW);
    digitalWrite(32, LOW);
    digitalWrite(35, LOW);

    pinMode(27, INPUT);
    pinMode(26, INPUT);
    pinMode(25, INPUT);
    pinMode(33, INPUT);
    pinMode(32, INPUT);
    pinMode(35, INPUT);
    //-init
    for (;;)
    {
        button1.tick();
        button2.tick();
        button3.tick();

        if (button2.isTriple()) {
        Serial.println("triple");
        }
        if (button2.isDouble()) {
        Serial.println("double");
        }
        if (button2.isSingle()) {
        Serial.println("single");
        }

        

        if (enreadxy)
        {
            // norm
            if (button2.isSingle())
            {
                xencode = xencode + move_map_coefficients[zooom];
            }
            if (button2.isDouble())
            {
                xencode = xencode - move_map_coefficients[zooom];
            }
            if (button3.isSingle())
            {
                yencode = yencode - move_map_coefficients[zooom];
            }
            if (button3.isDouble())
            {
                yencode = yencode + move_map_coefficients[zooom];
            }
            //-norm
        }
        if (enreadvalue)
        {
            // norm
            // Serial.println("move");
            if (button2.isSingle())
            {
                Serial.println("move");
                xvalue = xvalue + 1;
                if (xvalue > envalueinterval)
                {
                    xvalue = 0;
                }
                if (xvalue < 0)
                {
                    xvalue = envalueinterval;
                }
            }
            if (button2.isDouble())
            {
                Serial.println("move");
                xvalue = xvalue - 1;
                if (xvalue > envalueinterval)
                {
                    xvalue = 0;
                }
                if (xvalue < 0)
                {
                    xvalue = envalueinterval;
                }
            }
            if (button3.isSingle())
            {
                Serial.println("move");
                yvalue = yvalue + 1;
                if (yvalue > envalueinterval)
                {
                    yvalue = 0;
                }
                if (yvalue < 0)
                {
                    yvalue = envalueinterval;
                }
            }
            if (button3.isDouble())
            {
                Serial.println("move");
                yvalue = yvalue - 1;
                if (yvalue > envalueinterval)
                {
                    yvalue = 0;
                }
                if (yvalue < 0)
                {
                    yvalue = envalueinterval;
                }
            }

            //-norm
        }
        if (button1.isSingle())
        {
            isPress1 = true;
        }
        if (button2.isSingle())
        {
            isPress2 = true;
        }

        if (button1.isTriple()&&can_change_window)
        {
            window_enc++;
            if (window_enc > 1)
            {
                window_enc = 0;
            }
            if (window_enc < 0)
            {
                window_enc = 1;
            }
        }
        vTaskDelay(1);
    }
    //-loop
    vTaskDelete(NULL);
}