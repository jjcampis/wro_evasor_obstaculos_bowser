#include <Servo.h>
#include <NewPing.h>

//variables para tomar como referencia
int distanciaInicialIzq = 0;
int distanciaInicialDer = 0;
// Definir pines para los motores L298
const int motor1 = 7;
const int motor2 = 5;
const int pwm = 6;
//para los giros y avances
unsigned long tiempoInicioAvance = 0;  // Variable para controlar el tiempo de avance
const unsigned long duracionAvance = 10000;  // Duración de avance en milisegundos (5 segundos)

// Definir pines para el servo SG90
const int pinServo = 11;
Servo servo;

// Definir pines para los sensores de ultrasonido
const int TRIG_PIN_1 = 12;//izq
const int ECHO_PIN_1 = 13;
const int TRIG_PIN_2 = 8;//der
const int ECHO_PIN_2 = 9;

// Definir objetos de los sensores de ultrasonido
NewPing s_Izq(TRIG_PIN_1, ECHO_PIN_1, 400);
NewPing s_Der(TRIG_PIN_2, ECHO_PIN_2, 400);

// Definir variables para el contador de vueltas y giros
int contadorVueltas = 0;
int contadorGiros = 0;

void setup() {
  // Inicializar pines de los motores
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);

  // Inicializar el servo
  servo.attach(pinServo);
  // Realizar mediciones iniciales para establecer la referencia
  distanciaInicialIzq = s_Izq.ping_cm();
  distanciaInicialDer = s_Der.ping_cm();
  // Inicializar la comunicación serial
  Serial.begin(9600);
}

void loop() {
  // Realizar mediciones de ultrasonido
  int distanciaIzq = s_Izq.ping_cm();
  int distanciaDer = s_Der.ping_cm();


  // Calcular la diferencia entre las distancias
  int diferenciaDistancias = abs(distanciaIzq - distanciaDer);
if (diferenciaDistancias < 20){
avanzar(255);
}
  // Determinar la dirección más larga
  if ((diferenciaDistancias > 40) && (distanciaIzq > distanciaDer)) {
    // Gira a la izquierda
    giraIzquierda();
    contadorGiros++;
    // Inicia el temporizador de avance
    tiempoInicioAvance = millis();
    // Avanza durante un período de tiempo
    while (millis() - tiempoInicioAvance < duracionAvance) {
      avanzar(127);
    }
  }
  if((diferenciaDistancias > 40) && (distanciaIzq < distanciaDer)) {
    // Gira a la derecha
    giraDerecha();
    contadorGiros++;
    tiempoInicioAvance = millis();
    // Avanza durante un período de tiempo
    while (millis() - tiempoInicioAvance < duracionAvance) {
      avanzar(127);
    }
  }

  // Verificar si se ha completado una vuelta
  if (contadorGiros >= 4) {
    contadorVueltas++;
    contadorGiros = 0;
  }


  // Imprimir información en la comunicación serial
  // Imprimir los resultados en una tabla mediante Serial
  Serial.print("Ssr Izq:");
  Serial.print(distanciaIzq);
  Serial.print("\tSsr Der:");
  Serial.print(distanciaDer);
  Serial.print(" cm");
  Serial.print("\tdiff: ");
  Serial.print(diferenciaDistancias);
  Serial.print(" cm");
  Serial.print("\tVueltas: ");
  Serial.print(contadorVueltas);
  Serial.print("\tGiros: ");
  Serial.println(contadorGiros);
  /*Serial.print("Distancia Izquierda: ");
  Serial.print(distanciaIzq);
  Serial.print(" cm, Distancia Derecha: ");
  Serial.print(distanciaDer);
  Serial.print(" cm, diferencia: ");
  Serial.print(diferenciaDistancias);
  Serial.println(" cm");
  Serial.print(" cm, Vueltas: ");
  Serial.print(contadorVueltas);
  Serial.print(", Giros: ");
  Serial.println(contadorGiros);*/
  
  delay(1000);  // Esperar 1 segundo antes de la siguiente medición
}

void giraIzquierda() {
  servo.write(0);
}

void giraDerecha() {
  servo.write(180);
}
void avanzar(int pot) {
  servo.write(75);
  analogWrite(pwm,pot);
 digitalWrite(motor1,HIGH);  
 digitalWrite(motor2,LOW);  
}
