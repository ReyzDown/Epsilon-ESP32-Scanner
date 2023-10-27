// Author: [Eunous]
// Creation Date: [10/27/23]
// Description: This program performs WIFI Scan and display results in Serial Monitor.
// The use of this code is solely the responsibility of the user.

#include "wifiScan.h"

// Include the "wifiScan.h" header file required for this code.

void WiFiScanner::Scan() {
    // Display a message indicating that Wi-Fi scanning is starting.
    int n = WiFi.scanNetworks();
    Serial.println("Scan Start");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH |    Mac Address    | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            Serial.printf("%s | ", WiFi.BSSIDstr(i).c_str());
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    // Clear the list of scanned Wi-Fi networks.
    WiFi.scanDelete();
    Serial.println("Scan done");

    // Wait for 5 seconds before scanning again.
    delay(5000);
}

void WiFiScanner::Disconnect() {
    // Change the Wi-Fi mode to station mode (WIFI_STA) and disconnect from Wi-Fi.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
}