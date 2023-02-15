# Single DHT11
Independent DHT11 Webserver using ESP8266. 

Based on a very good tutorial from https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/. 

However instead of using Adafruit library, we are using a DHT11 library from DFRobot: https://github.com/seryafarma/DFRobot_DHT11.

Simple refactoring of files are also done, splitting the projects to smaller pieces.

## Hardware
The hardware utilizes a ESP8266 NodeMCU Lolin v3 board. It is connected to Pin 5 which is mapped to 14 in case of ESP8266.

See also: https://create.arduino.cc/projecthub/electropeak/getting-started-w-nodemcu-esp8266-on-arduino-ide-28184f

## Software
* Another simple two states approach using simple state machine library.
* Asynchronous ESP8266 webserver.
* Small javascript to query information from cache.