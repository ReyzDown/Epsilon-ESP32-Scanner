// Author: [Eunous]
// Date: [10/27/23]
// Description: This code creates a Wi-Fi soft access point (AP) with lyrics from the song "Never Gonna Give You Up" by Rick Astley.
// The use of this code is solely the responsibility of the user.

#include "rickroll.h"

// Include the "rickroll.h" header file required for this code.

// Lyrics from the song "Never Gonna Give You Up" by Rick Astley.
String never_gonna[] = {
    "We're no strangers to love",
    "You know the rules and so do I",
    "I just want to tell you how I'm feeling"
};

void rickroll::RickRollTask() {
    // Scan for available Wi-Fi networks and store the count.
    int network = WiFi.scanNetworks();
    Serial.println(network);

    // Calculate the size of the "never_gonna" array.
    size_t arraySize = sizeof(never_gonna) / sizeof(never_gonna[0]);
    size_t n = 0;

    // Start a Wi-Fi soft access point for each line of the lyrics.
    while (n < arraySize) {
        WiFi.softAP(never_gonna[n].c_str());
        n++;
    }

    // Scan for available Wi-Fi networks again and store the count.
    network = WiFi.scanNetworks();
    Serial.println(network);

    // Delay for 1 second.
    delay(1000);
}