# Open Connected Beehive project
A completely open-source device consisting of sensors to be attached to a beehive. These sensors gather data about the hive's conditions, and the data is then sent on to a web platform (also open-source). Monitored metrics include the weight of the beehive, the outside/inside temperature, the humidity, the number of bees going in and out of the hive, etc...
The web platform is accessible to everyone, allowing beekeepers to monitor their hives' well being, and researchers to gather more data about bees.
View the website [here](https://beetches.herokuapp.com/), and our Hackaday project page [here](https://hackaday.io/project/26182-open-connected-beehive).

# Project components

1. [Materials](https://hackaday.io/project/26182/components)
2. [Microcontroller code](https://github.com/rweinberger/connected-beehive/tree/master/arduino)
    * `trans_lorafeather.ino`: uploaded to LoRa feather (transmitter); reads sensor data and sends to second LoRa feather (receiver)
    * `rec_lora.ino`: uploaded to LoRa feather (receiver); receives data and sends it to WiFi feather
    * `lora_to_wifi.ino`: uploaded to WiFi ESP8266 feather; sends data to web server over WiFi
3. [Hardware setup](https://github.com/rweinberger/connected-beehive/tree/master/images)
    * Wireless LoRa transmitter
    * LoRa receiver to WiFi feather
4. [Website](https://github.com/rweinberger/connected-beehive-site/tree/766d86099f8420a70ec02faaa4ec69ae013b3f15)
    * Node.js powered web app to receive and display sensor data, both quantitatively and qualitatively
    * Currently live [here](https://beetches.herokuapp.com/)