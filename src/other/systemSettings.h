#pragma once

class systemSettings
{
public:
    systemSettings();

    int getZoom();
    String setZoom(int int_to_write);
};

systemSettings::systemSettings()
{
    if (!(read_from_card("/system_data/data_state") == "normal"))
    {
        Serial.println(!(read_from_card("/system_data/data_state") == "normal"));
        make_dir("/system_data/");

        write_to_card("/system_data/data_state", "normal");
        vTaskDelay(20);
        write_to_card("/system_data/mapZoom", "13");
    }
    
}

int systemSettings::getZoom()
{
    SdFat sd;
    if (!sd.begin(SD_PIN, SD_SCK_MHZ(20)))
    {
        return (1);
    }
    File myFile;
    myFile = sd.open("/system_data/mapZoom", FILE_READ);
    String readeddata = "";
    while (myFile.available())
    {
        readeddata += (char)myFile.read();
    }
    myFile.close();
    return (readeddata.toInt());
}

String systemSettings::setZoom(int int_to_write)
{
    String path = "/system_data/mapZoom";
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
