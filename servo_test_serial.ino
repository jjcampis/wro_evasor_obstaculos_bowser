#include <Servo.h>
// Definir pines para el servo SG90
const int pinServo = 11;
Servo servo;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // Inicializar el servo
  servo.attach(pinServo);
}

void loop() {
if(Serial.available()>0){
  String input = Serial.readStringUntil('\n'); // Lee una línea completa desde la comunicación serial
  int pos = input.toInt();
  Serial.println(pos);
  servo.write(pos);
  }
}
