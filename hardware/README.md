# ESP32 Project with TFT Display, Joystick, Buttons, and Audio Amplifier

## **Bill of Materials (BOM)**

| **Component**         | **Quantity** | **Details/Specifications**        | **Datasheet**                                                                 | **Purchase Link**                                                                |
|-----------------------|--------------|----------------------------------|-----------------------------------------------------------------------------|---------------------------------------------------------------------------------|
| ESP32 NodeMCU-32S     | 1            | Microcontroller with Wi-Fi/Bluetooth | [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.pdf) | [Buy Here](https://www.emag.ro/placa-esp32-cu-esp-wroom-32-38-pini-cu-cip-cp2102-multicolor-esp32-cp2102/pd/D7R798MBM/) |
| TFT Display ILI9488   | 1            | 3.95" SPI Display (480x320)      | [ILI9488 Datasheet](https://www.hpinfotech.ro/ILI9488.pdf)                   | [Buy Here](https://www.emag.ro/afisaj-lcd-ecran-touch-screen-tft-spi-3-95-ili9488-rezolutie-480x320-cu-sd-card-lcd395/pd/DV428TYBM/) |
| Analog Joystick       | 1            | 2-axis movement (VRX, VRY)       | [Joystick Datasheet](https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf) | [Buy Here](https://www.optimusdigital.ro/en/touch-sensors/742-ps2-joystick-breakout.html) |
| 6x Push Buttons       | 6            | Digital/Analog Input             | [Button Datasheet](https://www.ckswitches.com/media/1462/pts125.pdf)         | [Buy Here](https://www.emag.ro/buton-push-12-x-12-x-7-3-mm-ai510-s254/pd/DZPKQ7MBM/) |
| SD Card               | 1            | 128GB, FAT32 formatted           | N/A                                                                         | [Buy Here](https://www.emag.ro/card-de-memorie-samsung-evo-plus-128gb-mb-mc128ka-eu/pd/D778VXMBM/) |
| PAM8403 Amplifier     | 1            | Class D Audio Module (3W), I2S   | [PAM8403 Datasheet](https://www.mouser.com/datasheet/2/115/PAM8403-247318.pdf)| [Buy Here](https://www.emag.ro/modul-mini-amplificator-clasa-d-stereo-pam8403-de-3-w-cl648/pd/DNKGT1BBM/) |
| Speaker               | 1            | 8Ω, 1W                           | [Speaker Datasheet](https://www.farnell.com/datasheets/2827522.pdf)          | [Buy Here](https://www.optimusdigital.ro/en/speakers/2147-speaker-1-w.html)  |
| Resistors             | 6            | 1kΩ each                         | [Resistor Datasheet](https://docs.rs-online.com/0c4b/A700000008919910.pdf)   | [Buy Here](https://www.optimusdigital.ro/en/resistors/859-025w-1k-resistor.html) |
| Capacitor             | 1            | 10µF                             | [Capacitor Datasheet](https://ro.mouser.com/datasheet/2/88/SEK-3081771.pdf)  | [Buy Here](https://www.emag.ro/condensator-electrolitic-ajmaker-10uf-50-v-negru-argintiu-z000597/pd/D9HQLHYBM/) |
| Buck Converter        | 1            | MT3608 Step-Up Converter         | [MT3608 Datasheet](https://www.olimex.com/Products/Breadboarding/BB-PWR-3608/resources/MT3608.pdf) | [Buy Here](https://www.emag.ro/modul-convertor-step-up-cu-micro-usb-cu-mt3608-oky3501-6/pd/DXT4G9MBM/) |
| AA Battery Module     | 1            | Holder for 4x AA batteries       | [Battery Module Datasheet](https://www.farnell.com/datasheets/3497864.pdf)   | [Buy Here](https://www.optimusdigital.ro/en/battery-holders/12375-4-x-aa-battery-support.html) |
| AA Batteries          | 4            | R6, 1.5V each                    | N/A                                                                         | [Buy Here](https://www.emag.ro/baterii-energizer-max-aa-10-buc-7638900437775/pd/D3D1TGMBM/) |
| RGB LED               | 1            | Common cathode/anode RGB LED     | [RGB LED Datasheet](https://ro.mouser.com/datasheet/2/88/SEK-3081771.pdf)    | [Buy Here](https://www.optimusdigital.ro/en/leds/483-rgb-led-common-cathode.html) |
| Connection Wires      | 1 set        | Various jumper wires             | N/A                                                                         | [Buy Here](https://www.optimusdigital.ro/en/wires-with-connectors/12-breadboard-jumper-wire-set.html) |
| Universal PCB         | 1            | 9x15cm Prototype Board           | N/A                                                                         | [Buy Here](https://www.optimusdigital.ro/en/others/12518-9x15cm-universal-pcb-prototype-board-single-sided-254mm-hole-pitch.html) |

---

## **Hardware Functionality**

### **Components Used**
1. **ESP32 NodeMCU-32S**: Main microcontroller with Wi-Fi/Bluetooth connectivity.
2. **TFT Display ILI9488**: 3.95" display connected via **SPI protocol**.
3. **Analog Joystick**: Detects horizontal and vertical movement through VRX and VRY pins.
4. **6 Buttons**: Configured as digital/analog inputs.
5. **PAM8403 Amplifier**: Utilizes the **I2S interface** for digital audio output to an 8Ω speaker.
6. **SD Card**: Stores data, connected via **SPI protocol**.
7. **Buck Converter (MT3608)**: Converts and regulates voltage for ESP32 and other components.
8. **RGB LED**: Provides visual feedback.

---

## **Pin Configuration**

| **Component**         | **ESP32 Pins**           | **Description**                    |
|------------------------|-------------------------|------------------------------------|
| Buttons                | 26, 27, 33, 32, 34, 35 | Digital/Analog Inputs.             |
| Joystick (VRX, VRY)    | 39, 36                 | Analog inputs for horizontal/vertical movement. |
| SD Card                | 13 (CS), 14 (SCLK), 15 (MOSI), 19 (MISO) | SPI communication.                |
| TFT Display            | 5 (CS), 2 (DC), 4 (RST), 23 (MOSI), 18 (SCLK) | SPI communication.                |
| Joystick Switch        | 12                     | Digital Input.                     |
| PAM8403 Amplifier      | 25                     | I2S output for audio signal.       |
| RGB LED                | PWM pins               | Controlled for color indication.   |

---

## **Power Consumption**

- **Estimated Total Consumption**: ~475 mA.  
- **Battery Runtime**:  
   Using **4x AA batteries** (1.5V, ~2000mAh): approximately **4 hours** of operation.

---

## **Block Diagram**

![Block Diagram](![Blank diagram](https://github.com/user-attachments/assets/0a106e93-55a0-4ca5-a387-e1269dc94aad)
)

---

## **Electrical Scheme**

![Electrical Scheme](<img width="1752" alt="SchemaElectrica" src="https://github.com/user-attachments/assets/98ea4d95-5749-4253-904f-135c8345bb89" />
)
)

---

## **Images and Videos**

<details>
  <summary>Click to expand for images and videos</summary>

  ### **Circuit Image**
  ![Circuit Image](path_to_your_circuit_image.png)

  ### **Video Demonstration**
  [Watch Video Here](https://example.com/your-video-link)
</details>

---

## **Conclusion**
This project integrates the ESP32 NodeMCU-32S with multiple peripherals, including a TFT display, analog joystick, buttons, an audio amplifier (using I2S), and an SD card (using SPI). The setup provides full input, display, and audio output functionality.
