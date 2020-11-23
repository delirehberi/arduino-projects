#include <SPI.h>
#include <Ethernet.h>
#define LED 8

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xEF, 0xED};
EthernetServer server(80);
String readString;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  Ethernet.begin(mac);
  server.begin();

  Serial.print("Server is at:" );
  Serial.print(Ethernet.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.print(c);
        Serial.print("\n");
        if (readString.length() < 100) {
          readString += c;
        }
        if (c == '\n') {
          Serial.print(readString);
          client.println("<HTTP/1.1 200 OK>");
          client.println("<Connection-Type: text/html>");
          client.println("<Connection: close>");
          client.println("");

          client.println("<html><head><title>Test</title></head><body><h1>Hey</h1></html>");
          delay(1);

          client.stop();

          if (readString.indexOf("?ac") > 0) {
            digitalWrite(LED, HIGH);
          }
          if (readString.indexOf("?kapa") > 0) {
            digitalWrite(LED, LOW);
          }
          readString = "";
        }
      }
    }
  }
}
