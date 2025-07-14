#define pulse_ip 2    // Pin de entrada de la señal PWM
#define voltage_pin A0 // Pin analógico para medir el voltaje
#define debug_pin 13   // Pin de depuración (LED en el pin 13)


volatile bool flag = false; // Bandera para indicar que la interrupción ocurrió
unsigned long intervalo = 1000; // Intervalo en milisegundos, ajustable

int ontime, offtime, duty,Rif,Rig;
float freq, period, voltage,Rshunt,Potencia,D;
const int pinInterrupcion = 2; // Pin 2 para interrupción
volatile bool pulsoDetectado = false;

void setup() {
  Rif=2200;
  Rig=10000;
  Rshunt=0.2;
  D=0.5;
  pinMode(pinInterrupcion, INPUT);
  pinMode(pulse_ip, INPUT);     // Pin de entrada para la señal PWM
  pinMode(voltage_pin, INPUT);  // Pin de entrada para la medición de voltaje
  pinMode(debug_pin, OUTPUT);   // Pin de salida para depuración (LED)
  Serial.begin(38400);           // Inicializa la comunicación serie
   ontime = pulseIn(pulse_ip, HIGH);  // Mide el tiempo de encendido de la señal PWM
   offtime = pulseIn(pulse_ip, LOW);  // Mide el tiempo de apagado de la señal PWM
   period = ontime + offtime;         // Calcula el período completo de la señal
   freq = 1000000.0 / period;         // Calcula la frecuencia de la señal en Hz
   duty = (ontime / period) * 100;    // Calcula el porcentaje de ciclo de trabajo
   // Configurar interrupción en el pin 2 para detectar flanco de subida
  attachInterrupt(digitalPinToInterrupt(pinInterrupcion), detectarPulso, RISING);
}

void loop() {
   if (pulsoDetectado) {
    delayMicroseconds((ontime/2));
                   // Lee el voltaje en VDS
    delayMicroseconds((ontime));
    digitalWrite(debug_pin, HIGH);
    int vdsValue = analogRead(A0);
    int IdsValue = analogRead(A1);               // Lee el voltaje en RI
    float vdsVoltage = (vdsValue * 5.0) / 1023.0; // Convierte el valor leído a voltaje (0-5V)
    float IdsCurrent = ((((IdsValue * 5.0) / 1023.0))); // Convierte el valor leído a voltaje (0-5V)
    delayMicroseconds((ontime/2));
    Serial.print("VDS :");
    Serial.println(vdsVoltage,3);
    Serial.print("VIDS :");
    Serial.println(IdsCurrent,3);
    float IdsReal = ((IdsCurrent/(1+(Rig/Rif)))/(Rshunt));
    Potencia=vdsVoltage*IdsReal*D;
    float Tj = (Potencia*18.56)+25;
     Serial.print("P :");
    Serial.println(Potencia,3);
    Serial.print("Tj :");
    Serial.println(Tj,3);
    pulsoDetectado = false; // Restablecer la bandera
    digitalWrite(debug_pin, LOW);
    interrupts();
  }
}
void detectarPulso() {
  pulsoDetectado = true; // Establece la bandera cuando ocurre el pulso
  noInterrupts();
}#define pulse_ip 2    // Pin de entrada de la señal PWM
#define voltage_pin A0 // Pin analógico para medir el voltaje
#define debug_pin 13   // Pin de depuración (LED en el pin 13)


volatile bool flag = false; // Bandera para indicar que la interrupción ocurrió
unsigned long intervalo = 1000; // Intervalo en milisegundos, ajustable

int ontime, offtime, duty,Rif,Rig;
float freq, period, voltage,Rshunt,Potencia,D,k;
const int pinInterrupcion = 2; // Pin 2 para interrupción
volatile bool pulsoDetectado = false;

void setup() {
  k=0.2;
  Rif=10000;
  Rig=1000;
  Rshunt=0.22;
  D=0.5;
   pinMode(pinInterrupcion, INPUT);
  
  
  pinMode(pulse_ip, INPUT);     // Pin de entrada para la señal PWM
  pinMode(voltage_pin, INPUT);  // Pin de entrada para la medición de voltaje
  pinMode(debug_pin, OUTPUT);   // Pin de salida para depuración (LED)
  Serial.begin(38400);           // Inicializa la comunicación serie
   ontime = pulseIn(pulse_ip, HIGH);  // Mide el tiempo de encendido de la señal PWM
   offtime = pulseIn(pulse_ip, LOW);  // Mide el tiempo de apagado de la señal PWM
   period = ontime + offtime;         // Calcula el período completo de la señal
   freq = 1000000.0 / period;         // Calcula la frecuencia de la señal en Hz
   duty = (ontime / period) * 100;    // Calcula el porcentaje de ciclo de trabajo
   // Configurar interrupción en el pin 2 para detectar flanco de subida
  attachInterrupt(digitalPinToInterrupt(pinInterrupcion), detectarPulso, RISING);
}

void loop() {
   if (pulsoDetectado) {
    delayMicroseconds((ontime/2)*k);
                   // Lee el voltaje en VDS
    delayMicroseconds((ontime));
    digitalWrite(debug_pin, HIGH);
    
    int vdsValue = analogRead(A0);
    
    int IdsValue = analogRead(A1);               // Lee el voltaje en RI
    
    float vdsVoltage = ((vdsValue * 5.0) / 1023.0)*(0.512); // Convierte el valor leído a voltaje (0-5V)
    float IdsCurrent = ((((IdsValue * 5.0) / 1023.0))); // Convierte el valor leído a voltaje (0-5V)
    delayMicroseconds((ontime/2));
    Serial.print("VDS :");
    Serial.println(vdsVoltage,3);
    float IdsReal = ((IdsCurrent)/(48*Rshunt));
    Serial.print("IDS :");
    Serial.println(IdsReal,3);
    
    Potencia=vdsVoltage*IdsReal*D;
    float Tj = (Potencia*18.56)+25;
     Serial.print("P :");
    Serial.println(Potencia,3);
    Serial.print("Tj :");
    Serial.println(Tj,3);
    pulsoDetectado = false; // Restablecer la bandera
    digitalWrite(debug_pin, LOW);
    interrupts();
   
  }
   
}

void detectarPulso() {
  
  pulsoDetectado = true; // Establece la bandera cuando ocurre el pulso
  noInterrupts();
}
