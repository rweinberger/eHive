# The eHive: an open-source connected beehive
A completely open-source device consisting of sensors attached to a beehive. These sensors gather data about the hive's conditions, and the data is then sent on to a web platform (also open-source). Monitored metrics include the weight of the beehive, the outside/inside temperature, the humidity, the number of bees going in and out of the hive, etc...


The web platform is accessible to everyone, allowing beekeepers to monitor their hives' well being, and researchers to gather more data about bees.


This project was created during the 2017 CRI Summer School by Tanguy Chotel, Pauline Ko, Alfredo L'homme, Lin Li, Nikola Maksic, and Rebecca Weinberger. View the website [here](https://beetches.herokuapp.com/), and our Hackaday project page [here](https://hackaday.io/project/26182-ehive).

# Contents
1. [Materials](https://github.com/rweinberger/eHive/#materials)
2. [Microcontroller code](https://github.com/rweinberger/eHive/#microcontroller-code)
3. [Hardware Setup](https://github.com/rweinberger/eHive/#hardware-setup)
4. [Website](https://github.com/rweinberger/eHive/#website)

# Materials
[Materials](https://hackaday.io/project/26182/components)

# Microcontroller code
[Microcontroller code](https://github.com/rweinberger/eHive/tree/master/arduino)

1. `trans_lorafeather.ino`: uploaded to LoRa feather (transmitter); reads sensor data and sends to second LoRa feather (receiver)
2. `rec_lora.ino`: uploaded to LoRa feather (receiver); receives data and sends it to WiFi feather
3. `lora_to_wifi.ino`: uploaded to WiFi ESP8266 feather; sends data to web server over WiFi

# Hardware setup
[Hardware setup](https://github.com/rweinberger/eHive/tree/master/images)

1. Wireless LoRa feather transmitter (**A**) hooked up to remote temperature probe (**B**), temperature & humidity sensor (**C**), and load cell amplifier (**D**), which is connected to scale sensors by load combinator (**shown below**)
![alt text][lora_trans]
2. Hookup of load combinator (**E**). Each of the 4 load sensors (**F**) is attached to the board as shown. The YLW/ GRN/ WHT/ BLK/ RED pins correspond to the pins of the same name on the load cell amplifier in the previous schematic.
![alt text][load_combinator]
3. A second LoRa feather receiver (**G**) is connected to a WiFi feather (**H**). From the WiFi feather, data is sent to the web server.
![alt text][lora_to_wifi]

# Website 

[Website](https://github.com/rweinberger/eHive-site/tree/766d86099f8420a70ec02faaa4ec69ae013b3f15)

1. Node.js-based web app to receive and display sensor data in real time, both quantitatively and qualitatively
2. Currently live [here](https://beetches.herokuapp.com/)

[lora_trans]: https://raw.githubusercontent.com/rweinberger/eHive/master/images/lora_trans.png
[load_combinator]: https://raw.githubusercontent.com/rweinberger/eHive/master/images/load_combinator.png
[lora_to_wifi]: https://raw.githubusercontent.com/rweinberger/eHive/master/images/lora_to_wifi.png