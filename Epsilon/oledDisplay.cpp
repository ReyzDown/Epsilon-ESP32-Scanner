/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-oled
 */

#include "oledDisplay.h"

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

// create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


bool Display::displayWifiScan(int n, int i, String SSID, int RSSI, int Channel, String MACADD, String EncType){
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        return false;
    }
    
    oled.clearDisplay(); // clear display   
    oled.setTextSize(1);         // set text size
    oled.setTextColor(WHITE);    // set text color
    oled.setCursor(0, 0);  
    oled.println(n + "Network found");
    oled.display();
    delay(1000);
    oled.clearDisplay();
    oled.setCursor(0,10);
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.println("Nr | SSID | RSSI | CH | MAC Address | Encryption");
    oled.display();
    
    char message[100]; // Déclarez un tableau de caractères pour stocker le message formaté
    sprintf(message, "%2d  | %-32.32s | %4d | %s | %s ", i + 1, SSID, RSSI, Channel, MACADD, EncType);
    oled.println(message); // Imprimez le message formaté
    oled.display();
    return true;
}
bool Display::displayBLEScan(String advertize){
    oled.clearDisplay();
    oled.setTextSize(1);         
    oled.setTextColor(WHITE);
    oled.printf("%s", advertize);
    return true;
}
void Display::test(){
  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 10);       // set position to display
  oled.println("com"); // set text
  oled.display();              // display on OLED

}
