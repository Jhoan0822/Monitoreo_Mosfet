#include <TimerOne.h> //Library Manager: "timerone"

int dutyCycle = 510;  // Ciclo de trabajo (valor entre 2 y 1023)
int switchingT = 1000;  // Periodo de conmutacion en microsegundos
const int debugPin = 8; // Pin de depuración para el osciloscopio

void setup() {
  pinMode(9, OUTPUT);          // Configura el pin 9 como salida para el PWM
  pinMode(debugPin, OUTPUT);    // Configura el pin de depuración como salida
  Timer1.initialize(switchingT);      // 1000us = 1kHz PWM
  Timer1.pwm(9, dutyCycle);     // Aplica el ciclo de trabajo

  Serial.begin(9600);           // Inicializa la comunicación serial para monitorear
}

void loop() {
  
}
