# ard_uno_loadcell_display

Display Load Cell Measurements using a LCD Display w/ your Arduino Uno

## Getting Started

### Install the PlatformIO IDE VSCode Extension

Install the PlatformIO IDE extension from the VSCode extension marketplace (see workspace recommendations). You may be asked to install Python. You may follow the instructions [here](https://docs.platformio.org/en/latest/faq/install-python.html).

### Initialize the Project

In this example a PlatformIO project has already been created. The project configuration can be inspected in the [platformio.ini](./platformio.ini) file.

The `platformio` (or `pio`) command-line interface should be installed along the the extension. For the local development purposes you need to intialize the command-line interface. Execute the following commands in the command-line:

```bash
pio project init
```

Note: The command-line has to be a PlatformIO terminal. You can create a new PlatformIO termincal by pressing the `PlatformIO: New Terminal` buttom in the bottom left of your VSCode window.

Run the `pio check` command to do a static code analysis to check if everything is setup correctly.

### Set up Configuration and Secrets

You can find sections below on how to handle [configuration](#configuration) down below. Make to follow the instructions and you should be good to go.

### Connect the Hardware

For the project you need to have a:

- [Arduino UNO R3]
- [Mavin Load Cell - S Type - 200kg]
- [Load Cell Amplifier- HX711]
- [GeeekPi 2-Pack I2C 1602 LCD Display Module 16X]

Connect the [GeeekPi 2-Pack I2C 1602 LCD Display Module 16X] to the [Arduino UNO R3] based on the following layout:

| [Arduino UNO R3] | Cable Color | [GeeekPi 2-Pack I2C 1602 LCD Display Module 16X] |
| ---------------- | ----------- | ------------------------------------------------ |
| GND              | Black       | GND                                              |
| 5V               | Red         | VCC                                              |
| A4               | Yellow      | SDA                                              |
| A5               | Orrange     | SCL                                              |

You may want to check the [Z-0234 1602 Serial LCD Module Display Documentation] or the [Arduino UNO R3] documentation.

Next connect the [Load Cell Amplifier- HX711] to the [Arduino UNO R3] using the following layout:

| [Arduino UNO R3] | Cable Color | [Load Cell Amplifier- HX711] |
| ---------------- | ----------- | ---------------------------- |
| GND              | Black       | GND                          |
| 5V               | Red         | VCC                          |
| D5               | Yellow      | DT                           |
| D6               | Orrange     | SCL                          |

Lastly connect the [Load Cell Amplifier- HX711] to the [Mavin Load Cell - S Type - 200kg] according to this layout:

| [Load Cell Amplifier- HX711] | [Mavin Load Cell - S Type - 200kg] Cable Color |
| ---------------------------- | ---------------------------------------------- |
| E+                           | Red                                            |
| E-                           | Black                                          |
| A-                           | White                                          |
| A+                           | Green                                          |

The transparent cable of the [Mavin Load Cell - S Type - 200kg] is not connected to anything. You may refer to the [Tutorial to Interface HX711 Balance Module With Load Cell] for guidance.

### Build and Upload the Code to a Arduino Nano ESP32

After installation and initialization you may build and upload the code to your device. Connect the Ardunino Nano ESP32 via USB. Then run the following commands (in a PlatformIO terminal):

```bash
# Check if your device can be detected
pio device list
# Build the code
pio run -e uno -t build
# Upload the build
pio run -e uno -t upload
```

As an alternative to the command you can also use the PlatformIO buttons in VSCode. You can find the buttons below. Make szre to select the correct (`uno`) environment for the upload.

### Run Tests

```bash
# Run test locally on your desktop
pio test -e desktop
# Run test on the device
pio test -e uno
```

#### Debug Tests

If you are using VSCode (which is recommended), use the following steps to debug your test runs:

1. Select the `desktop` environment to select your local machine as the build target
2. Open the testing module [test_desktop_main.cpp](test/test_desktop/test_desktop_main.cpp) in your editor
3. Go to the debug tab in VSCode
4. Launch the code with the `PIO Debug` configuration

This will automatically attach a gdb debugger and enable VSCode debugging.

## Documentation

### Configuration

Set the configuration in the [config.h](lib/Config/config.h) header file. Use the provided constants as they are used in the code.

## Sources

- [Arduino UNO R3]
- [Mavin Load Cell - S Type - 200kg]
- [Load Cell Amplifier- HX711]
- [GeeekPi 2-Pack I2C 1602 LCD Display Module 16X]
- [Z-0234 1602 Serial LCD Module Display Documentation]
- [Tutorial to Interface HX711 Balance Module With Load Cell]

[Arduino UNO R3]: https://docs.arduino.cc/hardware/uno-rev3/
[Mavin Load Cell - S Type - 200kg]: https://www.tinytronics.nl/en/sensors/weight-pressure-force/load-cells/mavin-load-cell-s-type-200kg
[Load Cell Amplifier- HX711]: https://www.tinytronics.nl/en/sensors/weight-pressure-force/load-cells/load-cell-amplifier-hx711
[GeeekPi 2-Pack I2C 1602 LCD Display Module 16X]: https://www.amazon.com/GeeekPi-Character-Backlight-Raspberry-Electrical/dp/B07S7PJYM6
[Z-0234 1602 Serial LCD Module Display Documentation]: https://wiki.52pi.com/index.php?title=Z-0234
[Tutorial to Interface HX711 Balance Module With Load Cell]: https://www.instructables.com/How-to-Interface-HX711-Balance-Module-With-Load-Ce/
