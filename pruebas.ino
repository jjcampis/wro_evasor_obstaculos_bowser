#include <NewPing.h>

// Define los pines de los sensores de ultrasonido
const int TRIG_PIN_1 = 12;
const int ECHO_PIN_1 = 13;
const int TRIG_PIN_2 = 8;
const int ECHO_PIN_2 = 9;

// Define los objetos de los sensores de ultrasonido
NewPing s_Izq(TRIG_PIN_1, ECHO_PIN_1, 400);  // Sensor Izquierdo
NewPing s_Der(TRIG_PIN_2, ECHO_PIN_2, 400);  // Sensor Derecho

void setup() {
  // Inicializa la comunicación serial
  Serial.begin(9600);
}

void loop() {
  // Realizar mediciones de ultrasonido
  int dIzq = s_Izq.ping_cm();
  int dDer = s_Der.ping_cm();

  // Imprimir los resultados en una tabla mediante Serial
  Serial.print("Sensor Izquierdo: ");
  Serial.print(dIzq);
  Serial.print(" cm\t\tSensor Derecho: ");
  Serial.print(dDer);
  Serial.print(" cm");
  Serial.print(" cm\t\tdiff: ");
  Serial.print(abs(dDer-dIzq));
  Serial.println(" cm");

  delay(1000);  // Esperar 1 segundo antes de la siguiente medición
}
