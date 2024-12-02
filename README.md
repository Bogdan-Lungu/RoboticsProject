# GameBoy Console with ESP32 and 4-Inch TFT Display

---

## Introduction

This project replicates a retro-style console inspired by the Nintendo NES but redesigned as a handheld device. It includes a collection of small, classic games such as Breakout, Space Invader, and Snake. The console combines retro gaming elements with the portability of handheld devices like the Nintendo Switch.

### Goals:
- Create a portable entertainment device for retro gaming enthusiasts.
- Explore the efficient use of memory in classic-style games.
- Leverage the ESP32 microcontroller to build a functional and cost-effective handheld gaming system.

### Applications:
- **Hobbyists**: Experimenting with microcontroller-based gaming and audio playback.
- **Students**: Learning embedded systems design and hardware-software integration.
- **Developers**: Understanding low-resource hardware designs for interactive projects.

---

## General Description

The project revolves around the **ESP32 NodeMCU-32s** as the main controller, interfacing with a 3.95-inch **ILI9488 TFT Display**, audio playback through a **PAM8403 amplifier**, and game inputs via multiplexed buttons and a joystick. An SD card reader on the display provides storage for assets.

### Block Diagram


+------------------+        +------------------+        +------------------+
| Power Source     |        | ESP32 NodeMCU   |        | ILI9488 Display  |
| (4xAA Batteries) |------->| (Main MCU)      |------->| (3.95" LCD, SD   |
| + On/Off Switch  |        |                 |        | Reader Attached) |
+------------------+        +------------------+        +------------------+
         |                          |
         |                          |
         v                          v
+------------------+        +------------------+
| Joystick         |        | PAM8403 Amplifier|
| + Buttons        |<------>| + Speaker (8Ω)  |
| (Multiplexed GPIO)|        +------------------+
         |
         v
+------------------+
| RGB LED          |
| Status Indicator |
+------------------+

 # Interaction Workflow

## Power Up:
- Turn on the device using the main switch.
- RGB LED shows the status of the system during startup.

## Game Start:
- Games are loaded and displayed on the LCD screen.
- Users interact with the game via buttons or the joystick.

## Audio Playback:
- Background music or sound effects are played through the PAM8403 amplifier connected to the speaker.

---

# Hardware Design

## Components List
- **ESP32 NodeMCU-32s**: Microcontroller and main control unit.
- **ILI9488 3.95-Inch LCD Display**: Screen for game rendering.
- **SD Card Reader (integrated with display)**: For external storage of assets.
- **PAM8403 Amplifier Module**: Amplifies audio signals from the ESP32.
- **8Ω, 1W Speaker**: For audio output.
- **Push Buttons (Multiplexed)**: Provide game controls.
- **Joystick**: Additional control for games requiring directional inputs.
- **On/Off Switch**: To control the device's power state.
- **RGB LED**: Displays device status.
- **Power Source (4xAA Batteries)**: Portable power for the device.

## Electrical Design
### Power Management:
- 4xAA batteries supply power.
- An on/off switch is used to conserve battery life.

### Display Integration:
- SPI communication with the ESP32.
- SD card reader directly attached to the display for file access.

### Audio:
- DAC output from the ESP32 connected to the PAM8403 amplifier.
- Amplified audio signals drive an 8Ω speaker.

---

# Software Design

## Development Environment
- **Arduino IDE**: Used for firmware development.

## Libraries Used
- **TFT_eSPI**: Handles the LCD display.
- **Adafruit GFX**: Provides advanced graphics rendering capabilities.
- **SD**: Enables access to the SD card for game files and audio data.
- **ESP8266Audio**: Handles audio playback and decoding.
- **Probably more to come as I progress**

## Algorithms and Logic
### Game Logic:
- Each game (e.g., Breakout, Snake) has its own loop, processing input from buttons and joystick.
- Game state is displayed on the LCD screen, and audio feedback is provided during events.

### Audio Playback:
- Background music and sound effects are loaded from the SD card.
- The ESP32 sends decoded audio data to the amplifier for playback.

---

# Results Obtained

## Functional Game Console:
- Classic-style games run smoothly on the ESP32.
- User inputs (buttons, joystick) are responsive.

## Integrated Audio Playback:
- Seamless background music and sound effects enhance the gaming experience.

## Portable Design:
- Operates effectively on 4xAA batteries, ensuring portability.

---

# Conclusions

This project demonstrates:
- The potential of the ESP32 for creating handheld entertainment devices.
- The effective integration of hardware components like an amplifier, display, and buttons.
- The efficiency of Arduino libraries in enabling complex functionality with limited resources.

---

# Source Code and Resources

## Repository Structure

ESP32-GameBoy/
├── src/
│   └── main.cpp
├── hardware/
│   └── schematic.pdf
├── images/
│   ├── block_diagram.png
│   └── hardware_layout.jpg
├── data/
│   ├── audio/
│   │   └── background.wav
│   └── games/
│       └── breakout.bin
└── README.md

## Demo Video

Embed a YouTube demo video:

[![Demo Video](https://img.youtube.com/vi/YourVideoID/0.jpg)](https://www.youtube.com/watch?v=YourVideoID)

---

## Journal

### Development Timeline
- **Day 1**: Configured display and SD card reader.
- **Day 2**: Implemented basic game logic for Breakout.
- **Day 3**: Integrated audio playback and debugging.

### Challenges
- Debugging SD card initialization issues.
- Fine-tuning audio synchronization with gameplay.

---

## Bibliography/Resources

### Hardware Resources
- **ESP32 NodeMCU-32s Datasheet**
- **PAM8403 Amplifier Datasheet**
- **ILI9488 LCD Documentation**

### Software Resources
- **[TFT_eSPI Library](https://github.com/Bodmer/TFT_eSPI)**
- **[ESP8266Audio Library](https://github.com/earlephilhower/ESP8266Audio)**
- **[Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)**
