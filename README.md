# Feinstaub-App LoRa initialization script
Script for testing lora chip with esp8266 and lora module rn2483.

The following settings are used to run this script on esp8266:

Settings -> Additional board manager urls: http://arduino.esp8266.com/stable/package_esp8266com_index.json
Tools -> Board -> Board manager: Search for Esp8266 Community and install the latest version (tested with version 2.4.2)

Make following settings in the Tools-menu:
- Board: NodeMCU 1.0 (ESP-12E Module)
- Upload Speed: 256000
- Flash Size: 4M (3M SPIFFS)

Following libraries have to be installed:
- SoftwareSerial
- rn2xx3 (you don't need to add this. It is in libs folder)

NOTE: YOU HAVE TO ADD THE CONTENTS OF THE LIBS FOLDER TO YOUR LIBRARIES FOLDER IN YOUR LOCAL PROJECT DIRECTORY.

© M&R Games 2019 (Designed and developed by Marc Auberer in 2019)
