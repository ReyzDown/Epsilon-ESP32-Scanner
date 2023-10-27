
#ifndef WIFI_SCANNER_H
#define WIFI_SCANNER_H

#include <WiFi.h>
#include "oledDisplay.h"
#include "String.h"


class WiFiScanner {
public:
    void Scan();
    void Disconnect();
    
};
#endif
