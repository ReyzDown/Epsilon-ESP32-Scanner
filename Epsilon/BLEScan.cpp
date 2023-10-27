// Author: [Author's name or alias]
// Creation Date: [Creation Date]
// Description: This program performs BLE scanning and displays the results in Serial Monitor.
// The use of this code is solely the responsibility of the user.

#include "BLEScan.h"
#include "NimBLEDevice.h"

NimBLEScan* pBLEScan;
Display BLEDisplay; // Make sure that the Display class is correctly defined in OLEDLibrary.

// Class for callbacks of advertised BLE devices
class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
    void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice->toString().c_str());
    }
};

void BLEScanner::Scan() {
  // Configure BLE scanning parameters
  NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
  NimBLEDevice::setScanDuplicateCacheSize(200);
  NimBLEDevice::init("");

  // Obtain the BLE scanning instance
  pBLEScan = NimBLEDevice::getScan();

  // Set the advertised device callbacks to handle scan results
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks(), false);

  // Configure scanning parameters
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(97);
  pBLEScan->setWindow(37);
  pBLEScan->setMaxResults(0);

  while (true) {
    // Check if scanning is not already in progress and start it
    if (pBLEScan->isScanning() == false) {
      pBLEScan->start(0, nullptr, false);
    }
    // Wait for a certain duration before scanning again
    delay(2000);
  }
}
