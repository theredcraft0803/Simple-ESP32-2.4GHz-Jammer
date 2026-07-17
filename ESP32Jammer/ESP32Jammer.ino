#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"

byte full_channels[] = {
    1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
    43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
    85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100
};

const int num_full = sizeof(full_channels) / sizeof(full_channels[0]);

// === Radio Instances ===
// HSPI Bus (Modules 1 & 2)
RF24 radio_hspi1(26, 15); // CE=26, CSN=15 (Module 1)
RF24 radio_hspi2(27, 25); // CE=27, CSN=25 (Module 2)
// VSPI Bus (Modules 3 & 4)
RF24 radio_vspi1(4, 2);   // CE=4,  CSN=2  (Module 3)
RF24 radio_vspi2(16, 17); // CE=16, CSN=17 (Module 4)

// === State Variables ===
byte ch[4] = {45, 45, 45, 45};

void setup() {
  Serial.begin(115200);
  initializeJammers();
}

void loop() {
  runCurrentMode();
}

void initializeJammers() {
  // Disable ESP32 Bluetooth and Wi-Fi
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();

  // init HSPI (Module 1/2)
  SPIClass *hspi = new SPIClass(HSPI);
  hspi->begin(14, 12, 13, -1); // SCK=14, MISO=12, MOSI=13
  if (radio_hspi1.begin(hspi)) {
    Serial.println("HSPI Module 1 Jammer Initialized!");
    configureRadio(radio_hspi1, ch[0]);
  } else {
    Serial.println("HSPI Module 1 initialization failed!");
  }
  if (radio_hspi2.begin(hspi)) {
    Serial.println("HSPI Module 2 Jammer Initialized!");
    configureRadio(radio_hspi2, ch[1]);
  } else {
    Serial.println("HSPI Module 2 initialization failed!");
  }

  // init VSPI (Module 3/4)
  SPIClass *vspi = new SPIClass(VSPI);
  vspi->begin(18, 19, 23, -1); // SCK=18, MISO=19, MOSI=23
  if (radio_vspi1.begin(vspi)) {
    Serial.println("VSPI Module 3 Jammer Initialized!");
    configureRadio(radio_vspi1, ch[2]);
  } else {
    Serial.println("VSPI Module 3 initialization failed!");
  }
  if (radio_vspi2.begin(vspi)) {
    Serial.println("VSPI Module 4 Jammer Initialized!");
    configureRadio(radio_vspi2, ch[3]);
  } else {
    Serial.println("VSPI Module 4 initialization failed!");
  }
}

void runCurrentMode() {
  byte newCh[4];
  for (int i = 0; i < 4; i++) newCh[i] = full_channels[random(num_full)];
  updateChannels(newCh);
  delayMicroseconds(random(60));
}

void updateChannels(byte newCh[4]) {
  if (newCh[0] != ch[0]) { radio_hspi1.setChannel(newCh[0]); ch[0] = newCh[0]; }
  if (newCh[1] != ch[1]) { radio_hspi2.setChannel(newCh[1]); ch[1] = newCh[1]; }
  if (newCh[2] != ch[2]) { radio_vspi1.setChannel(newCh[2]); ch[2] = newCh[2]; }
  if (newCh[3] != ch[3]) { radio_vspi2.setChannel(newCh[3]); ch[3] = newCh[3]; }
}

void configureRadio(RF24& radio, byte channel) {
  radio.setAutoAck(false);
  radio.stopListening();
  radio.setRetries(0, 0);
  radio.setPALevel(RF24_PA_MAX, true);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.startConstCarrier(RF24_PA_MAX, channel);
}
