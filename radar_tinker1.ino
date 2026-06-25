// C++ code
//
#include <Adafruit_LiquidCrystal.h>

int distEsq = 0;

int distDir = 0;

int inicio = 0;

int fim = 0;

int velocidade = 0;

int i = 0;

int j = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop()
{
  distEsq = 0.01723 * readUltrasonicDistance(4, 5);
  if (distEsq < 20) {
    inicio = 0;
    j = 0;
    while (0.01723 * readUltrasonicDistance(6, 7) > 20) {
      j += 1;
    }
    velocidade = (5000 / j);
    delay(2000); // Wait for 2000 millisecond(s)
    Serial.println(velocidade);
    delay(1000); // Wait for 1000 millisecond(s)
  }
  if (velocidade > 5) {
    lcd_1.print("excesso");
    digitalWrite(2, HIGH);
    delay(2000); // Wait for 2000 millisecond(s)
    digitalWrite(2, LOW);
  } else {
    digitalWrite(3, HIGH);
    delay(2000); // Wait for 2000 millisecond(s)
    digitalWrite(3, LOW);
  }
  lcd_1.clear();
  lcd_1.print(velocidade);
}