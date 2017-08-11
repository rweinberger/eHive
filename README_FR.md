<h1>Open connected beehive, Ruche Connectée</h1>

C’est un device totalement open-source qui consiste en des capteurs (sensors) reliés à la ruche. Ces capteurs collectent les données sur les conditions de vie de la ruche et les données sont envoyées à une plateforme web open-source. Les mesures affichées incluent le poids de la ruche, les températures à l’intérérieur et à l’extérieur de la ruche, l’humidité, le nombre d’abeilles qui entrent et sortent de la ruche,etc…

La plateforme web est accessible à tous, elle permet aux apiculteurs de s’informer de la santé de la ruche d’une part, et aux chercheurs de collecter plus de données au sujet des abeilles d’autre part.

Ce projet a été créé pendant la Summer Class 2017 du CRI (Centre de la Recherche interdisciplinaire) par Tanguy Chotel, Pauline Ko, Alfredo L’homme, Lin Li, Nikola Maksic et Rebecca Weinberger. Le site web est visible à cette adresse, et la page Hackaday du projet est visible ici. 

# Sommaire
1. [Matériel](https://github.com/rweinberger/eHive/#materials)
2. [Code des microcontroleurs](https://github.com/rweinberger/eHive/#microcontroller-code)
3. [Configuration du matériel](https://github.com/rweinberger/eHive/#hardware-setup)
4. [Plateforme Web](https://github.com/rweinberger/eHive/#website)

# Matériel
[Matériel](https://hackaday.io/project/26182/components)

# Codes des microcontroleurs
[Code](https://github.com/rweinberger/eHive/tree/master/arduino)

1. `trans_lorafeather.ino`: uploaded to LoRa feather (transmitter); reads sensor data and sends to second LoRa feather (receiver)
2. `rec_lora.ino`: uploaded to LoRa feather (receiver); receives data and sends it to WiFi feather
3. `lora_to_wifi.ino`: uploaded to WiFi ESP8266 feather; sends data to web server over WiFi

# Configuration du matériel
[Branchements](https://github.com/rweinberger/eHive/tree/master/images)


1. L’émetteur LoRa (**A**) est relié au capteur de température à distance (**B**), aux sensors de température et d’humidité (**C**) et à l’amplificateur de cellule de charge (**D**). Le tout est relié aux capteurs à échelle par le combinateur de charge (**montré ci-dessous**).
![alt text][lora_trans]
2. Raccordement du combinateur de charge (**E**). Chacun des 4 capteurs de charge (**F**) est attaché à la carte comme indiqué. Les broches YLW / GRN / WHT / BLK / RED correspondent aux broches du même nom sur l'amplificateur de cellule de charge dans le schéma précédent.
 ![alt text][load_combinator]
3. Un deuxième récepteur LoRa (**G**) est connecté à une carte WiFi (**H**). De la carte WiFi, les données sont envoyées au serveur web.
 ![alt text][lora_to_wifi]

# Plateforme web 

[projet sur Github](https://github.com/rweinberger/eHive-site/tree/766d86099f8420a70ec02faaa4ec69ae013b3f15)

1. Application Web basée sur Node.js pour recevoir et afficher les données du capteur en temps réel, quantitativement et qualitativement.
2. Démo [ici](https://beetches.herokuapp.com/)


[lora_trans]: https://raw.githubusercontent.com/rweinberger/eHive/master/images/lora_trans.png
[load_combinator]: https://raw.githubusercontent.com/rweinberger/eHive/master/images/load_combinator.png
[lora_to_wifi]: https://raw.githubusercontent.com/rweinberger/eHive/master/images/lora_to_wifi.png

