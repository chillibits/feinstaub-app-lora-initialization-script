#include <rn2xx3.h>
#include <SoftwareSerial.h>

#define RST 13 // D7
SoftwareSerial lora_serial(12, 14); // RX: D6, TX: D5

rn2xx3 lora(lora_serial);

typedef struct lora_payload {
  int pm2_5: 12;
  int pm10: 12;
  int temp: 8;
  int humidity: 10;
  int pressure: 8;
  int pm2_5_accuracy: 1;
  int pm10_accuracy: 1;
  int reserved1_accuracy: 1;
  int reserved2_accuracy: 1;
  int reserved3_accuracy: 1;
  int reserved4_accuracy: 1;
} lora_payload;


void setup() {
  Serial.begin(57600);
  lora_serial.begin(9600);

  delay(2000);

  Serial.println(sizeof(lora_payload));

  Serial.println("Booting up ...");

  // reset module
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);

  // connect to lora service
  lora.autobaud();
  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(lora.hweui());
  Serial.println("RN2483 version number:");
  Serial.println(lora.sysver());
  lora.initOTAA("<YourApplicationEUI>", "<YourAppKey>");
  delay(2000);
}

void loop() {
    // initialize struct
    lora_payload data;
    
    // test data
    double pm2_5 = 399.9; // in µg/m³
    double pm10 = 12.24; // in µg/m³
    double temp = 15.5; // in °C
    double humidity = 51.5; // in %
    int pressure = 98900; // in hPa
    
    // put data into struct
    if(pm2_5 < 400) {
      data.pm2_5 = pm2_5 * 10;
      data.pm2_5_accuracy = 1;
    } else {
      data.pm2_5 = pm2_5;
      data.pm2_5_accuracy = 0;
    }
    if(pm10 < 400) {
      data.pm10 = pm10 * 10;
      data.pm10_accuracy = 1;
    } else {
      data.pm10 = pm10;
      data.pm10_accuracy = 0;
    }
    data.temp = 128 + 2 * temp;
    data.humidity = humidity * 10;
    data.pressure = pressure / 100 - 900;
    data.reserved1_accuracy = 0;
    data.reserved2_accuracy = 0;
    data.reserved3_accuracy = 0;
    data.reserved4_accuracy = 0;

    // try no. 1 for transfering data
    Serial.println("Sending ...");
    bool result = lora.txBytes((byte*)&data, sizeof(lora_payload));
    Serial.println(result ? "Successful" : "Failed");
    //in case of transmission failure
    while(result == 0) {
      delay(3000); // wait 3 secs for retry
      Serial.println("Retry sending: ...");
      result = lora.txBytes((byte*)&data, sizeof(lora_payload));
      Serial.println(result ? "Successful" : "Failed");
    }
    delay(150000); // wait 2.5 min.
}
