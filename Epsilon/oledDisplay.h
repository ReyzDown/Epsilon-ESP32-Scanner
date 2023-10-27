
#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

// #include <WiFi.h>
// #include "esp_wifi.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "String.h"


class Display {
public:
    bool displayWifiScan(int n, int i, String SSID, int RSSI, int channel, String MACADD, String EncType);
    bool displayBLEScan(String advertize);
    void test();
};
#endif
