#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//char server[] = "192.168.0.157";
char server[] = "ihome.fancyproject.pl";

EthernetClient client;
OneWire oneWire(2);
DallasTemperature sensors(&oneWire);
float value;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void loop() {
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {

    Serial.print(" Requesting temperatures..."); 
    sensors.requestTemperatures();

    Serial.print("Temperature is: "); 

    value = sensors.getTempCByIndex(0);
    Serial.print(value); 
    
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("GET /temperature/add?temp="+ String(value) +" HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  delay(60000);
}
