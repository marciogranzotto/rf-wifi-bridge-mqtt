# MQTT RF bridge

This project is a RF-WiFi bridge that receives commands using MQTT.

## Bill of Materials
- ESP8266 board (NodeMCU and ESP07 targets are included)
- RF Transmitter and optionally, a Receiver
  - [Here's the ones that I've used](https://www.aliexpress.com/item/433-Mhz-Superheterodyne-RF-Receiver-and-Transmitter-Module-ASK-low-power-kits-For-Arduino-ARM-MCU/32728352611.html)

## Flashing it

This project is ready to be used with Plataform.io, but you can use the regular Arduino IDE.

You have only to change a few parameters such your MQTT and WiFi information.

## Dependencies

- [rc-switch](https://github.com/sui77/rc-switch)
- [PubSubClient](https://github.com/knolleary/pubsubclient)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

## How to use it

The firmware expects a JSON payload with the RF information. Here's an example:
```json
{
    "protocol": 6,
    "pulse_length": 484,
    "binary": "1001101001100101100011110101"
}
```
You can get this information using the [example code](https://github.com/sui77/rc-switch/tree/master/examples/ReceiveDemo_Advanced) from the `rc-switch` library.
