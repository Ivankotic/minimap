#pragma once

class systemSettings
{
public:
    systemSettings();

    int getZoom();
    String setZoom(int int_to_write);
    int saveDot(float xb, float yb, String name);
    int getDots();
};

systemSettings::systemSettings()
{
    if (!(read_from_card("/systemData/data_state") == "normal"))
    {
        Serial.println(!(read_from_card("/systemData/data_state") == "normal"));
        write_to_card("/readme.txt", readmeText);
        vTaskDelay(20);
        make_dir("/systemData/");
        write_to_card("/systemData/data_state", "normal");
        vTaskDelay(20);
        write_to_card("/systemData/mapZoom", "13");
        vTaskDelay(20);
        write_to_card("/systemData/dots", "0");
    }
    
}

int systemSettings::saveDot(float xb, float yb, String name) {
    int dots_k = read_from_card("/systemData/dots").toInt();
    
    if ((dots_k + 1) > 10) {
        return(1);
    }
    
    dots_k = dots_k + 1;
    Serial.println(String(xb));

    vTaskDelay(20);
    write_to_card_fl("/systemData/dot_x_" + String(dots_k), xb);

    vTaskDelay(20);
    write_to_card_fl("/systemData/dot_y_" + String(dots_k), yb);

    vTaskDelay(20);
    write_to_card("/systemData/dot_name_" + String(dots_k), name);

    Serial.println(dots_k);

    vTaskDelay(20);
    write_to_card("/systemData/dots", String(dots_k));

    return(0);
}

int systemSettings::getZoom()
{
    SdFat sd;
    if (!sd.begin(SD_PIN, SD_SCK_MHZ(20)))
    {
        return (1);
    }
    File myFile;
    myFile = sd.open("/systemData/mapZoom", FILE_READ);
    String readeddata = "";
    while (myFile.available())
    {
        readeddata += (char)myFile.read();
    }
    myFile.close();
    return (readeddata.toInt());
}

int systemSettings::getDots()
{
    int dots_k = read_from_card("/systemData/dots").toInt();
    for (int i = 0; i < dots_k; i++)
    {
        if (i > 9) break;
        dot_list[i] = read_from_card("/systemData/dot_name_" + String(i + 1));
        dot_list_x[i] = read_from_card("/systemData/dot_x_" + String(i + 1));
        dot_list_y[i] = read_from_card("/systemData/dot_y_" + String(i + 1));
        vTaskDelay(20);
    }
    return(0);
}

String systemSettings::setZoom(int int_to_write)
{
    String path = "/systemData/mapZoom";
    String to_write = String(int_to_write);
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
    delete buf;
    return ("ok");
}
