/*
   Author: [Eunous]
   Date: [10/27/23]
   Description: This code combines functionalities for Wi-Fi scanning, BLE scanning, and a humorous "Rickroll" prank using ESP32.
   The use of this code is for demonstration or educational purposes.

   Instructions:
   1. Include the necessary header files: "wifiScan.h" "BLEScan.h" "rickroll.h" "deauther.h".
   2. Initialize instances for Wi-Fi scanning, BLE scanning, and the Rickroll class.
   3. In the setup function, begin the Serial communication and disconnect from any existing Wi-Fi networks.
   4. In the loop function, call functions to perform Wi-Fi scanning, BLE scanning, and the Rickroll prank.
*/

#include "wifiScan.h"
#include "BLEScan.h"
#include "rickroll.h"
#include "deauther.h"

// Initialize instances for various functionalities.
rickroll RickRoll;
Deauther Deauth;
WiFiScanner WIFIScan;
BLEScanner BLEScanner;

void setup() {
  // Begin Serial communication at a baud rate of 115200.
  Serial.begin(115200);

  // Disconnect from any existing Wi-Fi networks.
  WIFIScan.Disconnect();
}

void loop() {
  // Perform Wi-Fi scanning.
  WIFIScan.Scan();

  // Perform BLE scanning.
  BLEScanner.Scan();

  // Execute the Rickroll prank.
  RickRoll.RickRollTask();

  //Perform Deauth check deauther.cpp u need to enter MAC ADDRESS From AP and TARGET
  Deauth.SpamTask();
}