#define GREEN 3
#define RED 2
#define VIBRATION 4
#define WORK 2400000
#define REST 600000

void setup() {
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(VIBRATION,OUTPUT);
}

void loop() {
  digitalWrite(VIBRATION,HIGH);
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
  delay(2000);
  
  digitalWrite(VIBRATION,LOW);
  delay(500);
  digitalWrite(GREEN,HIGH);
  delay(WORK);

  digitalWrite(GREEN,LOW);
  digitalWrite(RED,HIGH);
  digitalWrite(VIBRATION,HIGH);
  delay(2000);
  digitalWrite(VIBRATION,LOW);
  delay(REST);
  
}
