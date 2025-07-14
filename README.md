¡Claro que sí! Crear una buena documentación para tu código es fundamental para un portafolio profesional en GitHub.

Aquí tienes el contenido completo, dividido en la descripción del repositorio y el archivo README.md.

1. Descripción del Repositorio de GitHub

Esta es la descripción corta que aparece debajo del nombre de tu repositorio. Debe ser concisa e informativa.

Descripción:
Arduino code for a project on monitoring MOSFET junction temperature by measuring Thermo-Sensitive Electrical Parameters (TSEPs) in real-time.

2. Contenido para el Archivo README.md

Crea un archivo llamado README.md en la raíz de tu repositorio y pega el siguiente contenido. Está formateado en Markdown para que se vea perfectamente en GitHub.

Generated markdown
# Monitoreo de Temperatura en MOSFETs usando Arduino

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Electronics](https://img.shields.io/badge/Electronics-Project-blue?style=for-the-badge)

Repositorio con el código fuente del proyecto de instrumentación para estimar la temperatura de la unión interna de un MOSFET utilizando Parámetros Eléctricos Sensibles a la Temperatura (TSEPs).

## 📝 Descripción del Proyecto

Este proyecto aborda el monitoreo de la salud de los MOSFETs, componentes críticos en la electrónica de potencia. La falla de estos dispositivos, a menudo causada por estrés térmico, puede comprometer sistemas enteros.

Nuestra solución utiliza dos microcontroladores Arduino para:
1.  **Generar una señal PWM estable** para conmutar el MOSFET.
2.  **Medir de forma síncrona** los parámetros eléctricos VDS (voltaje Dreno-Fuente) y IDS (corriente de Dreno) durante el estado de conducción.
3.  **Calcular la potencia disipada** y, a partir de un modelo térmico, **estimar la temperatura de la unión (Tj)** en tiempo real.

## 📂 Contenido del Repositorio

Este repositorio contiene dos sketches de Arduino principales:

1.  `PWM_Generator.ino`: Código para el Arduino **controlador**. Utiliza la librería `TimerOne` para generar una señal PWM precisa y estable por hardware, minimizando el jitter. Su única función es controlar el gate del MOSFET.

2.  `TSEP_Measurement.ino`: Código para el Arduino de **medición**. Este es el cerebro del sistema. Realiza las siguientes tareas:
    *   Se sincroniza con la señal PWM mediante una interrupción externa.
    *   Lee los valores analógicos de los circuitos de acondicionamiento para VDS y IDS.
    *   Realiza los cálculos para convertir las lecturas del ADC en valores reales de voltaje, corriente, potencia y temperatura.
    *   Envía los resultados al monitor serial para su visualización.

## 🛠️ Hardware y Dependencias

### Hardware Requerido
*   2 x Placas Arduino UNO (o compatibles)
*   1 x MOSFET de potencia (e.g., IRFZ44N)
*   Amplificadores Operacionales (para el circuito de acondicionamiento de señal)
*   Resistencia Shunt de bajo valor (para medir la corriente)
*   Resistencias y capacitores varios
*   Fuente de alimentación

### Software y Librerías
*   [Arduino IDE](https://www.arduino.cc/en/software)
*   Librería `TimerOne.h`: Instalar desde el Gestor de Librerías del Arduino IDE (`Herramientas > Administrar Bibliotecas...` y buscar "TimerOne").

## 🔌 Diagrama de Conexiones

Se utilizó un sistema de dos Arduinos para desacoplar la tarea de control (que requiere temporización precisa) de la tarea de medición (que implica cálculos y comunicación serial).


[Arduino 1: PWM_Generator] --(Pin 9)--> [Circuito Driver del Gate] --> [MOSFET Gate]
|
|---(Copia de la señal PWM)---> [Arduino 2: TSEP_Measurement (Pin 2)]

[Circuito de Potencia con MOSFET] --(Señales VDS y V_shunt)--> [Circuito de Acondicionamiento]
|
|---(VDS_acondicionado)---> [Arduino 2 (Pin A0)]
|---(IDS_acondicionado)---> [Arduino 2 (Pin A1)]

Generated code
**(Nota: Es altamente recomendable añadir una imagen del esquemático del circuito en esta sección para mayor claridad).**

## 💡 Cómo Funciona el Código de Medición

La clave del código `TSEP_Measurement.ino` es la **medición síncrona**.

1.  **Sincronización:** Una interrupción externa se activa en el flanco de subida de la señal PWM (`RISING`). Esto asegura que cada ciclo de medición comience exactamente al mismo tiempo que el MOSFET se enciende.
2.  **Espera Estratégica:** Dentro de la rutina de interrupción, se utiliza `delayMicroseconds()` para esperar hasta la mitad del pulso 'ON'. Esto evita medir durante los transitorios de conmutación (ruido) y captura la señal en su estado más estable.
3.  **Adquisición y Cálculo:** Se leen los valores de los ADC para VDS e IDS. Estos valores se convierten a sus unidades reales aplicando las ganancias inversas de los circuitos de acondicionamiento.
    *   `vdsVoltage = ((vdsValue * 5.0) / 1023.0) * (Factor_Ganancia_VDS)`
    *   `IdsReal = ((Ids_ADC_Voltage) / (Factor_Ganancia_IDS * Rshunt))`
4.  **Estimación de Temperatura:** Con los valores reales de VDS e IDS, se calcula la potencia disipada `Pd = VDS * IDS`. Finalmente, se aplica el modelo térmico estático: `Tj = Pd * Rth_ja + Ta` donde `Rth_ja` es la resistencia térmica de la unión al ambiente y `Ta` es la temperatura ambiente.

**Importante:** Las constantes de ganancia y los parámetros térmicos en el código (`0.512`, `48`, `18.56`) son específicas de nuestro montaje experimental y deben ser calibradas para cualquier otra implementación.

## 🚀 Cómo Usarlo

1.  **Montar el circuito** según el esquemático del proyecto.
2.  **Conectar** ambos Arduinos al computador.
3.  **Abrir `PWM_Generator.ino`** en el Arduino IDE, seleccionar la placa y el puerto correctos, y subir el código al Arduino controlador.
4.  **Abrir `TSEP_Measurement.ino`**, seleccionar la placa y el puerto del segundo Arduino, y subir el código.
5.  **Abrir el Monitor Serie** para el puerto del Arduino de medición y configurarlo a una velocidad de **38400 baudios**.
6.  Observar las mediciones de VDS, IDS, Potencia y Temperatura (Tj) en tiempo real.

## 👨‍💻 Autores

*   **Jhoan Eduardo Saldarriaga Serna**
*   **Alejandro Muñoz Gutiérrez**
*   **Henry Daniel Arboleda Correa**

Proyecto desarrollado como parte del curso de Instrumentación Electrónica en la **Universidad del Valle**.

## 📄 Licencia

Este proyecto se distribuye bajo la Licencia MIT. Ver el archivo `LICENSE` para más detalles.
IGNORE_WHEN_COPYING_START
content_copy
download
Use code with caution.
IGNORE_WHEN_COPYING_END
