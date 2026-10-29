#include <ESP32Servo.h>


// 1. CONFIGURACIÓN PARA 5 DEDOS
const int NUM_DEDOS = 5; 

// Asignación de pines (Pulgar, Índice, Medio, Anular, Meñique)
int pinesServo[NUM_DEDOS] = {2, 4, 6, 10, 21}; 
int pinesBoton[NUM_DEDOS] = {3, 5, 7, 20, 1};  

// Arreglos de memoria para los 5 elementos
Servo servos[NUM_DEDOS];
int posiciones[NUM_DEDOS] = {0, 0, 0, 0, 0};
int estadosBoton[NUM_DEDOS] = {HIGH, HIGH, HIGH, HIGH, HIGH};
int estadosAnteriores[NUM_DEDOS] = {HIGH, HIGH, HIGH, HIGH, HIGH};
unsigned long tiemposRebote[NUM_DEDOS] = {0, 0, 0, 0, 0};

unsigned long retardoRebote = 50; 

void setup() {
  for (int i = 0; i < NUM_DEDOS; i++) {
    servos[i].attach(pinesServo[i], 500, 2400);
    servos[i].write(posiciones[i]); 
    
    pinMode(pinesBoton[i], INPUT_PULLUP);
  }
}

void loop() {
  // El bucle revisa los 5 botones constantemente
  for (int i = 0; i < NUM_DEDOS; i++) {
    actualizarDedo(i);
  }
}

// 2. Maneja cada dedo de forma independiente
void actualizarDedo(int i) {
  int lectura = digitalRead(pinesBoton[i]);

  if (lectura != estadosAnteriores[i]) {
    tiemposRebote[i] = millis(); 
  }

  if ((millis() - tiemposRebote[i]) > retardoRebote) {
    if (lectura != estadosBoton[i]) {
      estadosBoton[i] = lectura;

      if (estadosBoton[i] == LOW) {
        if (posiciones[i] == 0) {
          posiciones[i] = 90; 
        } else {
          posiciones[i] = 0;
        }
        servos[i].write(posiciones[i]);
      }
    }
  }

  estadosAnteriores[i] = lectura;
}
