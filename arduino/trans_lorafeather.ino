// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_RX

#include <SPI.h>
#include <RH_RF95.h>
#include <Adafruit_Si7021.h>
#include <HX711.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/* for feather32u4 */
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 868.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Temperature probe outside the scale

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 20
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Calibration factor for the scale
//#define calibration_factor -7050.00

// Temperature & humidty sensors inside the device

Adafruit_Si7021 sensor = Adafruit_Si7021();
HX711 scale(18, 19);

float si_hum;
float si_temp;
//float wt;
float ex_temp;

void setup() 
{
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

//  while (!Serial);
  Serial.begin(9600);
  delay(100);

  Serial.println("Feather LoRa TX Test!");

  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); 
  Serial.println(RF95_FREQ);
  
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 5 to 23 dBm:
  rf95.setTxPower(23, false);

  delay(10);
  sensor.begin();
  delay(10);
  sensors.begin(); // DS18B20

//  scale.set_scale(calibration_factor);
//  scale.tare();
}

void loop()
{
  // Gathering sensor data (inside the device)
  si_hum = sensor.readHumidity();
  si_temp = sensor.readTemperature();
//  wt = scale.get_units()*.45;

  // Gathering temp probe data
  sensors.requestTemperatures();
  ex_temp = sensors.getTempCByIndex(0);
  
  Serial.println("Sending to rf95_server");
// Send a message to rf95_server
  
  String str_radiopacket = "</push?temp="+String(ex_temp)+"&hum="+String(si_hum)+"&wt=0"+String(wt)+">";
  
  char *radiopacket = &str_radiopacket[0u];

  Serial.print("Sending "); Serial.println(radiopacket);
    
  Serial.println("Sending..."); 
  delay(10);
  rf95.send((uint8_t *)radiopacket, str_radiopacket.length() + 1);


  Serial.println("Waiting for packet to complete..."); 
  delay(10);
  rf95.waitPacketSent();
  
  // Now wait for a reply
  
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  Serial.println("Waiting for reply..."); 
  delay(10);
  if (rf95.waitAvailableTimeout(1000))
  { 
    // Should be a reply message for us now   
    if (rf95.recv(buf, &len))
   {
      Serial.print("Got reply: ");
      Serial.println((char*)buf);
      Serial.print("RSSI: ");
      Serial.println(rf95.lastRssi(), DEC);    
    }
    else
    {
      Serial.println("Receive failed");
    }
  }
  else
  {
    Serial.println("No reply, is there a listener around?");
  }
  delay(1000);
}
    
