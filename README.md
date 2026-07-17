# Simple ESP32 2.4GHz Jammer

A simple ESP32-based 2.4 GHz jammer using up to four nRF24L01+ modules.

## Hardware Connections

### Module 1 (HSPI)

| nRF24L01+ | ESP32 GPIO |
| --------- | ---------- |
| SCK       | GPIO14     |
| MOSI      | GPIO13     |
| MISO      | GPIO12     |
| CE        | GPIO26     |
| CSN       | GPIO15     |

### Module 2 (HSPI)

| nRF24L01+ | ESP32 GPIO |
| --------- | ---------- |
| SCK       | GPIO14     |
| MOSI      | GPIO13     |
| MISO      | GPIO12     |
| CE        | GPIO27     |
| CSN       | GPIO25     |

### Module 3 (VSPI)

| nRF24L01+ | ESP32 GPIO |
| --------- | ---------- |
| SCK       | GPIO18     |
| MOSI      | GPIO23     |
| MISO      | GPIO19     |
| CE        | GPIO4      |
| CSN       | GPIO2      |

### Module 4 (VSPI)

| nRF24L01+ | ESP32 GPIO |
| --------- | ---------- |
| SCK       | GPIO18     |
| MOSI      | GPIO23     |
| MISO      | GPIO19     |
| CE        | GPIO16     |
| CSN       | GPIO17     |

### Power Supply

Connect **all** nRF24L01+ modules as follows:

* **VCC → 3.3V**
* **GND → GND**

> **Important:** Do **not** connect the nRF24L01+ modules to 5V, as this may permanently damage them.

## Installation

1. Open the project in the Arduino IDE (or another compatible IDE).
2. Select your ESP32 board.
3. Install all required libraries.
4. Compile and upload the firmware.
5. Power the ESP32.

## Disclaimer

This project is provided for **educational and research purposes only**. Ensure that you comply with all applicable laws and regulations when experimenting with radio-frequency hardware. The author assumes no responsibility for misuse or any damage caused by this project.
