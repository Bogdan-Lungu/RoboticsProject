# ESP32 Gaming Console Project

## General Description
This project implements a gaming console based on the **ESP32** microcontroller, featuring classic games such as **Space Invaders**, **Breakout**, and **Dino**. The system integrates components such as an analog joystick, a TFT display, and DAC-generated sounds, effectively utilizing the hardware and software functionalities of the platform.

---

## Current Status of the Software Implementation
- **Implemented Games**:
  - **Space Invaders**: Fully functional gameplay with moving enemies and random enemy shooting.
  - **Breakout**: Ball, paddle, and brick collision logic are implemented.
  - **Dino**: Dynamically generated obstacles and jump/collision logic.
- **Graphical Interface**:
  - Main menu for game selection.
  - Post-game menu with options to replay or return to the main menu.
- **Additional Features**:
  - Custom sound effects and background music.
  - RGB LED feedback for in-game events.

---

## Motivation for the Chosen Libraries
- **TFT_eSPI**:
  - Provides a fast and efficient method to display graphics on the TFT screen.
  - Optimized for SPI communication and supports various TFT display types.
- **math.h**:
  - Used for precise calculations in generating trajectories and physics-based behaviors in games.
  - Functions like `cos()` and `sin()` are essential for ball dynamics in Breakout.
- **Arduino.h**:
  - Core library for handling hardware functions such as GPIO, multitasking, and more.
  - Facilitates easy interfacing with ESP32 components.

---

## "New" aspect of the game
- Integration of multiple games into a single system with an intuitive menu and simple interactions.
- RGB LED feedback to enhance the gaming experience.
- Custom sound, making the experience more immersive.

---

## Justification for Using Laboratory Features
- **GPIO Pins**:
  - Used for reading joystick positions (X and Y axes) to control the player or paddle.
  - Control of the RGB LED to indicate different states or actions.
- **SPI (Serial Peripheral Interface)**:
  - Communicates with the TFT display for rendering graphics.
  - Extends functionality by supporting SD card storage.
- **ADC (Analog to Digital Converter)**:
  - Converts analog joystick signals for user interaction.
- **DAC (Digital to Analog Converter)**:
  - Generates sounds for music and sound effects.

---

## Project Structure and Validation of Functionalities
### Project Structure
- **Main Menu**: Allows the user to select one of three games.
- **Games**:
  - **Space Invaders**: Enemies, ship, and logic for bullets and collisions.
  - **Breakout**: Ball, paddle, and brick collision logic.
  - **Dino**: Jumping, dynamically generated obstacles, and collision logic.
- **Post-game Menu**: Offers options to replay or return to the main menu.

### Validation
- Each functionality has been individually tested, including joystick interaction, TFT display graphics, and RGB LED feedback.
- Games were tested for:
  - Correct collisions (bullets, ball, dino vs obstacles).
  - Real-time score updates and rendering.
  - Proper sound generation during game events.

---

## Demo Video
A demo video showcasing all project functionalities, including game selection, gameplay for each game, and general interface interaction, has been created. The video is available on YouTube and can be viewed 

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/9yQ0Fiu_aGQ/0.jpg)](https://youtu.be/9yQ0Fiu_aGQ)

---

## Sensor Calibration
- **Joystick**:
  - Analog values were read directly from ADC pins, with predefined thresholds for movement detection.
  - A dead zone was implemented to ignore minor signal fluctuations.
- **RGB LED**:
  - Digital values were used to control each LED (R, G, B) independently, enabling distinct color combinations for feedback events.
- **Sound**:
  - DAC-generated tones were manually tuned to match accurate frequencies for musical notes, ensuring smooth and harmonious playback.

---

## Optimizations
- **Graphics**:
  - Visual elements are updated only when their positions change, reducing full screen redraws.
- **Memory**:
  - Matrix and structure sizes were adjusted to minimize memory usage.
- **Sound**:
  - Sound signal generation uses simplified logic to reduce processor load.
- **Modularity**:
  - The code is organized into sections (menus, games, utility functions) for readability and easy extension.

---



