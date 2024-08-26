# Open-Delphi-Display
Thanks to the original developer for creating the original code that sprung this project!!!

Current status: In progress - Please do not load the existing code until official release!

This is a fork designed specifically for Open-Delphi support. This is designed (currently) for P01/P59 ECU's, standard in most LS swaps and 97-2008(ish) vehicles. 

Mapping for the newer ECU architectures will come, along with additional features and benefits as it integrates into the Open-Delphi tuning platform

## Open-Delphi-Display Features:
- Generic 0-5v Analog sensor input support
- Wideband Display support
- Flex Fuel % Display
- Vehicle Controls:
  - Fan On/Off Command
  - Lockup Control
- More to come

## Software:
- Arduino IDE 2.3.2 + ESP32 arduino core 2.0.17
- modified TFT_eSPI library 2.5.43

## Minimum Requirements
- ESP32-Wroom TFT 2.8 320x240
- ELM327 Bluetooth adapter
- Speaker (if desired)
- Push Button (2 Pole)
- 12v to 5v dc micro usb power regulator module
  
## Original Features:
- 8 layout page selectable display
- DTC read and clear function (Engine warning light only)
- Warning when parameter reaches setting value
- Adjustable warning value for each PIDs
- Configurable CPU overheat protection
- Configurable gauge Auto turn on/off
- Auto screen brightness
- Change off screen to user screen with micro SDcard
- Firmware updatable (micro SDcard and WiFi)
- VIN Read on the About page.
