/*
 * Devre tamam.
 * 
 * Kod tamam.
 * Eposta server denemesi yapıldı. Geç geliyor eposta o yüzden pek sağlıklı olmayacak gibi.
 * PushNotification işi yaş.
 * 
 * ~/www/ringing
 * ~/Arduino/projects
 * 
 */
#include <SPI.h>
#include <Ethernet.h>
#include <string.h>
byte mac[] = {0xDE, 0xEF, 0xBE, 0xED, 0x10, 0xAB};

byte server[] = {192, 168, 1, 64};
int serverPort = 3000;
IPAddress ip(192, 168, 1, 54);
IPAddress myDns(192, 168, 1, 1);

EthernetClient client;
unsigned long byteCount = 0;

int buttonState = 0;
void setup() {
  Serial.begin(9600);
  while (!Serial) {};

  pinMode(2, INPUT); //button
  pinMode(8, OUTPUT); // led

  Serial.println("Initializing ethernet with DHCP!");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet with DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware ) {
      Serial.println("Plug the shield!");
      while (true) {
        delay(1);
      }
    }

    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Plug the cable. IDIOT!");
    }

    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("Configured!: ");
    Serial.print(Ethernet.localIP());
  }
  delay(1000);


}

void loop() {
  buttonState = digitalRead(2);
  if (buttonState == HIGH) {
    Serial.println("Connecting to remote page");
    int connection = client.connect(server, serverPort);
    if (connection == 1) {
      String HTTP_METHOD = "GET";
      String HTTP_URL = "/";
      String HTTP_PROTOCOL = "HTTP/1.1";
      String URL = HTTP_METHOD + " " + HTTP_URL + " " + HTTP_PROTOCOL;

      //Serial.println("URL: " + URL);

      client.println(URL);
      client.println("Host: tester.com");
      client.println("Connection.close");
      client.println();
    } else {
      Serial.println("Connection failed!");
      switch (connection) {
        case -1:
          Serial.println("Timeout");
          break;
        case -2:
          Serial.println("InvalidServer");
          break;
        case -3:
          Serial.println("Truncated");
          break;
        case -4:
          Serial.println("InvalidResponse");
          break;
        default:
          Serial.println("No reason");
          Serial.println(connection);
          break;
      }
    }
    delay(10000);
  } else {
  }

  int len = client.available();
  if (len > 0 ) {
    byte buffer[80];
    if (len > 80) len = 80;
    client.read(buffer, len);
    Serial.write(buffer, len);
    byteCount = byteCount + len;
  }

  //if (!client.connected()) {
  //  Serial.println();
  //  Serial.println("disconnectiong.");
  //  client.stop();
  //  Serial.print("Recieved:" );
  //  Serial.print(byteCount);
  //  while (true) {
  //    delay(1);
  //  }
  //}
}
